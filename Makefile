default: install

compile:
	cd python; make

install: compile
	cd nss; make install
	cd pam; make install

clean:
	cd python; make clean
	cd nss; make clean
	cd pam; make clean
