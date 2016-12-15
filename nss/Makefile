CFLAGS=$(shell python-config --cflags) -std=c99

LDFLAGS=$(shell python-config --ldflags)

CC=gcc

DEST=/lib/x86_64-linux-gnu

default: libnss_oauth2.so

nss_oauth2.o: nss_oauth2.c
	$(CC) $(CFLAGS) -fPIC -c -o nss_oauth2.o nss_oauth2.c

libnss_oauth2.so: nss_oauth2.o
	$(CC) $(LDFLAGS) -shared -o libnss_oauth2.so ../python/oauth2.o nss_oauth2.o

install: libnss_oauth2.so
	cp -a libnss_oauth2.so $(DEST)
	if test -f $(DEST)/libnss_oauth2.so.2; then rm $(DEST)/libnss_oauth2.so.2; fi
	ln -s $(DEST)/libnss_oauth2.so $(DEST)/libnss_oauth2.so.2

clean:
	rm -f *.o *.so
