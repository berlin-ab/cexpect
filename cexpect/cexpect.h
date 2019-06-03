typedef struct FormatterData Formatter;
typedef struct SuiteData Suite;
typedef struct TestData Test;

// Tests
extern void add_test(Suite *suite, void (*test_function)(Test *test));
extern void pass_test(Test *test);
extern void fail_test(Test *test, char *expected_value, char *actual_value);

// Suites
extern int run_suite(Suite *suite);
extern Suite *make_suite(char *suite_name);
extern int number_of_failed_tests(Suite *suite);
extern int number_of_passing_tests(Suite *suite);
extern void set_formatter(Suite *suite, Formatter *formatter);


// Formatters
extern Formatter *make_void_formatter();
extern Formatter *make_dot_formatter();


// Int matchers
extern void expect_equal(Test *test, int expected_value, int actual_value);


// Runner
extern void cexpect_start(Suite *suite);
