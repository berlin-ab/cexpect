.PHONY: test

test:
	rm -rf build/
	mkdir -p build/
	gcc -shared suite/suite.c -fPIC -I . -o build/cunit.so
	gcc test/cunit_test.c \
		-I . \
		build/cunit.so \
		-o build/cunit_test.o \
		&& ./build/cunit_test.o
