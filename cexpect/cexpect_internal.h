#ifndef CEXPECT_INTERNAL_H
#define CEXPECT_INTERNAL_H

#include "cexpect_list.h"
#include "cexpect.h"



// Tests
extern void perform_test(Test *test);
extern int get_line_number_for_test(Test *test);
extern char *get_file_name_for_test(Test *test);
extern Suite *get_suite_for_test(Test *test);

extern Test *make_test(Suite *suite, test_function_type test_function, int line_number, char *file_name);

// Suites
extern Suite *make_suite(char *suite_name, Formatter *formatter);
extern void set_formatter_for_suite(Suite *suite, Formatter *formatter);
extern void add_before_each_to_suite(Suite *suite, void (*before_each_function)());
extern void add_after_each_to_suite(Suite *suite, void (*before_each_function)());
extern void before_each(Suite *suite);
extern void after_each(Suite *suite);
extern List *get_tests(Suite *suite);
extern char *get_suite_name(Suite *suite);
extern Formatter *get_formatter(Suite *suite);
extern List *get_failed_tests(Suite *suite);


// Failed tests
FailedTest *make_failed_test(Test *test, char *expected_value, char *actual_value);


// Formatters
void perform_format_start(Formatter *formatter, Suite *suite);
void perform_format_success(Formatter *formatter, Test *test);
void perform_format_fail(Formatter *formatter, Test *test);
void perform_format_summary(Formatter *formatter, Suite *suite);


// Int matchers
extern void expect_equal(Test *test, int expected_value, int actual_value);



#endif //CEXPECT_INTERNAL_H
