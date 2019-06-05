#include <stdlib.h>


#include "cexpect.h"


struct TestData {
	test_function_type test_function;
	Suite *suite;
	int line_number;
	char *file_name;
};


Test *make_test(Suite *suite, test_function_type test_function, int line_number, char *file_name) {
	Test *test = calloc(1, sizeof(Test));
	test->test_function = test_function;
	test->line_number = line_number;
	test->file_name = file_name;
	test->suite = suite;

	return test;
}

Suite *get_suite_for_test(Test *test) {
	return test->suite;
}


int get_line_number_for_test(Test *test) {
	return test->line_number;
};


char *get_file_name_for_test(Test *test) {
	return test->file_name;
};


void perform_test(Test *test) {
	test->test_function(test);
}