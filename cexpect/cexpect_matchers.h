#ifndef CEXPECT_CEXPECT_MATCHERS_H
#define CEXPECT_CEXPECT_MATCHERS_H


#include "cexpect_memory_allocation_types.h"



typedef struct MatchResultData MatchResult;
typedef struct MatcherData Matcher;


/*
 * Create a custom matcher:
 *
 * 1. Decide if you are making a comparison matcher or an inspection matcher (defined below)
 * 2. Implement a function that takes a matcher and the actual value as an argument.
 *    - find the expected value by calling get_expected_value()
 *    - compare the expected value against the actual value
 *    - use allocate_memory() to construct expected and actual messages
 *    - call match_succeeded() or match_failed() from within the function
 *
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
extern Matcher *make_inspection_matcher(
	MatchResult *(*inspection_function)(Matcher *matcher, void *actual_value));

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
extern MatchResult *match_succeeded();
extern MatchResult *match_failed(char *expected_message, char *actual_message);
extern void *get_expected_value(Matcher *matcher);


#endif //CEXPECT_CEXPECT_MATCHERS_H
