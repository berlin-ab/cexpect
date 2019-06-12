#include <stdlib.h>


#include "cexpect_formatter.h"


struct FormatterData {
	format_failure fail;
	format_success success;
	format_pending pending;
	format_summary summary;
	format_start report_start;
	void *extra;
};


/*
 * Formatter extension point
 */
Formatter *make_formatter(
	format_failure fail,
	format_success success,
	format_pending pending,
	format_summary summary,
	format_start start,
	void *extra
) {
	Formatter *formatter = calloc(1, sizeof(Formatter));
	formatter->fail = fail;
	formatter->success = success;
	formatter->pending = pending;
	formatter->summary = summary;
	formatter->report_start = start;
	formatter->extra = extra;
	return formatter;
}


void do_format_start(Formatter *formatter, char *suite_name) {
	formatter->report_start(suite_name, formatter->extra);
}


void do_format_failure(Formatter *formatter) {
	formatter->fail(formatter->extra);
}


void do_format_success(Formatter *formatter) {
	formatter->success(formatter->extra);
}


void do_format_pending(Formatter *formatter) {
	formatter->pending(formatter->extra);
}


void do_format_summary(Formatter *formatter,
                       int number_of_tests,
                       int number_of_passing_tests,
                       int number_of_failed_tests,
                       FailedTest failed_tests[]) {

	formatter->summary(
		number_of_tests,
		number_of_passing_tests,
		number_of_failed_tests,
		failed_tests,
		formatter->extra
	);
}
