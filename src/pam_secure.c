#include <security/pam_modules.h>
#include <security/pam_ext.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

// Hardcoded secret for demo purposes (in real life, fetch from DB/file)
#define DEMO_SECRET "JBSWY3DPEHPK3PXP" 

PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    (void)pamh; (void)flags; (void)argc; (void)argv;
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    (void)pamh; (void)flags; (void)argc; (void)argv;
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    (void)flags; (void)argc; (void)argv;
    int retval;
    const char *user;
    char *input_code_str;
    struct pam_conv *conv;
    struct pam_message msg;
    const struct pam_message *msgp;
    struct pam_response *resp;

    retval = pam_get_user(pamh, &user, NULL);
    if (retval != PAM_SUCCESS) {
        return retval;
    }

    // Prompt for TOTP code
    retval = pam_get_item(pamh, PAM_CONV, (const void **)&conv);
    if (retval != PAM_SUCCESS) {
        return retval;
    }

    msg.msg_style = PAM_PROMPT_ECHO_OFF;
    msg.msg = "Enter TOTP Code: ";
    msgp = &msg;

    retval = conv->conv(1, &msgp, &resp, conv->appdata_ptr);
    if (retval != PAM_SUCCESS) {
        return retval;
    }

    if (resp == NULL) {
        return PAM_AUTH_ERR;
    }

    input_code_str = resp[0].resp;
    if (input_code_str == NULL) {
        free(resp);
        return PAM_AUTH_ERR;
    }

    int input_code = atoi(input_code_str);
    
    // Verify TOTP
    if (verify_totp(DEMO_SECRET, input_code)) {
        retval = PAM_SUCCESS;
    } else {
        retval = PAM_AUTH_ERR;
    }

    // Clean up
    memset(input_code_str, 0, strlen(input_code_str)); // Zero out memory
    free(input_code_str);
    free(resp);

    return retval;
}
