#include <stdio.h>


#include "cexpect.h"
#include "cexpect_formatter.h"
#include "cexpect_list.h"


typedef int (*printer_function_type)(const char *format, ...);

static printer_function_type printer = printf;


static void report_failing_test_with_dot() {
	printer("F");
}


static void report_successful_test_with_dot() {
	printer(".");
}


static void report_start_for_dots(char *suite_name) {
	printf("Running suite: %s\n", suite_name);
}


static void report_summary_for_dots(
	int number_of_tests, 
	int number_of_passing_tests,
	int number_of_failed_tests,
	FailedTest failed_tests[]
	) {
	printf("\n");
	printf("\n");
	printf("Summary:\n");
	printf("\nRan %d test(s).\n\n%d passed, %d failed",
	       number_of_tests,
	       number_of_passing_tests,
	       number_of_failed_tests);
	printf("\n\n");
	for(int i = 0; i < number_of_failed_tests; i++) {
		FailedTest failed_test = failed_tests[i];
		printf("expected %s, got %s -- %s:%d\n",
		       failed_test.expected_value,
		       failed_test.actual_value,
		       failed_test.file_name,
		       failed_test.line_number);
	}
	printf("\n");
}


Formatter *make_dot_formatter(printer_function_type new_printer) {
	printer = new_printer;
	
	return make_formatter(
		report_failing_test_with_dot,
		report_successful_test_with_dot,
		report_summary_for_dots,
		report_start_for_dots
		);
}
