#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <nss.h>
#include <syslog.h>
#include <Python.h>
#include "../python/oauth2.h"

static struct Users *userlist = NULL;
static struct User *curr = NULL;

void toPasswd(struct User *user, struct passwd *pwd) {
  pwd->pw_name = user->name;
  pwd->pw_uid = user->uid;
  pwd->pw_gid = user->gid;
  pwd->pw_gecos = user->name;
  pwd->pw_dir = user->home;
  pwd->pw_shell = user->shell;
}

/**
 * Prepare buffers.
 */
enum nss_status _nss_oauth2_setpwent(void)
{
  syslog(LOG_AUTH|LOG_DEBUG, "_nss_oauth2_setpwent() called");
  userlist = users();
  curr = userlist->result;
  return NSS_STATUS_SUCCESS;
}

/**
 * Free buffers.
 */
enum nss_status _nss_oauth2_endpwent(void)
{
  syslog(LOG_AUTH|LOG_DEBUG, "_nss_oauth2_endpwent() called");
  return NSS_STATUS_SUCCESS;
}

enum nss_status _nss_oauth2_getpwent_r(struct passwd *result, char *buffer, size_t buflen, int *errnop)
{
  syslog(LOG_AUTH|LOG_DEBUG, "_nss_oauth2_getpwent_r() called");
  if ((curr - userlist->result) < userlist->length) {
    toPasswd(curr, result);
    curr++;
    return NSS_STATUS_SUCCESS;
  } else {
    return NSS_STATUS_NOTFOUND;
  }
}

enum nss_status _nss_oauth2_getpwuid_r(uid_t uid, struct passwd *result, char *buffer, size_t buflen, int *errnop)
{
  syslog(LOG_AUTH|LOG_DEBUG, "_nss_oauth2_getpwuid_r() called");
  userlist = users();
  if (userlist) {
    for (int i = 0; i < userlist->length; i++) {
      if (userlist->result[i].uid == uid) {
        toPasswd(&userlist->result[i], result);
        return NSS_STATUS_SUCCESS;
      }
    }
    return NSS_STATUS_NOTFOUND;
  } else {
    return NSS_STATUS_NOTFOUND;
  }
}

enum nss_status _nss_oauth2_getpwnam_r(const char *name, struct passwd *result, char *buffer, size_t buflen, int *errnop)
{
  syslog(LOG_AUTH|LOG_DEBUG, "_nss_oauth2_getpwnam_r() called");
  struct User *user = isuser(name);
  if (user) {
    toPasswd(user, result);
    return NSS_STATUS_SUCCESS;
  } else {
    return NSS_STATUS_NOTFOUND;
  }
}
