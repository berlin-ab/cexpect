.PHONY: test


ifndef VERBOSE
.SILENT:
endif


#
# Run all tests
#
check: test_cexpect test_integers test_booleans test_list test_strings test_cexpect_list_matchers test_cexpect_dot_formatter


test: check


output_dir = build/
lib_dir = build/lib
include_dir = build/include
test_dir = build/test
coverage_dir = build/coverage


coverage_flags = ""
coverage: coverage_flags += --coverage
coverage: check
	gcov *.gc*
	lcov --capture --directory . --output-file build/coverage.info --rc lcov_branch_coverage=1 
	genhtml build/coverage.info --output-directory $(coverage_dir) --branch-coverage --legend --highlight --sort
	rm *.gcno
	rm *.gcda
	rm default.profraw
	open build/coverage/index.html


default_compile_flags = -pedantic-errors -std=gnu99 -Wall -g $(coverage_flags) -Wno-int-conversion -Wno-pointer-to-int-cast -I $(include_dir)
default_link_flags =  -L $(lib_dir)
default_compile_test_flags = $(default_compile_flags) $(default_link_flags)
shared_library_flags = -shared -fPIC


clean:
	rm -rf $(output_dir)
	mkdir -p $(lib_dir)
	mkdir -p $(include_dir)
	mkdir -p $(test_dir)
	mkdir -p $(coverage_dir)


#
# Headers
#
present_external_interface: clean
	cp cexpect/*.h $(include_dir)
	cp cexpect_cmatchers/cexpect_cmatchers.h $(include_dir)
	cp cexpect_dot_formatter/cexpect_dot_formatter.h $(include_dir)


present_cexpect_void_formatter_external_interface: present_external_interface
	cp cexpect_void_formatter/cexpect_void_formatter.h $(include_dir)


#
# Static libraries
#
build_cexpect_core: clean present_external_interface
	$(CC) $(default_compile_flags) cexpect_core/*.c -c
	libtool -static -o $(lib_dir)/libcexpect_core.a *.o
	rm *.o


build_cexpect_dot_formatter: present_external_interface build_cexpect_core
	$(CC) $(default_compile_flags) cexpect_dot_formatter/*.c -c
	libtool -static -o $(lib_dir)/libcexpect_dot_formatter.a *.o
	rm *.o


build_cexpect_cmatchers: clean present_external_interface
	$(CC) $(default_compile_flags) cexpect_cmatchers/*.c -c
	libtool -static -o $(lib_dir)/libcexpect_cmatchers.a *.o
	rm *.o


#
# Shared libraries
#
build_cexpect: clean present_external_interface build_cexpect_dot_formatter build_cexpect_core build_cexpect_cmatchers
	$(CC) $(default_compile_flags) \
		$(shared_library_flags) \
		$(default_link_flags) \
		cexpect/*.c \
		-Wl,-all_load \
		-l cexpect_core \
		-l cexpect_cmatchers \
		-l cexpect_dot_formatter \
		-o $(lib_dir)/libcexpect.so


build_void_formatter: present_cexpect_void_formatter_external_interface
	$(CC) $(default_compile_flags) \
		$(shared_library_flags) \
		$(default_link_flags) \
		cexpect_void_formatter/*.c \
		-l cexpect_core \
		-o $(lib_dir)/libcexpect_void_formatter.so


#
# Build tests
#
build_cexpect_test: clean build_cexpect build_void_formatter
	$(CC) $(default_compile_test_flags) test/cexpect/cexpect_test.c -l cexpect -l cexpect_void_formatter -o $(test_dir)/cexpect_test.o


build_integers_test: clean build_cexpect build_cexpect_cmatchers
	$(CC) $(default_compile_test_flags) test/cexpect_cmatchers/integers_test.c -l cexpect -o $(test_dir)/integers_test.o


build_booleans_test: clean build_cexpect build_void_formatter
	$(CC) $(default_compile_test_flags) test/cexpect_cmatchers/booleans_test.c -l cexpect -l cexpect_void_formatter -o $(test_dir)/booleans_test.o


build_strings_test: clean build_cexpect build_void_formatter
	$(CC) $(default_compile_test_flags) test/cexpect_cmatchers/strings_test.c -l cexpect -l cexpect_void_formatter -o $(test_dir)/strings_test.o


build_custom_list_matchers:
	$(CC) $(default_compile_test_flags) $(shared_library_flags) test/cexpect_list/custom_list_matchers.c -l cexpect  -o $(lib_dir)/libcustom_list_matchers.so


build_list_test: build_custom_list_matchers
	$(CC) $(default_compile_test_flags) test/cexpect_list/list_test.c -l cexpect -l custom_list_matchers -o $(test_dir)/list_test.o


build_cexpect_dot_formatter_test: clean build_cexpect_core build_cexpect build_cexpect_cmatchers build_cexpect_dot_formatter
	$(CC) $(default_compile_test_flags) test/cexpect_dot_formatter/cexpect_dot_formatter_test.c -l cexpect -o $(test_dir)/cexpect_dot_formatter_test.o


build_readme_test:  clean build_cexpect build_cexpect_cmatchers
	$(CC) $(default_compile_test_flags) test/examples/readme_test.c -l cexpect -o $(test_dir)/readme_test.o


build_cexpect_list_matchers_test: clean build_cexpect build_cexpect_core build_cexpect_cmatchers
	$(CC) $(default_compile_test_flags) test/cexpect_list/list_matchers_test.c test/cexpect_list/custom_list_matchers.c -l cexpect -o $(test_dir)/cexpect_list_matchers_test.o


#
# Run tests
#
test_cexpect: clean build_cexpect build_cexpect_cmatchers build_cexpect_test
	./$(test_dir)/cexpect_test.o


test_integers: clean build_cexpect build_cexpect_cmatchers build_integers_test
	./$(test_dir)/integers_test.o


test_booleans: clean build_cexpect build_cexpect_cmatchers build_booleans_test
	./$(test_dir)/booleans_test.o


test_strings: clean build_cexpect build_cexpect_cmatchers build_strings_test
	./$(test_dir)/strings_test.o


test_list: clean build_cexpect build_cexpect_cmatchers build_list_test
	./$(test_dir)/list_test.o


test_cexpect_dot_formatter: clean build_cexpect build_cexpect_cmatchers build_cexpect_dot_formatter_test
	./$(test_dir)/cexpect_dot_formatter_test.o


test_cexpect_list_matchers: clean build_cexpect build_cexpect_cmatchers build_cexpect_list_matchers_test
	./$(test_dir)/cexpect_list_matchers_test.o


readme_test: clean build_cexpect build_cexpect_cmatchers build_readme_test
	./$(test_dir)/readme_test.o
