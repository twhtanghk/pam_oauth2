CFLAGS=$(shell python-config --cflags) -std=c99

LDFLAGS=$(shell python-config --ldflags)

CC=gcc

default: isauth users

oauth2.o:
	$(CC) $(CFLAGS) -fPIC -c -o oauth2.o oauth2.c

isauth: oauth2.o
	$(CC) $(CFLAGS) -fPIC -c -o isauth.o isauth.c
	$(CC) $(LDFLAGS) -o isauth oauth2.o isauth.o

users: oauth2.o
	$(CC) $(CFLAGS) -fPIC -c -o users.o users.c
	$(CC) $(LDFLAGS) -o users oauth2.o users.o

clean:
	rm -f *.o *.pyc core isauth isuser users
