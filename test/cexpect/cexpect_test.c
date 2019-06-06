#include <stdlib.h>
#include <stdio.h>


#include "cexpect.h"
#include "cexpect_cmatchers.h"
#include "cexpect_void_formatter.h"
#include "cexpect_dot_formatter.h"


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
 * Test helpers
 */
static char *some_before_each_value = "something invalid";
static char *some_after_each_value = "something invalid";


void some_failing_test(Test *test) {
	expect_equal(test, 1, 2);
}


void some_passing_test(Test *test) {
	expect_equal(test, 1, 1);
}


void before_each() {
	some_before_each_value = "changed by before each";
}


void after_each() {
	some_after_each_value = "changed by after each";
}


void a_test_depending_on_before_each_hook(Test *test) {
	expect(test, some_before_each_value, is_string_equal_to("changed by before each"));
}


void a_test_depending_on_after_each(Test *test) {
	expect(test, some_after_each_value, is_string_equal_to("changed by after each"));
}


void add_suite_failing_suite(Suite *suite) {
	add_test(suite, some_failing_test);
}


void add_suite_passing_suite(Suite *suite) {
	add_test(suite, some_passing_test);
}


/* 
 * Tests
 */
void a_suite_should_fail(Test *test) {
	Suite *suite = create_suite("Failing suite.");
	set_formatter(suite, make_void_formatter());
	add_suite_failing_suite(suite);
	run_suite(suite);

	expect_equal(test, number_of_failed_tests(suite), 1);
}


void a_passing_suite_should_return_zero_status_code(Test *test) {
	Suite *suite = create_suite("Failing suite.");
	set_formatter(suite, make_void_formatter());
	add_suite_passing_suite(suite);

	int status_code = run_suite(suite);	
	expect_equal(test, status_code, 0);
}


void a_failing_suite_should_return_non_zero_status_code(Test *test) {
	Suite *suite = create_suite("Failing suite.");
	set_formatter(suite, make_void_formatter());
	add_suite_failing_suite(suite);

	int status_code = run_suite(suite);	
	expect_equal(test, status_code, 1);
}


void a_suite_should_report_successful_tests(Test *test) {
	Suite *suite = create_suite("Successful suite.");
	set_formatter(suite, make_void_formatter());
	add_suite_passing_suite(suite);
	run_suite(suite);
	expect_equal(test, number_of_passing_tests(suite), 1);
}


void a_suite_should_contain_passes_and_failures(Test *test) {
	Suite *suite = create_suite("Successful suite.");
	set_formatter(suite, make_void_formatter());
	add_test(suite, some_passing_test);
	add_test(suite, some_failing_test);
	run_suite(suite);
	expect_equal(test, number_of_passing_tests(suite), 1);
	expect_equal(test, number_of_failed_tests(suite), 1);
}


void a_before_each_hook_should_work(Test *test) {
	Suite *suite = create_suite("Successful suite.");
	set_formatter(suite, make_void_formatter());
	add_before_each(suite, before_each);
	add_test(suite, a_test_depending_on_before_each_hook);
	run_suite(suite);
	expect_equal(test, number_of_passing_tests(suite), 1);
}


void an_after_each_hook_should_work(Test *test) {
	Suite *suite = create_suite("Successful suite.");
	set_formatter(suite, make_void_formatter());
	add_after_each(suite, after_each);
	add_test(suite, some_passing_test);
	add_test(suite, a_test_depending_on_after_each);
	run_suite(suite);
	expect_equal(test, number_of_passing_tests(suite), 2);
}


int main(int argc, char *args[]) {
	Suite *suite = create_suite("cexpect suite");
	set_formatter(suite, make_dot_formatter(printf));
	add_test(suite, a_suite_should_fail);
	add_test(suite, a_suite_should_report_successful_tests);
	add_test(suite, a_suite_should_contain_passes_and_failures);
	add_test(suite, a_failing_suite_should_return_non_zero_status_code);
	add_test(suite, a_passing_suite_should_return_zero_status_code);
	add_test(suite, a_before_each_hook_should_work);
	add_test(suite, an_after_each_hook_should_work);

	start_cexpect(suite);
}
