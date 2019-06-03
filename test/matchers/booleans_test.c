#include <stdio.h>

#include "cexpect.h"
#include "cexpect_cmatchers.h"


void is_false_with_false_statement(Test *test) {
    bool actual_value = false;
    expect(test, &actual_value, is_false());
}


void is_false_with_true_statement(Test *test) {
    bool actual_value = true;
    expect(test, &actual_value, is_false());
}

void is_true_with_true_statement(Test *test) {
    bool actual_value = true;
    expect(test, &actual_value, is_true());
}


void is_true_with_false_statement(Test *test) {
    bool actual_value = false;
    expect(test, &actual_value, is_true());
}


Suite *run_example_suite(void (*test_function)(Test *test)) {
    Suite *suite = make_suite("suite");
    set_formatter(suite, make_void_formatter());
    add_test(suite, test_function);
    run_suite(suite);
    return suite;
}


void is_false_should_pass_when_given_a_false_statement(Test *test) {
    Suite *suite = run_example_suite(is_false_with_false_statement);
    
    expect(test, number_of_passing_tests(suite), is_int_equal_to(1));
}


void is_false_should_fail_when_given_a_true_statement(Test *test) {
    Suite *suite = run_example_suite(is_false_with_true_statement);
    
    expect(test, number_of_failed_tests(suite), is_int_equal_to(1));
}
 

void is_true_should_pass_when_given_a_true_statement(Test *test) {
    Suite *suite = run_example_suite(is_true_with_true_statement);

    expect(test, number_of_passing_tests(suite), is_int_equal_to(1));
}


void is_true_should_fail_when_given_a_false_statement(Test *test) {
    Suite *suite = run_example_suite(is_true_with_false_statement);

    expect(test, number_of_failed_tests(suite), is_int_equal_to(1));
}

int main(int args[]) {
    Suite *suite = make_suite("Booleans suite");
    add_test(suite, is_false_should_pass_when_given_a_false_statement);
    add_test(suite, is_false_should_fail_when_given_a_true_statement);
    add_test(suite, is_true_should_pass_when_given_a_true_statement);
    add_test(suite, is_true_should_fail_when_given_a_false_statement);
    cexpect_start(suite);
}
