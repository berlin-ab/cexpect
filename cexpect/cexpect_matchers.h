#ifndef CEXPECT_CEXPECT_MATCHERS_H
#define CEXPECT_CEXPECT_MATCHERS_H

#include "cexpect.h"


typedef struct MatcherData Matcher;
typedef struct MatchResultData MatchResult;


/*
 * for example:
 * 
 *   expect(test, true, is_true()); # passes
 *   expect(test, false, is_false()); # passes
 *   expect(test, true, is_false()); # fails
 *   
 */
extern void expect(Test *test, void *actual_value, Matcher *matcher);
extern void pass_test(Test *test);
extern void fail_test(Test *test, char *expected_value, char *actual_value);


/*
 * Extending matchers:
 */

/*
 * make_inspection_matcher: 
 * 
 *   Make matchers when the expected value is known
 *   
 *   for example:
 *      
 *      expect(test, list, is_empty_list());
 * 
 */
extern Matcher *make_inspection_matcher(MatchResult *(*inspection_function)(Matcher *matcher, void *actual_value));

/*
 * make_comparison_matcher:
 * 
 *   Make matchers to compare an actual value against an expected value:
 *   
 *   for example:
 *   
 *      expect(test, 1, is_int_equal_to(2));
 *      
 */
typedef MatchResult *(*comparison_function_type)(Matcher *matcher, void *actual_value);
extern Matcher *make_comparison_matcher(
	comparison_function_type comparison_function,
	void *expected_value);

/*
 * Communicate results from custom matchers:
 * 
 *  - Create a match result, and call either `match_succeeded()` or `match_failed()`
 *  - Use `get_expected_value()` to perform a comparison against the actual value.
 *  
 */
extern MatchResult *make_match_result();
extern MatchResult *match_succeeded(MatchResult *match_result);
extern MatchResult *match_failed(MatchResult* match_result, char *expected_message, char *actual_message);
extern void *get_expected_value(Matcher *matcher);

#endif //CEXPECT_CEXPECT_MATCHERS_H