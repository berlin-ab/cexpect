#include "cexpect_formatter.h"


typedef int (*printer_function_type)(const char *format, ...);


static void report_failing_test_with_dot(void *extra) {
	printer_function_type internal_printer = (printer_function_type) extra;
	internal_printer("F");
}


static void report_pending_test_with_dot(void *extra) {
	printer_function_type internal_printer = (printer_function_type) extra;
	internal_printer("*");
}


static void report_successful_test_with_dot(void *extra) {
	printer_function_type internal_printer = (printer_function_type) extra;
	internal_printer(".");
}


static void report_start_for_dots(char *suite_name, void *extra) {
	printer_function_type internal_printer = (printer_function_type) extra;
	internal_printer("Running suite: %s\n", suite_name);
}


static void report_summary_for_dots(
	int number_of_tests, 
	int number_of_passing_tests,
	int number_of_failed_tests,
	int number_of_pending_tests,
	FailedTest failed_tests[],
	void *extra
	) {
	printer_function_type internal_printer = (printer_function_type) extra;
	internal_printer("\n");
	internal_printer("\n");
	internal_printer("Summary:\n");
	internal_printer("\nRan %d test(s).\n\n%d passed, %d failed, %d pending",
	       number_of_tests,
	       number_of_passing_tests,
	       number_of_failed_tests,
	       number_of_pending_tests);
	internal_printer("\n\n");
	for(int i = 0; i < number_of_failed_tests; i++) {
		FailedTest failed_test = failed_tests[i];
		internal_printer("expected %s, got %s -- %s -- %s:%d\n",
		       failed_test.expected_value,
		       failed_test.actual_value,
		       failed_test.test_name,
		       failed_test.file_name,
		       failed_test.line_number
		       );
	}
	internal_printer("\n");
}


Formatter *make_dot_formatter(printer_function_type new_printer) {
	return make_formatter(
		report_failing_test_with_dot,
		report_successful_test_with_dot,
		report_pending_test_with_dot,
		report_summary_for_dots,
		report_start_for_dots,
		(void *) new_printer
		);
}
