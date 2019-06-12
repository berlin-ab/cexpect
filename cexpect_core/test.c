#include <stdlib.h>
#include <stdbool.h>


#include "cexpect.h"


#include "internal/suite.h"
#include "internal/failed_test.h"


struct TestData {
	test_function_type test_function;
	Suite *suite;
	int line_number;
	char *file_name;
	bool is_pending;
};


Test *make_test(Suite *suite, test_function_type test_function) {
	Test *test = calloc(1, sizeof(Test));
	test->is_pending = true;
	test->test_function = test_function;
	test->suite = suite;

	return test;
}


Suite *get_suite_for_test(Test *test) {
	return test->suite;
}


static bool is_still_pending(Test *test) {
	return test->is_pending;
}


static void notify_of_pending_test(Test *test) {
	Suite *suite = test->suite;
	increment_pending_tests(suite);
	Formatter *formatter = get_formatter(suite);
	do_format_pending(formatter);
}


static void mark_no_longer_pending(Test *test) {
	test->is_pending = false;
}


void perform_test(Test *test) {
	test->test_function(test);

	if (is_still_pending(test))
		notify_of_pending_test(test);
}


void pass_test(Test *test) {
	mark_no_longer_pending(test);
	
	Suite *suite = get_suite_for_test(test);
	increment_passing_tests(suite);

	Formatter *formatter = get_formatter(suite);
	
	do_format_success(formatter);
}


void fail_test(Test *test, char *expected_value, char *actual_value, int line_number, char *file_name) {
	mark_no_longer_pending(test);
	
	FailedTest *failed_test = make_failed_test(
		expected_value,
		actual_value,
		line_number,
		file_name);

	Suite *suite = get_suite_for_test(test);

	add_to_list(
		get_failed_tests(suite),
		failed_test);

	do_format_failure(get_formatter(suite));
}


