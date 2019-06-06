#include <stdlib.h>


#include "cexpect_list.h"
#include "cexpect_internal.h"
#include "cexpect_dot_formatter.h"


/*
 * Runner
 */
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
	exit(run_suite(suite));
}

