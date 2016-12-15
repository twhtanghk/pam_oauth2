#include <syslog.h>
#include <Python.h>
#include <security/pam_modules.h>
#include "../python/oauth2.h"

PAM_EXTERN int pam_sm_chauthtok(pam_handle_t *pamh, int flags, int argc, const char **argv) {
  syslog(LOG_AUTH|LOG_DEBUG, "oauth2 pam_chauthtok");
  return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_open_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
  syslog(LOG_AUTH|LOG_DEBUG, "oauth2 pam_open_session");
  return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_close_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
  syslog(LOG_AUTH|LOG_DEBUG, "oauth2 pam_close_session");
  return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv) {
  syslog(LOG_AUTH|LOG_DEBUG, "oauth2 pam_sm_authenticate");
  const char *id, *secret;
  pam_get_user(pamh, &id, NULL);
  pam_get_authtok(pamh, PAM_AUTHTOK, &secret, NULL);
  return isauth(id, secret) ? PAM_SUCCESS : PAM_AUTH_ERR;
}

PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv) {
  syslog(LOG_AUTH|LOG_DEBUG, "oauth2 pam_sm_setcred");
  return PAM_CRED_UNAVAIL;
}

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv) {
  syslog(LOG_AUTH|LOG_DEBUG, "oauth2 pam_sm_acct_mgmt");
  return PAM_SUCCESS;
}
