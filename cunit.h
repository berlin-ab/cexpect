#include <stdbool.h>

typedef struct FormatterData Formatter;
typedef struct RunnerData Runner;
typedef struct SuiteData Suite;
typedef struct TestData Test;

// Tests
extern void add_test(Runner *runner, void (*test_function)(Test *test));
extern void pass_test(Test *test);
extern void fail_test(Test *test);

// Suites
extern void run_suite(Suite *suite);


// Runners
extern Runner *make_runner();
extern void run(Runner *runner);
extern int number_of_failed_tests(Runner *runner);
extern int number_of_passing_tests(Runner *runner);
extern void set_formatter(Runner *runner, Formatter *formatter);


// Formatters
extern Formatter *make_void_formatter();
extern Formatter *make_dot_formatter();


// Int matchers
extern void assert_equal(Test *test, int expected_value, int actual_value);
