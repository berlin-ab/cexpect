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
		-shared cunit/cunit_cmatchers.c \
		-fPIC \
		-I . \
		-o build/cunit_cmatchers.so


build_cunit_test:
	gcc -g test/cunit/cunit_test.c \
		-I . \
		build/cunit.so \
		-o build/cunit_test.o


build_integers_test:
	gcc -Wno-int-conversion -g test/matchers/integers_test.c \
		-I . \
		build/cunit.so build/cunit_cmatchers.so \
		-o build/integers_test.o


build_booleans_test:
	gcc -Wno-int-conversion -g test/matchers/booleans_test.c \
	-I . \
	build/cunit.so build/cunit_cmatchers.so \
	-o build/booleans_test.o


test_cunit: clean build_cunit build_cunit_matchers build_cunit_test
	./build/cunit_test.o


test_integers: clean build_cunit build_cunit_matchers build_integers_test
	./build/integers_test.o


test_booleans: clean build_cunit build_cunit_matchers build_booleans_test
	./build/booleans_test.o


readme_test: clean build_cunit build_cunit_matchers
	gcc -Wno-int-conversion -g test/examples/readme_test.c \
		-I . \
		build/cunit.so build/cunit_cmatchers.so \
		-o build/readme_test.o
	./build/readme_test.o


test: test_cunit test_integers test_booleans


