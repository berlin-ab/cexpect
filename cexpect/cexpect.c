#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "cexpect.h"
#include "cexpect_dot_formatter.h"

#define MAX_SUITE_SIZE 100


struct TestData {
    bool is_active;
    void (*test_function)(Test *test);
    Suite *suite;
    int line_number;
    char *file_name;
};


struct FailedTestData {
    char *expected_value;
    char *actual_value;
    int line_number;
    char *file_name;
};


struct SuiteData {
    char *name;
    Test tests[MAX_SUITE_SIZE];
    FailedTest failed_tests[MAX_SUITE_SIZE];
    int size;
    int number_of_failed_tests;
    int number_of_passing_tests;
    Formatter *formatter;
};


struct FormatterData {
    void (*fail)(Test *test);
    void (*success)(Test *test);
    void (*summary)(Suite *suite);
    void (*report_start)(Suite *suite);
};


/*
 * Suite
 */
Suite *make_suite(char *suite_name) {
	Suite *suite = calloc(1, sizeof(Suite));
	suite->formatter = make_dot_formatter();
	suite->name = suite_name;

	for (int i = 0; i < MAX_SUITE_SIZE; i++) {
		Test test;
		test.is_active = false;
		suite->tests[i] = test;
	}

	return suite;
}


char *get_suite_name(Suite *suite) {
	return suite->name;
}


int number_of_tests(Suite *suite) {
	return suite->size;
}


int number_of_failed_tests(Suite *suite) {
	return suite->number_of_failed_tests;
}


int number_of_passing_tests(Suite *suite) {
	return suite->number_of_passing_tests;
}


/* 
 * Failed tests
 */
FailedTest *get_failed_test(Suite *suite, int test_number) {
	return &suite->failed_tests[test_number];
}


char *get_failing_test_expected_value(FailedTest *failed_test) {
	return failed_test->expected_value;
}


char *get_failing_test_actual_value(FailedTest *failed_test) {
	return failed_test->actual_value;
}


int get_failing_test_line_number(FailedTest *failed_test) {
	return failed_test->line_number;
}


char *get_failing_test_file_name(FailedTest *failed_test) {
	return failed_test->file_name;
}

/*
 * Tests
 */
void add_test_to_suite(Suite *suite, void (*test_function)(Test *test), int line_number, char *file_name) {
	Test test;
	test.is_active = true;
	test.test_function = test_function;
	test.line_number = line_number;
	test.file_name = file_name;
	test.suite = suite;

	suite->tests[suite->size] = test;
	suite->size++;
}


void pass_test(Test *test) {
	test->suite->number_of_passing_tests++;
	test->suite->formatter->success(test);
}


void fail_test(Test *test, char *expected_value, char *actual_value) {
    FailedTest failed_test;
    failed_test.expected_value = expected_value;
    failed_test.actual_value = actual_value;
    failed_test.line_number = test->line_number;
    failed_test.file_name = test->file_name;

    test->suite->failed_tests[test->suite->number_of_failed_tests] = failed_test;
    test->suite->number_of_failed_tests++;
    test->suite->formatter->fail(test);
}


/*
 * Assertions
 */
void expect_equal(Test *test, int expected_value, int actual_value) {
    if (expected_value == actual_value) {
		pass_test(test);
    } else {
		char *expected_value_string = calloc(100, sizeof(char));
		char *actual_value_string = calloc(100, sizeof(char));

		sprintf(expected_value_string, "%d", expected_value);
		sprintf(actual_value_string, "%d", actual_value);

		fail_test(test, expected_value_string, actual_value_string);
    }
}


/*
 * Formatter extension point
 */
Formatter *make_formatter(
	void (*fail)(Test *test),
	void (*success)(Test *test),
	void (*summary)(Suite *suite),
	void (*start)(Suite *suite)
	) {
	Formatter *formatter = calloc(1, sizeof(Formatter));
	formatter->fail = fail;
	formatter->success = success;
	formatter->summary = summary;
	formatter->report_start = start;
	return formatter;
}


void set_formatter(Suite *suite, Formatter *formatter) {
    suite->formatter = formatter;
}


/*
 * Runner
 */
int run_suite(Suite *suite) {
    suite->formatter->report_start(suite);

    for (Test *test = suite->tests; test->is_active == true; test = test+1) {
	test->test_function(test);
    }

    suite->formatter->summary(suite);

    return suite->number_of_failed_tests > 0;
}


void start_cexpect(Suite *suite) {
    exit(run_suite(suite));
}

