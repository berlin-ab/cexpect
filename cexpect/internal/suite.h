#ifndef CEXPECT_SUITE_H
#define CEXPECT_SUITE_H

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
extern void increment_passing_tests(Suite *suite);

#endif //CEXPECT_SUITE_H
