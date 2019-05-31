.PHONY: test


clean:
	rm -rf build/
	mkdir -p build/


build_cunit: clean
	gcc -Wno-pointer-to-int-cast \
		-shared cunit/cunit.c \
		-fPIC \
		-I . \
		-o build/cunit.so


build_cunit_matchers: clean
	gcc -Wno-pointer-to-int-cast \
		-shared cunit/cmatchers.c \
		-fPIC \
		-I . \
		-o build/cmatchers.so


build_cunit_test:
	gcc -g test/cunit_test.c \
		-I . \
		build/cunit.so \
		-o build/cunit_test.o


build_integers_test:
	gcc -Wno-int-conversion -g test/integers_test.c \
		-I . \
		build/cunit.so build/cmatchers.so \
		-o build/integers_test.o


test_cunit: clean build_cunit build_cunit_matchers build_cunit_test
	./build/cunit_test.o


test_integers: clean build_cunit build_cunit_matchers build_integers_test
	./build/integers_test.o


test: test_cunit test_integers
