#ifndef __oauth2_h
#define __oauth2_h

#include <sys/types.h>

struct User {
  char *name;
  uid_t uid;
  gid_t gid;
  char *home;
  char *shell; 
};  

struct Users {
  int length;
  struct User *result;
};

extern int isauth(const char *id, const char *secret);
extern struct User *isuser(const char *username);
extern struct Users *users(void);

#endif
