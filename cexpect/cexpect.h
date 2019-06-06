#ifndef CEXPECT_H
#define CEXPECT_H

typedef struct SuiteData Suite;
typedef struct TestData Test;
typedef struct FormatterData Formatter;

#define add_test(suite, test_function) add_test_to_suite(suite, test_function, __LINE__, __FILE__)
typedef void (*test_function_type)(Test *test);
extern void add_test_to_suite(Suite *suite, test_function_type test_function, int line_number, char *file_name);
extern int run_suite(Suite *suite);
extern void set_formatter(Suite *suite, Formatter *formatter);
extern void start_cexpect(Suite *suite);

#endif // CEXPECT_H