#include <stdlib.h>


#include "cexpect_formatter.h"


/* 
 * Void formatter 
 */
static void report_failing_test_with_void(void *extra) {
}


static void report_successful_test_with_void(void *extra) {
}


static void report_pending_test_with_void(void *extra) {
}


static void report_summary_for_void(
	int number_of_tests,
	int number_of_passing_tests,
	int number_of_failed_tests,
	int number_of_pending_tests,
	FailedTest failed_tests[],
	void *extra
) {
}


static void report_start_for_void(char *suite_name, void *extra) {
}


Formatter *make_void_formatter() {
	return make_formatter(
		report_failing_test_with_void,
		report_successful_test_with_void,
		report_pending_test_with_void,
		report_summary_for_void,
		report_start_for_void,
		NULL);
}
