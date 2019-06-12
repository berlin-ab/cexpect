#ifndef CEXPECT_FORMATTER_H
#define CEXPECT_FORMATTER_H


typedef struct FormatterData Formatter;
typedef struct FailedTestData FailedTest;


struct FailedTestData {
	char *expected_value;
	char *actual_value;
	int line_number;
	char *file_name;
	void *extra;
};


typedef void (*format_failure)(void *extra);
typedef void (*format_success)(void *extra);
typedef void (*format_pending)(void *extra);
typedef void (*format_summary)(
	int number_of_tests,
	int number_of_passing_tests,
	int number_of_failed_tests,
	int number_of_pending_tests,
	FailedTest failed_tests[],
	void *extra
);
typedef void (*format_start)(char *suite_name, void *extra);


Formatter *make_formatter(
	format_failure failure,
	format_success success,
	format_pending pending,
	format_summary summary,
	format_start start,
	void *extra
	);

void do_format_success(Formatter *formatter);
void do_format_failure(Formatter *formatter);
void do_format_pending(Formatter *formatter);
void do_format_start(Formatter *formatter, char *suite_name);
void do_format_summary(
	Formatter *formatter,
	int number_of_tests,
	int number_of_passing_tests,
	int number_of_failed_tests,
	int number_of_pending_tests,
	FailedTest failed_tests[]
);


#endif // CEXPECT_FORMATTER_H
