#include <stdlib.h>
#include <stdio.h>


#include "cexpect.h"
#include "cexpect_list.h"
#include "cexpect_internal.h"
#include "cexpect_dot_formatter.h"


Suite *create_suite(char *suite_name) {
	return make_suite(suite_name, make_dot_formatter(&printf));
}


void set_formatter(Suite *suite, Formatter *formatter) {
	set_formatter_for_suite(suite, formatter);
}


void add_test_to_suite(Suite *suite, test_function_type test_function, int line_number, char *file_name) {
	add_to_list(
		get_tests(suite), 
		make_test(suite, test_function, line_number, file_name));
}


int run_suite(Suite *suite) {
	Formatter *formatter = get_formatter(suite);
	perform_format_start(formatter, suite);

	for (ListItem *item = list_first(get_tests(suite)); item; item = list_next(item)) {
		Test *test = list_value(item);
		perform_test(test);
	}

	perform_format_summary(formatter, suite);

	return number_of_failed_tests(suite) > 0;
}


void start_cexpect(Suite *suite) {
	int status_code = run_suite(suite);

	exit(status_code);
}

