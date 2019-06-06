.PHONY: test

ifndef VERBOSE
.SILENT:
endif

output_dir = build/
lib_dir = build/lib
include_dir = build/include
internal_include_dir = build/include_internal
test_dir = build/test
coverage_dir = build/coverage

coverage_flags = ""

ifdef COVERAGE
coverage_flags = --coverage

coverage:
	gcov *.gc*
	lcov --capture --directory . --output-file build/coverage.info
	genhtml build/coverage.info --output-directory build/coverage
	rm *.gcno
	rm *.gcda
	open build/coverage/index.html
endif 

default_compile_flags = -g $(coverage_flags) -Wno-int-conversion -Wno-pointer-to-int-cast -I $(include_dir) -L $(lib_dir) 
shared_library_flags = -shared -fPIC


clean:
	rm -rf $(output_dir)
	mkdir -p $(lib_dir)
	mkdir -p $(include_dir)
	mkdir -p $(internal_include_dir)
	mkdir -p $(test_dir)
	mkdir -p build/coverage


present_external_interface: clean
	cp cexpect/cexpect.h $(include_dir)
	cp cexpect/cexpect_formatter.h $(include_dir)
	cp cexpect_list/cexpect_list.h $(include_dir)
	

present_internal_interface: clean
	cp cexpect/test.h $(internal_include_dir)
	cp cexpect/suite.h $(internal_include_dir)
	cp cexpect/failed_test.h $(internal_include_dir)


present_cexpect_dot_formatter_external_interface: present_external_interface
	cp cexpect_dot_formatter/cexpect_dot_formatter.h $(include_dir)
	

present_cexpect_void_formatter_external_interface: present_external_interface
	cp cexpect_void_formatter/cexpect_void_formatter.h $(include_dir)
	
	
build_cexpect_core: clean present_external_interface present_internal_interface build_list
	$(CC) $(default_compile_flags) -I $(internal_include_dir) $(shared_library_flags) cexpect_core/*.c -l cexpect_list -o $(lib_dir)/libcexpect_core.so
	
	
build_void_formatter: present_cexpect_void_formatter_external_interface
	$(CC) $(default_compile_flags) $(shared_library_flags) cexpect_void_formatter/*.c -l cexpect_list -l cexpect_core -o $(lib_dir)/libcexpect_void_formatter.so
	

build_cexpect_dot_formatter: present_cexpect_dot_formatter_external_interface build_cexpect_core
	$(CC) $(default_compile_flags) $(shared_library_flags) cexpect_dot_formatter/*.c -l cexpect_core -o $(lib_dir)/libcexpect_dot_formatter.so


build_cexpect: clean build_list present_external_interface build_cexpect_dot_formatter build_cexpect_core
	$(CC) $(default_compile_flags) $(shared_library_flags) cexpect/*.c cexpect_dot_formatter/*.c -l cexpect_list -l cexpect_core -o $(lib_dir)/libcexpect.so


build_cexpect_matchers: clean build_cexpect_core
	cp cexpect_matchers/*.h $(include_dir)
	$(CC) $(default_compile_flags) $(shared_library_flags) cexpect_matchers/*.c -lcexpect_core -o $(lib_dir)/libcexpect_cmatchers.so


build_cexpect_test: clean build_void_formatter
	$(CC) $(default_compile_flags) test/cexpect/cexpect_test.c -l cexpect_core -l cexpect -l cexpect_cmatchers -l cexpect_void_formatter -o $(test_dir)/cexpect_test.o


build_integers_test: clean build_cexpect build_cexpect_matchers
	$(CC) $(default_compile_flags) test/cexpect_matchers/integers_test.c -l cexpect -l cexpect_core -l cexpect_cmatchers -o $(test_dir)/integers_test.o


build_booleans_test: clean build_cexpect build_void_formatter
	$(CC) $(default_compile_flags) test/cexpect_matchers/booleans_test.c -l cexpect -l cexpect_core -l cexpect_cmatchers -l cexpect_void_formatter -o $(test_dir)/booleans_test.o
	

build_strings_test: clean build_cexpect build_void_formatter
	$(CC) $(default_compile_flags) test/cexpect_matchers/strings_test.c -l cexpect -l cexpect_cmatchers -l cexpect_void_formatter -l cexpect_core -o $(test_dir)/strings_test.o
	

build_list: clean
	$(CC) $(default_compile_flags) $(shared_library_flags) cexpect_list/*.c -o $(lib_dir)/libcexpect_list.so


build_custom_list_matchers:
	$(CC) $(default_compile_flags) $(shared_library_flags) test/cexpect_list/custom_list_matchers.c -l cexpect_cmatchers -l cexpect_list -o $(lib_dir)/libcustom_list_matchers.so


build_list_test: build_list build_custom_list_matchers
	$(CC) $(default_compile_flags) test/cexpect_list/list_test.c -l cexpect -l cexpect_cmatchers -l cexpect_list -l cexpect_core -l custom_list_matchers -o $(test_dir)/list_test.o


build_cexpect_dot_formatter_test: clean build_cexpect_core build_cexpect build_cexpect_matchers build_cexpect_dot_formatter
	$(CC) $(default_compile_flags) test/cexpect_dot_formatter/cexpect_dot_formatter_test.c -l cexpect -l cexpect_cmatchers -l cexpect_dot_formatter -l cexpect_core -o $(test_dir)/cexpect_dot_formatter_test.o


test_cexpect: clean build_cexpect build_cexpect_matchers build_cexpect_test
	./$(test_dir)/cexpect_test.o


test_integers: clean build_cexpect build_cexpect_matchers build_integers_test
	./$(test_dir)/integers_test.o


test_booleans: clean build_cexpect build_cexpect_matchers build_booleans_test
	./$(test_dir)/booleans_test.o


test_strings: clean build_cexpect build_cexpect_matchers build_strings_test
	./$(test_dir)/strings_test.o


test_list: clean build_cexpect build_cexpect_matchers build_list_test
	./$(test_dir)/list_test.o


test_cexpect_dot_formatter: clean build_cexpect build_cexpect_matchers build_cexpect_dot_formatter_test
	./$(test_dir)/cexpect_dot_formatter_test.o


build_readme_test:  clean build_cexpect build_cexpect_matchers
	$(CC) $(default_compile_flags) test/examples/readme_test.c -l cexpect -l cexpect_cmatchers -l cexpect_core -o $(test_dir)/readme_test.o


readme_test: clean build_cexpect build_cexpect_matchers build_readme_test
	./$(test_dir)/readme_test.o




test: test_cexpect test_integers test_booleans test_list test_strings test_cexpect_dot_formatter
