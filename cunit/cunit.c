#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cunit.h"


typedef struct TestData {
	bool is_active;
  void (*test_function)(Test *test);
	void (*fail)(Test *test);
	Suite *suite;
} Test;


struct SuiteData {
	Test tests[100];
	int size;
	int number_of_failed_tests;
	int number_of_passing_tests;
	Formatter *formatter;
};

struct FormatterData {
    void (*fail)(Test *test);
    void (*success)(Test *test);
    void (*summary)(Suite *suite);
};


void debug(char *message) {
//	printf("%s\n", message);
};


void fail_test(Test *test) {
	test->fail(test);
}


void pass_test(Test *test) {
	test->suite->number_of_passing_tests++;
	test->suite->formatter->success(test);
}


int number_of_failed_tests(Suite *suite) {
	return suite->number_of_failed_tests;
}


int number_of_passing_tests(Suite *suite) {
	return suite->number_of_passing_tests;
}


void report_failing_test(Test *test) {
	test->suite->number_of_failed_tests++;
	test->suite->formatter->fail(test);
}


void assert_equal(Test *test, int expected_value, int actual_value) {
    if (expected_value == actual_value) {
	pass_test(test);
    } else {
	fail_test(test);
    }
}


void report_failing_test_with_void(Test *test) {
}


void report_successful_test_with_void(Test *test) {
}


void report_summary_for_void(Suite *suite) {
}


void report_failing_test_with_dot(Test *test) {
    printf("F");
}


void report_successful_test_with_dot(Test *test) {
    printf(".");
}


void report_summary_for_dots(Suite *suite) {
    printf("\n");
    printf("\n");
    printf("Summary:\n");
    printf("\nRan %d test(s).\n\n%d passed, %d failed",
	   suite->size,
	   suite->number_of_passing_tests,
	   suite->number_of_failed_tests);
    printf("\n\n");
}


Formatter *make_void_formatter() {
    Formatter *formatter = calloc(1, sizeof(Formatter));
    formatter->fail = report_failing_test_with_void;
    formatter->success = report_successful_test_with_void;
    formatter->summary = report_summary_for_void;
    return formatter;
}


Formatter *make_dot_formatter() {
    Formatter *formatter = calloc(1, sizeof(Formatter));
    formatter->fail = report_failing_test_with_dot;
    formatter->success = report_successful_test_with_dot;
    formatter->summary = report_summary_for_dots;
    return formatter;
}


void add_test(Suite *suite, void (*test_function)(Test *test)) {
    for (int i = 0; i < 100; i++) {
        Test test;
	test.is_active = false;
	suite->tests[i] = test;
    }

    Test test;
    test.is_active = true;
    test.test_function = test_function;
    test.fail = report_failing_test;
    test.suite = suite;
    
    suite->tests[suite->size] = test;
    suite->size++;
}


void set_formatter(Suite *suite, Formatter *formatter) {
    suite->formatter = formatter;
}


void run_suite(Suite *suite) {
    debug("before suite");

    for (Test *test = suite->tests; test->is_active == true; test = test+1) {
	debug("before test");
	test->test_function(test);
	debug("after test");
    }

    suite->formatter->summary(suite);
    debug("after suite");
}


Suite *make_suite() {
    Suite *suite = calloc(1,sizeof(Suite));
    suite->formatter = make_dot_formatter();
    return suite;
}


void run(Suite *suite) {
    debug("start");
    run_suite(suite);
    debug("end");
}
