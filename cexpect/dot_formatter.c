#include <stdio.h>


#include "cexpect.h"
#include "cexpect_dot_formatter.h"


static printer_function_type get_printer(Formatter *formatter) {
	return (printer_function_type) get_formatter_extra(formatter);
}


static void report_failing_test_with_dot(Formatter *formatter, Test *test) {
	printer_function_type printer = get_printer(formatter);
	printer("F");
}


static void report_successful_test_with_dot(Formatter *formatter, Test *test) {
	printer_function_type printer = get_printer(formatter);
	printer(".");
}


static void report_start_for_dots(Formatter *formatter, Suite *suite) {
	printer_function_type printer = get_printer(formatter);
	printer("Running suite: %s\n", get_suite_name(suite));
}


static void report_summary_for_dots(Formatter *formatter, Suite *suite) {
	printer_function_type printer = get_printer(formatter);
	printer("\n");
	printer("\n");
	printer("Summary:\n");
	printer("\nRan %d test(s).\n\n%d passed, %d failed",
	       number_of_tests(suite),
	       number_of_passing_tests(suite),
	       number_of_failed_tests(suite));
	printer("\n\n");
	for(int i = 0; i < number_of_failed_tests(suite); i++) {
		FailedTest *failed_test = get_failed_test(suite, i);
		printer("expected %s, got %s -- %s:%d\n",
		       get_failing_test_expected_value(failed_test),
		       get_failing_test_actual_value(failed_test),
		       get_failing_test_file_name(failed_test),
		       get_failing_test_line_number(failed_test));
	}
	printer("\n");
}


Formatter *make_dot_formatter(printer_function_type printer) {
	return make_formatter(
		report_failing_test_with_dot,
		report_successful_test_with_dot,
		report_summary_for_dots,
		report_start_for_dots,
		printer
		);
}
