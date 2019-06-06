#include <stdio.h>


#include "cexpect_internal.h"


static void report_failing_test_with_dot(Test *test) {
	printf("F");
}


static void report_successful_test_with_dot(Test *test) {
	printf(".");
}


static void report_start_for_dots(Suite *suite) {
	printf("Running suite: %s\n", get_suite_name(suite));
}


static void report_summary_for_dots(Suite *suite) {
	printf("\n");
	printf("\n");
	printf("Summary:\n");
	printf("\nRan %d test(s).\n\n%d passed, %d failed",
	       number_of_tests(suite),
	       number_of_passing_tests(suite),
	       number_of_failed_tests(suite));
	printf("\n\n");
	for(int i = 0; i < number_of_failed_tests(suite); i++) {
		FailedTest *failed_test = get_failed_test_for_suite(suite, i);
		printf("expected %s, got %s -- %s:%d\n",
		       get_failing_test_expected_value(failed_test),
		       get_failing_test_actual_value(failed_test),
		       get_failing_test_file_name(failed_test),
		       get_failing_test_line_number(failed_test));
	}
	printf("\n");
}


Formatter *make_dot_formatter() {
	return make_formatter(
		report_failing_test_with_dot,
		report_successful_test_with_dot,
		report_summary_for_dots,
		report_start_for_dots
		);
}
