#include <stdlib.h>

#include "cexpect.h"
#include "cexpect_formatter.h"
#include "cexpect_cmatchers.h"
#include "custom_list_matchers.h"


#include "../../cexpect_core/internal/list.h"


static char *expected_message = "something invalid";
static char *expected_success_message = "something invalid";
static char *expected_failure_message = "something invalid";
static char *actual_message = "something invalid";
static bool was_pending;


void before_each(void) {
	expected_message = "something invalid";
	actual_message = "something invalid";
	was_pending = false;
}


void capture_format_failure(void *extra) {
	expected_failure_message = "WAT";
}


void capture_format_success(void *extra) {
	expected_success_message = "success";
}


void capture_format_summary(
	int number_of_tests,
	int number_of_successful_tests,
	int number_of_failing_tests,
	int number_of_pending_tests,
	FailedTest failed_tests[],
	void *extra) {
	expected_message = failed_tests[0].expected_value;
	actual_message = failed_tests[0].actual_value;
}


void capture_format_start(char *suite_name, void *extra) {}


void capture_format_pending(void *extra) {
	was_pending = true;
}


Formatter *make_capturing_formatter() {
	return make_formatter(
		capture_format_failure,
		capture_format_success,
		capture_format_pending,
		capture_format_summary,
		capture_format_start,
		NULL
		);
}


void a_pending_test(Test *test) {
}


void a_failing_test(Test *test) {
	Cexpect_List *list = make_list();
	
	int *expected_size_pointer = calloc(1, sizeof(int));
	*expected_size_pointer = 1;
	
	expect(test, list, list_has_size(expected_size_pointer));
}


void a_failing_test_for_list_is_empty(Test *test) {
	Cexpect_List *list = make_list();
	add_to_list(list, 1);

	expect(test, list, list_is_empty());
}


void a_successful_test(Test *test) {
	Cexpect_List *list = make_list();
	expect(test, list, list_is_empty());
}


void a_failing_test_for_list_size_provides_diagnostics(Test *test) {
	Suite *suite = create_suite("Cexpect_List matchers test");
	set_formatter(suite, make_capturing_formatter());
	add_test(suite, a_failing_test);
	
	run_suite(suite);
	
	expect(test, expected_message, is_string_equal_to("list to have size = 1"));
	expect(test, actual_message, is_string_equal_to("size = 0"));
}


void a_failing_test_for_list_is_empty_provides_diagnostics(Test *test) {
	Suite *suite = create_suite("Cexpect_List matchers test");
	set_formatter(suite, make_capturing_formatter());
	add_test(suite, a_failing_test_for_list_is_empty);

	run_suite(suite);

	expect(test, expected_failure_message, is_string_equal_to("WAT"));
	expect(test, expected_message, is_string_equal_to("list size of 0"));
	expect(test, actual_message, is_string_equal_to("actual size of 1"));
}


void a_successful_test_for_list_size_captures_diagnostics(Test *test) {
	Suite *suite = create_suite("Cexpect_List matchers test");
	set_formatter(suite, make_capturing_formatter());

	add_test(suite, a_successful_test);
	run_suite(suite);
	
	expect(test, expected_success_message, is_string_equal_to("success"));
}


void a_pending_test_captures_pending(Test *test) {
	Suite *suite = create_suite("Cexpect_List matchers test");
	set_formatter(suite, make_capturing_formatter());
	
	add_test(suite, a_pending_test);
	
	run_suite(suite);
	
	bool *was_pending_pointer = calloc(1, sizeof(bool));
	*was_pending_pointer = was_pending;
	
	expect(test, was_pending_pointer, is_true());
}


void a_non_pending_test_does_not_capture_pending(Test *test) {
	Suite *suite = create_suite("Cexpect_List matchers test");
	set_formatter(suite, make_capturing_formatter());

	add_test(suite, a_failing_test);

	run_suite(suite);

	bool *was_pending_pointer = calloc(1, sizeof(bool));
	*was_pending_pointer = was_pending;

	expect(test, was_pending_pointer, is_false());
}


int main(int argc, char *args[])
{
	Suite *suite = create_suite("Cexpect_List matchers test");

	add_before_each(suite, before_each);
	add_test(suite, a_successful_test_for_list_size_captures_diagnostics);
	add_test(suite, a_failing_test_for_list_size_provides_diagnostics);
	add_test(suite, a_failing_test_for_list_is_empty_provides_diagnostics);
	add_test(suite, a_pending_test_captures_pending);
	add_test(suite, a_non_pending_test_does_not_capture_pending);

	start_cexpect(suite);
}
