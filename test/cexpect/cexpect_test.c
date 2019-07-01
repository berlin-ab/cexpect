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
	expect(test, expected_value, is_int_equal_to(actual_value));
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


void a_test_without_an_expectation(Test *test) {
	// no expectations made.
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


void a_test_without_an_assertion_should_be_considered_pending(Test *test) {
	Suite *suite = create_suite("Successful suite.");
	set_formatter(suite, make_void_formatter());
	add_test(suite, a_test_without_an_expectation);
	run_suite(suite);
	expect_equal(test, number_of_pending_tests(suite), 1);
}


void a_test_pending_test_with_an_expectation(Test *test) {
	pending(test);

	bool *expected_value = calloc(1, sizeof(bool));
	*expected_value = true;
	
	expect(test, expected_value, is_false());
}


void a_pending_test_before_an_expectation_should_not_be_a_failure(Test *test) {
	Suite *suite = create_suite("Successful suite.");
	set_formatter(suite, make_void_formatter());
	add_test(suite, a_test_pending_test_with_an_expectation);
	
	run_suite(suite);
	
	expect(test, number_of_pending_tests(suite), is_int_equal_to(1));
	expect(test, number_of_failed_tests(suite), is_int_equal_to(0));
}


void *allocate_memory_spy(size_t num, size_t size) {
	return calloc(num, size);
}


#include "../../cexpect_core/internal/list.h"


List *free_memory_spy_list = NULL;


void free_memory_spy(void *pointer) {
	if (free_memory_spy_list == NULL)
		free_memory_spy_list = make_list();

	add_to_list(free_memory_spy_list, pointer);

	free(pointer);
}

int void_printer(const char *format, ...) {
	return 0;
}


bool list_includes_address(List *list, void *address) {
	bool list_includes_formatter_address = false;

	for(ListItem *list_item = list_first(list);
         list_item;
         list_item = list_next(list_item)){

		if (list_value(list_item) == address)
			list_includes_formatter_address = true;
	}

	return list_includes_formatter_address;
}


void a_formatter_is_freed_along_with_the_suite(Test *test) {
	Formatter *formatter = make_dot_formatter(
		void_printer, 
		allocate_memory_spy, 
		free_memory_spy);
	
	Formatter *other_formatter = make_dot_formatter(
		void_printer, 
		allocate_memory_spy, 
		free_memory_spy);
	
	Suite *suite = make_suite("some suite", 
		formatter, 
		allocate_memory_spy, 
		free_memory_spy);

	free_suite(suite);

	bool list_includes_formatter_address = list_includes_address(
		free_memory_spy_list, 
		formatter);
	
	expect(test, &list_includes_formatter_address, is_true());

	bool list_includes_other_formatter_address = list_includes_address(
		free_memory_spy_list,
		other_formatter);
	
	expect(test, &list_includes_other_formatter_address, is_false());
}


int main(int argc, char *args[]) {
	Suite *suite = create_suite("cexpect suite");
	set_formatter(suite, make_dot_formatter(printf, calloc, free));
	add_test(suite, a_suite_should_fail);
	add_test(suite, a_suite_should_report_successful_tests);
	add_test(suite, a_suite_should_contain_passes_and_failures);
	add_test(suite, a_failing_suite_should_return_non_zero_status_code);
	add_test(suite, a_passing_suite_should_return_zero_status_code);
	add_test(suite, a_before_each_hook_should_work);
	add_test(suite, an_after_each_hook_should_work);
	add_test(suite, a_test_without_an_assertion_should_be_considered_pending);
	add_test(suite, a_pending_test_before_an_expectation_should_not_be_a_failure);
	add_test(suite, a_formatter_is_freed_along_with_the_suite);
	
	start_cexpect(suite);
}
