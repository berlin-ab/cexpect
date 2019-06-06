#ifndef CEXPECT_FAILED_TEST_H
#define CEXPECT_FAILED_TEST_H

FailedTest *make_failed_test(Test *test, char *expected_value, char *actual_value);

#endif //CEXPECT_FAILED_TEST_H
