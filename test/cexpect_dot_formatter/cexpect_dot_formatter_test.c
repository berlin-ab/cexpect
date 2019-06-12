#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#include "cexpect.h"
#include "cexpect_dot_formatter.h"
#include "cexpect_cmatchers.h"
#include "cexpect_list.h"


static char *printed_message = "";
static List *printed_messages;


bool output_matches_string(char *expected_string) {
	for (ListItem *item = list_first(printed_messages); item; item = list_next(item)) {
		char *actual_value = (char *) list_value(item);
		if (strstr(actual_value, expected_string) != NULL)
			return true;
	}

	return false;
}


static int printer(const char *format, ...) {
	printed_message = (char *)format;
	return 0;
}


static int list_printer(const char *format, const char *message, const char *other_message, char *test_name, char *file_name, int line_number) {
	char *formatted_message = calloc(1000, sizeof(char));

	sprintf(
		formatted_message, 
		format, 
		message, 
		other_message,
		test_name,
		file_name, 
		line_number 
		);
	
//	printf("%s", formatted_message);
	add_to_list(printed_messages, (void *) formatted_message);
	
	return 0;
}


void before_each(void) {
	printed_messages = make_list();
	printed_message = "something invalid";
}


void a_failing_test_prints_an_F(Test *test) {
	Formatter *formatter = make_dot_formatter(printer);
	do_format_failure(formatter);
	
	expect(test, printed_message, is_string_equal_to("F"));
}


void a_passing_test_prints_a_dot(Test *test) {
	Formatter *formatter = make_dot_formatter(printer);
	do_format_success(formatter);
	
	expect(test, printed_message, is_string_equal_to("."));
}


void a_pending_test_prints_an_asterix(Test *test) {
	Formatter *formatter = make_dot_formatter(printer);
	do_format_pending(formatter);

	expect(test, printed_message, is_string_equal_to("*"));
}


void a_failing_test_prints_a_message_about_the_failing_test(Test *test) {
	bool contains_string;
	FailedTest failed_tests[1];
	FailedTest failed_test;
	failed_test.test_name = "some test name";
	failed_test.file_name = "some file name";
	failed_test.line_number = 1;
	failed_test.expected_value = "true";
	failed_test.actual_value = "false";
	failed_test.extra = list_printer;
	failed_tests[0] = failed_test;
	
	Formatter *formatter = make_dot_formatter(list_printer);
	do_format_summary(
		formatter,
		1,
		0,
		1,
		100,
		failed_tests
		);

	bool *expected  = calloc(1, sizeof(bool));

	// Test failure expectation message
	contains_string = output_matches_string("expected true, got false -- some test name -- some file name:1");
	*expected = contains_string;
	expect(test, &contains_string, is_true());

	// Final count summary report
	contains_string = output_matches_string("0 passed, 1 failed, 100 pending");
	*expected = contains_string;
	expect(test, &contains_string, is_true());
}


int main(int argsc, char *args[]) {
	Suite *suite = create_suite("Dot formatter");

	add_before_each(suite, before_each);
	add_test(suite, a_failing_test_prints_an_F);
	add_test(suite, a_passing_test_prints_a_dot);
	add_test(suite, a_failing_test_prints_a_message_about_the_failing_test);
	add_test(suite, a_pending_test_prints_an_asterix);

	start_cexpect(suite);
}