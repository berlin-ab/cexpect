#include "cexpect_internal.h"
#include "cexpect_cmatchers.h"
#include "cexpect_void_formatter.h"

Suite *run_example_suite(test_function_type test_function) {
	Suite *suite = create_suite("suite");
	set_formatter(suite, make_void_formatter());
	add_test(suite, test_function);
	run_suite(suite);
	return suite;
}


void a_failing_test(Test *test) {
	expect(test, "a", is_string_equal_to("b"));
}


void a_passing_test(Test *test) {
	expect(test, "a", is_string_equal_to("a"));
}

void a_partially_matching_test_from_the_expected(Test *test) {
	expect(test, "a", is_string_equal_to("abc"));
}


void a_partially_matching_test_from_the_actual(Test *test) {
	expect(test, "abc", is_string_equal_to("a"));
}


void a_string_fails_when_not_equal(Test *test) {
	Suite *suite = run_example_suite(a_failing_test);

	expect(test, number_of_failed_tests(suite), is_int_equal_to(1));
	expect(test, number_of_passing_tests(suite), is_int_equal_to(0));
}


void a_string_matches_when_equal(Test *test) {
	Suite *suite = run_example_suite(a_passing_test);

	expect(test, number_of_passing_tests(suite), is_int_equal_to(1));
	expect(test, number_of_failed_tests(suite), is_int_equal_to(0));
}


void a_string_partially_matching_should_not_pass(Test *test) {
	Suite *suite = run_example_suite(a_partially_matching_test_from_the_expected);
	
	expect(test, number_of_failed_tests(suite), is_int_equal_to(1));
	expect(test, number_of_passing_tests(suite), is_int_equal_to(0));

	suite = run_example_suite(a_partially_matching_test_from_the_actual);

	expect(test, number_of_failed_tests(suite), is_int_equal_to(1));
	expect(test, number_of_passing_tests(suite), is_int_equal_to(0));
}


int main(int argc, char *args[]) {
	Suite *suite = create_suite("string matchers");
	add_test(suite, a_string_fails_when_not_equal);
	add_test(suite, a_string_matches_when_equal);
	add_test(suite, a_string_partially_matching_should_not_pass);
	start_cexpect(suite);
}