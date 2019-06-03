#include "cexpect.h"


/* 
 * Void formatter 
 */
static void report_failing_test_with_void(Test *test) {
}


static void report_successful_test_with_void(Test *test) {
}


static void report_summary_for_void(Suite *suite) {
}


static void report_start_for_void(Suite *suite) {
}


Formatter *make_void_formatter() {
	return make_formatter(
		report_failing_test_with_void,
		report_successful_test_with_void,
		report_summary_for_void,
		report_start_for_void);
}
