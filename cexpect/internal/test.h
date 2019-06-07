#ifndef CEXPECT_TEST_H
#define CEXPECT_TEST_H


#include "cexpect_suite_types.h"


/*
 * make a new test:
 * 
 */
extern Test *make_test(Suite *suite, test_function_type test_function, int line_number, char *file_name);


/*
 * perform a test: 
 * 
 */
extern void perform_test(Test *test);


/*
 * update the results of an expectation:
 * 
 */
extern void pass_test(Test *test);
extern void fail_test(Test *test, char *expected_value, char *actual_value);


/*
 * get information about a test:
 * 
 */
extern int get_line_number_for_test(Test *test);
extern char *get_file_name_for_test(Test *test);
extern Suite *get_suite_for_test(Test *test);


#endif //CEXPECT_TEST_H
