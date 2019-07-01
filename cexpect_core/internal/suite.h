#ifndef CEXPECT_SUITE_H
#define CEXPECT_SUITE_H


#include "list.h"


/*
 * update how the suite should be formatted:
 * 
 */
extern void set_formatter_for_suite(Suite *suite, Formatter *formatter);


/*
 * update how many tests have passed:
 * 
 */
extern void increment_passing_tests(Suite *suite);
extern void increment_pending_tests(Suite *suite);


/*
 * set hooks:
 * 
 */
extern void add_before_each_to_suite(Suite *suite, void (*before_each_function)());
extern void add_after_each_to_suite(Suite *suite, void (*before_each_function)());


/*
 * perform hooks: 
 * 
 */
extern void before_each(Suite *suite);
extern void after_each(Suite *suite);



/*
 * fetch data about the suite:
 * 
 */
extern List *get_tests(Suite *suite);
extern char *get_suite_name(Suite *suite);
extern List *get_failed_tests(Suite *suite);
extern void populate_failed_tests(Suite *suite, FailedTest *failed_tests);


#endif //CEXPECT_SUITE_H
