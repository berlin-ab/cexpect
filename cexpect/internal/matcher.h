#ifndef CEXPECT_MATCHER_H
#define CEXPECT_MATCHER_H


extern void pass_test(Test *test);
extern void fail_test(Test *test, char *expected_value, char *actual_value);


#endif //CEXPECT_MATCHER_H
