#include <stdbool.h>
#include "cexpect.h"


typedef struct MatcherData Matcher;
typedef struct MatcherResultData MatcherResult;

// assertions
extern void expect(Test *test, void *actual_value, Matcher *matcher);
extern Matcher *make_inspection_matcher(struct MatcherResult (*inspection_function)(Matcher *matcher, void *actual_value));


// matchers for primative types
extern Matcher *is_int_equal_to(void *expected_value);


// matchers for stdbool
extern Matcher *is_false(void);
extern Matcher *is_true(void);

