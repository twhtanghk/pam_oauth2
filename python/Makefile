CFLAGS=$(shell python-config --cflags | sed 's/\-Werror=format\-security//g') -std=c99

LDFLAGS=$(shell python-config --ldflags)

CC=gcc

default: isauth users

oauth2.o:
	$(CC) $(CFLAGS) -fPIC -c -o oauth2.o oauth2.c

isauth: oauth2.o
	$(CC) $(CFLAGS) -fPIC -c -o isauth.o isauth.c
	$(CC) -o isauth oauth2.o isauth.o $(LDFLAGS)

users: oauth2.o
	$(CC) $(CFLAGS) -fPIC -c -o users.o users.c
	$(CC) -o users oauth2.o users.o $(LDFLAGS)

clean:
	rm -f *.o *.pyc core isauth isuser users
