#include "cunit.h"


void some_failing_test(Test *test) {
    assert_equal(test, 1, 2);
}


void some_passing_test(Test *test) {
    assert_equal(test, 1, 1);
}


void add_suite_failing_suite(Runner *runner) {
    add_test(runner, some_failing_test);
}


void add_suite_passing_suite(Runner *runner) {
    add_test(runner, some_passing_test);
}


void a_suite_should_fail(Test *test) {
    Runner *runner = make_runner();
    set_formatter(runner, make_void_formatter());
    add_suite_failing_suite(runner);
    run(runner);
	
    assert_equal(test, number_of_failed_tests(runner), 1);
}


void a_suite_should_report_successful_tests(Test *test) {
    Runner *runner = make_runner();
    set_formatter(runner, make_void_formatter());
    add_suite_passing_suite(runner);
    run(runner);
    assert_equal(test, number_of_passing_tests(runner), 1);
}


void add_suite_cunit(Runner *runner) {
    add_test(runner, a_suite_should_fail);
    add_test(runner, a_suite_should_report_successful_tests);
}


int main(int args[]) {
    Runner *runner = make_runner();
    set_formatter(runner, make_dot_formatter());
    add_suite_cunit(runner);
    run(runner);
}
