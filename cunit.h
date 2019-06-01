#include <stdbool.h>

typedef struct FormatterData Formatter;
typedef struct SuiteData Suite;
typedef struct TestData Test;

// Tests
extern void add_test(Suite *suite, void (*test_function)(Test *test));
extern void pass_test(Test *test);
extern void fail_test(Test *test);

// Suites
extern void run_suite(Suite *suite);


// Suites
extern Suite *make_suite(char *suite_name);
extern void run(Suite *suite);
extern int number_of_failed_tests(Suite *suite);
extern int number_of_passing_tests(Suite *suite);
extern void set_formatter(Suite *suite, Formatter *formatter);


// Formatters
extern Formatter *make_void_formatter();
extern Formatter *make_dot_formatter();


// Int matchers
extern void assert_equal(Test *test, int expected_value, int actual_value);
