#include <stdio.h>
#include "oauth2.h"

int main(int argc, char **argv) {
  struct Users *pUsers = users(); 
  struct User *user = pUsers->result;
  for (int i = 0; i < pUsers->length; i++)
    printf("{name: %s, uid: %d, gid: %d, home: %s, shell: %s}\n", user[i].name, user[i].uid, user[i].gid, user[i].home, user[i].shell);
  return 0;
}
