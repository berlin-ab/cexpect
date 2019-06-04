#include <stdbool.h>
#include "cexpect.h"


typedef struct MatcherData Matcher;
typedef struct MatchResultData MatchResult;

// assertions
extern void expect(Test *test, void *actual_value, Matcher *matcher);
extern Matcher *make_inspection_matcher(MatchResult *(*inspection_function)(Matcher *matcher, void *actual_value));
extern Matcher *make_comparison_matcher(MatchResult *(*comparison_function)(Matcher *matcher, void *actual_value), void *expected_value);

// results
extern MatchResult *make_match_result();
extern MatchResult *match_succeeded(MatchResult *match_result);
extern MatchResult *match_failed(MatchResult* match_result, char *expected_message, char *actual_message);
extern void *get_expected_value(Matcher *matcher);


// matchers for primative types
extern Matcher *is_int_equal_to(void *expected_value);


// matchers for stdbool
extern Matcher *is_false(void);
extern Matcher *is_true(void);

