#include "cexpect.h"
#include <stdlib.h>


/* 
 * Void formatter 
 */
static void format_failing_test_with_void(Formatter *formatter, Test *test) {
}


static void format_successful_test_with_void(Formatter *formatter, Test *test) {
}


static void format_suite_summary_for_void(Formatter *formatter, Suite *suite) {
}


static void format_suite_start_for_void(Formatter *formatter, Suite *suite) {
}


Formatter *make_void_formatter() {
	return make_formatter(
		format_failing_test_with_void,
		format_successful_test_with_void,
		format_suite_summary_for_void,
		format_suite_start_for_void,
		NULL);
}
