#include <stdlib.h>


#include "cexpect_internal.h"
#include "cexpect_list.h"


FailedTest *make_failed_test(Test *test, char *expected_value, char *actual_value) {
	FailedTest *failed_test = calloc(1, sizeof(FailedTest));
	failed_test->expected_value = expected_value;
	failed_test->actual_value = actual_value;
	failed_test->line_number = get_line_number_for_test(test);
	failed_test->file_name = get_file_name_for_test(test);
	return failed_test;
}

/* 
 * Failed tests
 */
FailedTest *get_failed_test(List *failed_tests, int test_number) {
	int index = 0;

	for (ListItem *item = list_first(failed_tests); item; item = list_next(item)) {
		if (test_number == index) {
			return (FailedTest *)list_value(item);
		}
		index++;
	}

	return NULL;
}


char *get_failing_test_expected_value(FailedTest *failed_test) {
	return failed_test->expected_value;
}


char *get_failing_test_actual_value(FailedTest *failed_test) {
	return failed_test->actual_value;
}


int get_failing_test_line_number(FailedTest *failed_test) {
	return failed_test->line_number;
}


char *get_failing_test_file_name(FailedTest *failed_test) {
	return failed_test->file_name;
}
