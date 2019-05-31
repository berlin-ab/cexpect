#include <stdbool.h>

typedef struct FormatterData Formatter;
typedef struct RunnerData Runner;
typedef struct SuiteData Suite;
typedef struct TestData Test;
typedef struct MatcherData Matcher;


extern void fail_test(Test *test);
extern void add_test(Runner *runner, void (*test_function)(Test *test));
extern void run_suite(Suite *suite);
extern void run(Runner *runner);
extern Runner *make_runner();
extern int number_of_failed_tests(Runner *runner);
extern int number_of_passing_tests(Runner *runner);
extern void assert_equal(Test *test, int expected_value, int actual_value);
extern Formatter *make_void_formatter();
extern Formatter *make_dot_formatter();
extern void set_formatter(Runner *runner, Formatter *formatter);

extern void assert_that(Test *test, void *actual_value, Matcher *matcher);
extern Matcher *is_int_equal_to(void *expected_value);
