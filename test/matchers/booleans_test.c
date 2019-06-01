#include <stdio.h>

#include "cunit.h"
#include "cunit_cmatchers.h"


void is_false_with_false_statement(Test *test) {
    bool actual_value = false;
    assert_that(test, &actual_value, is_false());
}


void is_false_with_true_statement(Test *test) {
    bool actual_value = true;
    assert_that(test, &actual_value, is_false());
}

void is_true_with_true_statement(Test *test) {
    bool actual_value = true;
    assert_that(test, &actual_value, is_true());
}


void is_true_with_false_statement(Test *test) {
    bool actual_value = false;
    assert_that(test, &actual_value, is_true());
}


void is_false_should_pass_when_given_a_false_statement(Test *test) {
    Suite *suite = make_suite("suite");
    set_formatter(suite, make_void_formatter());
    add_test(suite, is_false_with_false_statement);
    run_suite(suite);
    
    assert_that(test, number_of_passing_tests(suite), is_int_equal_to(1));
}


void is_false_should_fail_when_given_a_true_statement(Test *test) {
    Suite *suite = make_suite("suite");
    set_formatter(suite, make_void_formatter());
    add_test(suite, is_false_with_true_statement);
    run_suite(suite);
    
    assert_that(test, number_of_failed_tests(suite), is_int_equal_to(1));
}
 

void is_true_should_pass_when_given_a_true_statement(Test *test) {
    Suite *suite = make_suite("suite");
    set_formatter(suite, make_void_formatter());
    add_test(suite, is_true_with_true_statement);
    run_suite(suite);

    assert_that(test, number_of_passing_tests(suite), is_int_equal_to(1));
}


void is_true_should_fail_when_given_a_false_statement(Test *test) {
    Suite *suite = make_suite("suite");
    set_formatter(suite, make_void_formatter());
    add_test(suite, is_true_with_false_statement);
    run_suite(suite);

    assert_that(test, number_of_failed_tests(suite), is_int_equal_to(1));
}

int main(int args[]) {
    Suite *suite = make_suite("Booleans suite");
    add_test(suite, is_false_should_pass_when_given_a_false_statement);
    add_test(suite, is_false_should_fail_when_given_a_true_statement);
    add_test(suite, is_true_should_pass_when_given_a_true_statement);
    add_test(suite, is_true_should_fail_when_given_a_false_statement);
    cunit_start(suite);
}
