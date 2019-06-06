#ifndef CEXPECT_FORMATTER_H
#define CEXPECT_FORMATTER_H

#include "cexpect_list.h"

typedef struct FormatterData Formatter;
typedef struct FailedTestData FailedTest;


struct FailedTestData {
	char *expected_value;
	char *actual_value;
	int line_number;
	char *file_name;
};


typedef void (*format_failure)();
typedef void (*format_success)();
typedef void (*format_summary)(
	int number_of_tests,
	int number_of_passing_tests,
	int number_of_failed_tests,
	List *failed_tests
);
typedef void (*format_start)(char *suite_name);

Formatter *make_formatter(
	format_failure failure,
	format_success success,
	format_summary summary,
	format_start start);

#endif // CEXPECT_FORMATTER_H
