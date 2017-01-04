#include <Python.h>
#include <syslog.h>
#include "oauth2.h"

#define PyString_FromString(s) PyUnicode_DecodeFSDefault(s)
#define PyString_AsString(s) PyBytes_AS_STRING(PyUnicode_AsEncodedString(s, "utf-8", "strict"))

char *pyhome = NULL;
PyObject *pIsauth = NULL;
PyObject *pIsuser = NULL;
PyObject *pClient = NULL;
PyObject *pUsers = NULL;
PyObject *pModule = NULL;
struct Users userlist;

extern char **environ;

void printenv(void) {
  for (char **curr = environ; *curr != NULL; curr++)
    syslog(LOG_AUTH|LOG_DEBUG, *curr);
}

void config(void) {
#ifdef DEBUG
  printenv();
#endif

  if (pIsauth == NULL) {
    Py_Initialize();
    PyObject *pName = PyString_FromString("oauth2");
    pModule = PyImport_Import(pName);

    pIsauth = PyObject_GetAttrString(pModule, "isauth");
  }

  if (pIsuser == NULL) {
    pIsuser = PyObject_GetAttrString(pModule, "isuser");
  }

  if (pUsers == NULL) {
    pUsers = PyObject_GetAttrString(pModule, "users");
  }
}

int isauth(const char *id, const char *secret) {
  config();

  PyObject *pArgs = PyTuple_New(1);

  PyObject *user = PyDict_New();
  PyDict_SetItemString(user, "id", PyString_FromString(id));
  PyDict_SetItemString(user, "secret", PyString_FromString(secret));
  PyTuple_SetItem(pArgs, 0, user);

  return Py_True == PyObject_CallObject(pIsauth, pArgs);
}

void pyUser(PyObject *pyuser, struct User *user) {
    user->name = PyString_AsString(PyDict_GetItem(pyuser, PyString_FromString("name")));
    user->uid = PyLong_AsLong(PyDict_GetItem(pyuser, PyString_FromString("uid")));
    user->gid = PyLong_AsLong(PyDict_GetItem(pyuser, PyString_FromString("gid")));
    user->home= PyString_AsString(PyDict_GetItem(pyuser, PyString_FromString("home")));
    user->shell = PyString_AsString(PyDict_GetItem(pyuser, PyString_FromString("shell")));
}

struct User found;
struct User *isuser(const char *username) {
  config();

  PyObject *pArgs = PyTuple_New(1);

  PyTuple_SetItem(pArgs, 0, PyString_FromString(username));

  PyObject *ret = PyObject_CallObject(pIsuser, pArgs);
  if (ret != Py_None)
    pyUser(ret, &found);
  return ret == Py_None ? NULL : &found;
}

struct Users *users(void) {
  config();

  PyObject *list = PyObject_CallObject(pUsers, NULL);
  userlist.length = PyList_Size(list);
  if (userlist.result != NULL)
    free(userlist.result);
  userlist.result = calloc(userlist.length, sizeof(struct User));
  for (int i = 0; i < userlist.length; i++) {
    PyObject *user = PyList_GetItem(list, i);
    pyUser(user, &userlist.result[i]);
  }
  return &userlist; 
}
