#include "cunit.h"


void some_failing_test(Test *test) {
    assert_equal(test, 1, 2);
}


void some_passing_test(Test *test) {
    assert_equal(test, 1, 1);
}


void add_suite_failing_suite(Suite *suite) {
    add_test(suite, some_failing_test);
}


void add_suite_passing_suite(Suite *suite) {
    add_test(suite, some_passing_test);
}


void a_suite_should_fail(Test *test) {
    Suite *suite = make_suite("Failing suite.");
    set_formatter(suite, make_void_formatter());
    add_suite_failing_suite(suite);
    run(suite);
	
    assert_equal(test, number_of_failed_tests(suite), 1);
}


void a_suite_should_report_successful_tests(Test *test) {
    Suite *suite = make_suite("Successful suite.");
    set_formatter(suite, make_void_formatter());
    add_suite_passing_suite(suite);
    run(suite);
    assert_equal(test, number_of_passing_tests(suite), 1);
}


void add_suite_cunit(Suite *suite) {
    add_test(suite, a_suite_should_fail);
    add_test(suite, a_suite_should_report_successful_tests);
}


int main(int args[]) {
    Suite *suite = make_suite("CUnit suite");
    set_formatter(suite, make_dot_formatter());
    add_suite_cunit(suite);
    run(suite);
}
