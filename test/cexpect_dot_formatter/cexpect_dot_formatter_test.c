#include <string.h>


#include "cexpect.h"
#include "cexpect_dot_formatter.h"
#include "cexpect_cmatchers.h"
#include "cexpect_list.h"
#include "stdlib.h"

#include "stdio.h"
static char *printed_message = "";
static List *printed_messages;

bool
matches_string(char *expected_string);
static int printer(const char *format, ...) {
	printed_message = (char *)format;
	return 0;
}


static int list_printer(const char *format, const char *message, const char *other_message, char *file_name, int line_number) {
	char *formatted_message = calloc(1000, sizeof(char));
	sprintf(formatted_message, format, message, other_message, file_name, line_number);
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

bool matches_string(char *expected_string) {
	bool contains_string = false;
	
	for (ListItem *item = list_first(printed_messages); item; item = list_next(item))
	{
		char *string = (char *) list_value(item);

		if (strstr(string, expected_string) != NULL)
		{
			contains_string = true;
		}
	}
	return contains_string;
}
void a_failing_test_prints_a_message_about_the_failing_test(Test *test) {
	bool contains_string;
	FailedTest failed_tests[1];
	FailedTest failed_test;
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
		failed_tests
		);

	contains_string = matches_string("expected true, got false -- some file name:1");
	
	bool *expected  = calloc(1, sizeof(bool));
	*expected = contains_string;
	
	expect(test, &contains_string, is_true());
}

int main(int argsc, char *args[]) {
	Suite *suite = create_suite("Dot formatter");

	add_before_each(suite, before_each);
	add_test(suite, a_failing_test_prints_an_F);
	add_test(suite, a_passing_test_prints_a_dot);
	add_test(suite, a_failing_test_prints_a_message_about_the_failing_test);

	start_cexpect(suite);
}