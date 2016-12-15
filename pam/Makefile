CFLAGS=$(shell python-config --cflags)

LDFLAGS=$(shell python-config --ldflags)

CC=gcc

DEST=/lib/security

default: pam_oauth2.so

pam_oauth2.o: pam_oauth2.c
	$(CC) $(CFLAGS) -fPIC -c -o pam_oauth2.o pam_oauth2.c

pam_oauth2.so: pam_oauth2.o
	$(CC) $(LDFLAGS) -shared -o pam_oauth2.so ../python/oauth2.o pam_oauth2.o

install: pam_oauth2.so
	if ! test -d $(DEST); then mkdir $(DEST); fi
	cp -a pam_oauth2.so $(DEST)

clean:
	rm -f *.o *.so
