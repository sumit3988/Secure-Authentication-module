#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void secure_strncpy(char *dest, const char *src, size_t n) {
    if (n > 0) {
        strncpy(dest, src, n - 1);
        dest[n - 1] = '\0';
    }
}

// Simplified TOTP for demonstration
// Real implementation requires HMAC-SHA1 and base32 decoding
int generate_totp(const char *secret, long time_step) {
    unsigned long hash = 0;
    size_t i;
    for (i = 0; i < strlen(secret); i++) {
        hash = hash * 31 + secret[i];
    }
    // Mix time_step in a non-linear way
    hash = (hash ^ time_step) * 2654435761ul; 
    return (int)(hash % 1000000);
}

int verify_totp(const char *secret, int user_code) {
    long current_time = time(NULL) / 30; // 30-second window
    
    // Check current, previous, and next window for drift
    if (generate_totp(secret, current_time) == user_code) return 1;
    if (generate_totp(secret, current_time - 1) == user_code) return 1;
    if (generate_totp(secret, current_time + 1) == user_code) return 1;
    
    return 0;
}
