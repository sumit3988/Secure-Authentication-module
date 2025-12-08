#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include "../src/utils.h"

int main() {
    printf("Running Unit Tests...\n");
    
    // Test 1: TOTP Generation and Verification
    const char *secret = "JBSWY3DPEHPK3PXP";
    long t = time(NULL) / 30;
    int code = generate_totp(secret, t);
    printf("Generated Code: %d\n", code);
    
    if (verify_totp(secret, code)) {
        printf("PASS: TOTP Verification (Current Time)\n");
    } else {
        printf("FAIL: TOTP Verification (Current Time)\n");
        return 1;
    }

    if (!verify_totp(secret, code + 100)) {
        printf("PASS: TOTP Verification (Invalid Code)\n");
    } else {
        printf("FAIL: TOTP Verification (Invalid Code)\n");
        return 1;
    }

    // Test 2: Secure String Copy
    char dest[10];
    secure_strncpy(dest, "123456789012345", sizeof(dest));
    if (strlen(dest) == 9 && dest[9] == '\0') {
        printf("PASS: Secure String Copy (Truncation)\n");
    } else {
        printf("FAIL: Secure String Copy (Truncation)\n");
        return 1;
    }

    printf("All Unit Tests Passed.\n");
    return 0;
}
