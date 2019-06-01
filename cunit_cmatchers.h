#include "cunit.h"

typedef struct MatcherData Matcher;

extern void assert_that(Test *test, void *actual_value, Matcher *matcher);
extern Matcher *is_int_equal_to(void *expected_value);
extern Matcher *is_false(void);
extern Matcher *is_true(void);
