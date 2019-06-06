#ifndef CEXPECT_TEST_H
#define CEXPECT_TEST_H

extern Test *make_test(Suite *suite, test_function_type test_function, int line_number, char *file_name);
extern void perform_test(Test *test);
extern int get_line_number_for_test(Test *test);
extern char *get_file_name_for_test(Test *test);
extern Suite *get_suite_for_test(Test *test);

#endif //CEXPECT_TEST_H
