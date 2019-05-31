#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cunit.h"


typedef struct TestData {
	bool is_active;
  void (*test_function)(Test *test);
	void (*fail)(Test *test);
	Runner *runner;
} Test;


struct SuiteData {
	Test tests[100];
	int size;
};


struct RunnerData {
	Suite *suite;
	int number_of_failed_tests;
	int number_of_passing_tests;
	Formatter *formatter;
};


struct FormatterData {
	void (*fail)(Test *test);
	void (*success)(Test *test);
};



void debug(char *message) {
//	printf("%s\n", message);
};


void fail_test(Test *test) {
	test->fail(test);
}


void pass_test(Test *test) {
	test->runner->number_of_passing_tests++;
	test->runner->formatter->success(test);
}


int number_of_failed_tests(Runner *runner) {
	return runner->number_of_failed_tests;
}


int number_of_passing_tests(Runner *runner) {
	return runner->number_of_passing_tests;
}

void report_failing_test(Test *test) {
	test->runner->number_of_failed_tests++;
	test->runner->formatter->fail(test);
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


void report_failing_test_with_dot(Test *test) {
	printf("F");
}


void report_successful_test_with_dot(Test *test) {
	printf(".");
}


Formatter *make_void_formatter() {
	Formatter *formatter = calloc(1, sizeof(Formatter));
	formatter->fail = report_failing_test_with_void;
	formatter->success = report_successful_test_with_void;
	return formatter;
}


Formatter *make_dot_formatter() {
	Formatter *formatter = calloc(1, sizeof(Formatter));
	formatter->fail = report_failing_test_with_dot;
	formatter->success = report_successful_test_with_dot;
	return formatter;
}


void add_test(Runner *runner, void (*test_function)(Test *test)) {
	if (runner->suite == NULL) {
		runner->suite = calloc(1, sizeof(Suite));
		runner->number_of_failed_tests = 0;

		for (int i = 0; i < 100; i++) {
			Test test;
			test.is_active = false;
			runner->suite->tests[i] = test;
		}
	}

	Test test;
	test.is_active = true;
	test.test_function = test_function;
	test.fail = report_failing_test;
	test.runner = runner;
	runner->suite->tests[runner->suite->size] = test;
	runner->suite->size++;
}


void set_formatter(Runner *runner, Formatter *formatter) {
	runner->formatter = formatter;
}


void run_suite(Suite *suite) {
	debug("before suite");

	for (Test *test = suite->tests; test->is_active == true; test = test+1) {
		debug("before test");
		test->test_function(test);
		debug("after test");
	}
	
	debug("after suite");
}


Runner *make_runner() {
	Runner *runner = malloc(sizeof(runner));
	runner->formatter = make_void_formatter();
	return runner;
}


void run(Runner *runner) {
	debug("start");
	run_suite(runner->suite);
	debug("end");
}
