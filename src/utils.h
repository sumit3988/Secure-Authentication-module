#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

// Secure string copy
void secure_strncpy(char *dest, const char *src, size_t n);

// TOTP generation (simplified for demo)
// In a real app, this would use HMAC-SHA1
int generate_totp(const char *secret, long time_step);

// Verify TOTP
int verify_totp(const char *secret, int user_code);

#endif
