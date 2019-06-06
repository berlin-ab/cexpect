#include <stdlib.h>


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
	formatter->success(test);
}


void perform_format_fail(Formatter *formatter, Test *test) {
	formatter->fail(test);
}


void perform_format_start(Formatter *formatter, Suite *suite) {
	formatter->report_start(suite);
}


void perform_format_summary(Formatter *formatter, Suite *suite) {
	formatter->summary(suite);
}
