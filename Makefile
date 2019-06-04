.PHONY: test

ifndef VERBOSE
.SILENT:
endif


output_dir = build/
lib_dir = build/lib
include_dir = build/include
test_dir = build/test


default_compile_flags = -Wno-int-conversion -Wno-pointer-to-int-cast -g -I $(include_dir) -L $(lib_dir) 
shared_library_flags = -shared -fPIC


clean:
	rm -rf $(output_dir)
	mkdir -p $(lib_dir)
	mkdir -p $(include_dir)
	mkdir -p $(test_dir)


build_cexpect: clean
	cp cexpect/*.h build/include/
	$(CC) $(default_compile_flags) $(shared_library_flags) cexpect/*.c -o $(lib_dir)/libcexpect.so


build_cexpect_matchers: clean
	cp cexpect_matchers/*.h build/include/
	$(CC) $(default_compile_flags) $(shared_library_flags) cexpect_matchers/*.c -lcexpect -o $(lib_dir)/libcexpect_cmatchers.so


build_cexpect_test:
	$(CC) $(default_compile_flags) test/cexpect/cexpect_test.c -l cexpect -o $(test_dir)/cexpect_test.o


build_integers_test: clean build_cexpect build_cexpect_matchers
	$(CC) $(default_compile_flags) test/matchers/integers_test.c -l cexpect -l cexpect_cmatchers -o $(test_dir)/integers_test.o


build_booleans_test:
	$(CC) $(default_compile_flags) test/matchers/booleans_test.c -l cexpect -l cexpect_cmatchers -o $(test_dir)/booleans_test.o
	

build_list:
	cp cexpect_list/*.h $(include_dir)/
	$(CC) $(default_compile_flags) $(shared_library_flags) cexpect_list/*.c -o $(lib_dir)/libcexpect_list.so


build_custom_list_matchers:
	$(CC) $(default_compile_flags) $(shared_library_flags) test/examples/custom_list_matchers.c -l cexpect_cmatchers -l cexpect_list -o $(lib_dir)/libcustom_list_matchers.so


build_list_test: build_list build_custom_list_matchers
	$(CC) $(default_compile_flags) test/examples/list_test.c -l cexpect -l cexpect_cmatchers -l cexpect_list -l custom_list_matchers -o $(test_dir)/list_test.o


test_cexpect: clean build_cexpect build_cexpect_matchers build_cexpect_test
	./$(test_dir)/cexpect_test.o


test_integers: clean build_cexpect build_cexpect_matchers build_integers_test
	./$(test_dir)/integers_test.o


test_booleans: clean build_cexpect build_cexpect_matchers build_booleans_test
	./$(test_dir)/booleans_test.o


test_list: clean build_cexpect build_cexpect_matchers build_list_test
	./$(test_dir)/list_test.o
	

build_readme_test:  clean build_cexpect build_cexpect_matchers
	$(CC) $(default_compile_flags) test/examples/readme_test.c -l cexpect -l cexpect_cmatchers -o $(test_dir)/readme_test.o


readme_test: clean build_cexpect build_cexpect_matchers build_readme_test
	./$(test_dir)/readme_test.o


test: test_cexpect test_integers test_booleans test_list
