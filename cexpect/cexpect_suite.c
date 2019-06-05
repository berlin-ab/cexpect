#include <stdlib.h>


#include "cexpect.h"
#include "cexpect_list.h"
#include "cexpect_dot_formatter.h"


struct SuiteData {
	char *name;
	List *tests;
	List *failed_tests;
	int number_of_passing_tests;
	Formatter *formatter;
};


/*
 * Suite
 */
Suite *make_suite(char *suite_name) {
	Suite *suite = calloc(1, sizeof(Suite));
	suite->formatter = make_dot_formatter();
	suite->name = suite_name;
	suite->tests = make_list();
	suite->failed_tests = make_list();

	return suite;
}


void set_formatter(Suite *suite, Formatter *formatter) {
	suite->formatter = formatter;
}


char *get_suite_name(Suite *suite) {
	return suite->name;
}


int number_of_tests(Suite *suite) {
	return list_size(suite->tests);
}


int number_of_failed_tests(Suite *suite) {
	return list_size(suite->failed_tests);
}


int number_of_passing_tests(Suite *suite) {
	return suite->number_of_passing_tests;
}

FailedTest *get_failed_test_for_suite(Suite *suite, int test_number) {
	return get_failed_test(suite->failed_tests, test_number);
}

/*
 * Tests
 */
void add_test_to_suite(Suite *suite, test_function_type test_function, int line_number, char *file_name) {
	add_to_list(suite->tests, make_test(suite, test_function, line_number, file_name));
}


void pass_test(Test *test) {
	Suite *suite = get_suite_for_test(test);
	suite->number_of_passing_tests++;

	Formatter *formatter = get_formatter(suite);
	perform_format_success(formatter, test);
}


void fail_test(Test *test, char *expected_value, char *actual_value) {
	FailedTest *failed_test = make_failed_test(test, expected_value, actual_value);
	Suite *suite = get_suite_for_test(test);
	add_to_list(suite->failed_tests, failed_test);
	perform_format_fail(suite->formatter, test);
}


Formatter *get_formatter(Suite *suite) {
	return suite->formatter;
}


List *get_tests(Suite *suite) {
	return suite->tests;
}
