test_compile_flags = --coverage -Wno-int-conversion -g -I cexpect build/cexpect.so build/cexpect_cmatchers.so


.PHONY: test

clean:
	rm -rf build/
	mkdir -p build/


build_cexpect: clean
	gcc -g \
		--coverage \
		-Wno-pointer-to-int-cast \
		-shared cexpect/cexpect.c \
		-fPIC \
		-I cexpect \
		-o build/cexpect.so


build_cexpect_matchers: clean
	gcc -g \
		--coverage \
		-Wno-pointer-to-int-cast \
		-shared cexpect/cexpect_cmatchers.c \
		-fPIC \
		-I cexpect \
		-o build/cexpect_cmatchers.so


build_cexpect_test:
	gcc -g \
		--coverage \
		test/cexpect/cexpect_test.c \
		-I cexpect \
		build/cexpect.so \
		-o build/cexpect_test.o


build_integers_test:
	gcc test/matchers/integers_test.c $(test_compile_flags) -o build/integers_test.o


build_booleans_test:
	gcc test/matchers/booleans_test.c $(test_compile_flags) -o build/booleans_test.o


build_list_test:
	gcc test/examples/list_test.c $(test_compile_flags) -o build/list_test.o


build_libraries: clean build_cexpect build_cexpect_matchers


test_cexpect: build_libraries build_cexpect_test
	./build/cexpect_test.o


test_integers: build_libraries build_integers_test
	./build/integers_test.o


test_booleans: build_libraries build_booleans_test
	./build/booleans_test.o


test_list: build_libraries build_list_test
	./build/list_test.o


test_readme: clean build_cexpect build_cexpect_matchers
	gcc -Wno-int-conversion -g test/examples/readme_test.c \
		-I cexpect \
		build/cexpect.so build/cexpect_cmatchers.so \
		-o build/readme_test.o
	./build/readme_test.o


test: test_cexpect test_integers test_booleans

