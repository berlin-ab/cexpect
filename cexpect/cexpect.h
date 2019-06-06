#ifndef CEXPECT_H
#define CEXPECT_H


typedef struct SuiteData Suite;
typedef struct TestData Test;


#include "cexpect_formatter.h"


#define add_test(suite, test_function) add_test_to_suite(suite, test_function, __LINE__, __FILE__)
typedef void (*test_function_type)(Test *test);

/*
 * create a new suite instance:
 * 
 */
extern Suite *create_suite(char *suite_name);

/*
 * Add tests to a suite:
 * 
 */
extern void add_test_to_suite(Suite *suite, test_function_type test_function, int line_number, char *file_name);



/*
 * Add a function to run before each test:
 * 
 */
extern void add_before_each(Suite *suite, void (*before_each_function)());


/*
 * Add a function to run before each test:
 * 
 */
extern void add_after_each(Suite *suite, void (*after_each_function)());


/*
 * run suite without exiting:
 * 
 */
extern int run_suite(Suite *suite);

/*
 * change formatter the suite uses:
 * 
 *   default = dot_formatter
 *   
 */
extern void set_formatter(Suite *suite, Formatter *formatter);
extern void start_cexpect(Suite *suite);


/* 
 * exposed for tests 
 */
extern int number_of_tests(Suite *suite);
extern int number_of_failed_tests(Suite *suite);
extern int number_of_passing_tests(Suite *suite);


#endif // CEXPECT_H