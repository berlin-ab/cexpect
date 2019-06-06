#include <stdio.h>


#include "cexpect.h"
#include "cexpect_list.h"


static void report_failing_test_with_dot() {
	printf("F");
}


static void report_successful_test_with_dot() {
	printf(".");
}


static void report_start_for_dots(char *suite_name) {
	printf("Running suite: %s\n", suite_name);
}


static void report_summary_for_dots(
	int number_of_tests, 
	int number_of_passing_tests,
	int number_of_failed_tests,
	List *failed_tests
	) {
	printf("\n");
	printf("\n");
	printf("Summary:\n");
	printf("\nRan %d test(s).\n\n%d passed, %d failed",
	       number_of_tests,
	       number_of_passing_tests,
	       number_of_failed_tests);
	printf("\n\n");
	for(ListItem *list_item = list_first(failed_tests); list_item; list_item = list_next(list_item)) {
		FailedTest *failed_test = (FailedTest *)list_value(list_item);
		printf("expected %s, got %s -- %s:%d\n",
		       failed_test->expected_value,
		       failed_test->actual_value,
		       failed_test->file_name,
		       failed_test->line_number);
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
