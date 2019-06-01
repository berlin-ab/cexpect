#include "cunit.h"
#include <stdbool.h>


typedef struct MatcherData Matcher;


// assertions
extern void expect(Test *test, void *actual_value, Matcher *matcher);


// matchers for primative types
extern Matcher *is_int_equal_to(void *expected_value);


// matchers for stdbool
extern Matcher *is_false(void);
extern Matcher *is_true(void);

