#include <stdlib.h>

#include "cexpect_formatter.h"
#include "cexpect_internal.h"


struct FormatterData {
	format_failure fail;
	format_success success;
	format_summary summary;
	format_start report_start;
};


/*
 * Formatter extension point
 */
Formatter *make_formatter(
	format_failure fail,
	format_success success,
	format_summary summary,
	format_start start
) {
	Formatter *formatter = calloc(1, sizeof(Formatter));
	formatter->fail = fail;
	formatter->success = success;
	formatter->summary = summary;
	formatter->report_start = start;
	return formatter;
}


void perform_format_success(Formatter *formatter, Test *test) {
	formatter->success();
}


void perform_format_fail(Formatter *formatter, Test *test) {
	formatter->fail();
}


void perform_format_start(Formatter *formatter, Suite *suite) {
	formatter->report_start(get_suite_name(suite));
}


void perform_format_summary(Formatter *formatter, Suite *suite) {
	int _number_of_failed_tests = number_of_failed_tests(suite);
	FailedTest failed_tests[_number_of_failed_tests];
	
	int i = 0;
	
	for(ListItem *list_item = list_first(get_failed_tests(suite)); list_item; list_item = list_next(list_item)) {
		failed_tests[i] = *(FailedTest *)list_value(list_item);
		i++;
	}
	
	
	formatter->summary(
		number_of_tests(suite),
		number_of_passing_tests(suite),
		_number_of_failed_tests,
		failed_tests
		);
}
