#include <stdio.h>


#include "cexpect_cmatchers.h"


/* 
 * primitive matchers:
 * 
 */
static MatchResult *match_integers(Matcher *matcher, void *actual_value) {
	MatchResult *result = make_match_result();

	bool is_match = (int)get_expected_value(matcher) == (int)actual_value;

	if (is_match)
		return match_succeeded(result);

	char *expected_message = allocate_memory(100, sizeof(char));
	char *actual_message = allocate_memory(100, sizeof(char));
	snprintf(expected_message, 100, "%d", (int)get_expected_value(matcher));
	snprintf(actual_message, 100, "%d", (int)actual_value);
	return match_failed(result, expected_message, actual_message);
}


Matcher *is_int_equal_to(void *expected_value) {
	return make_comparison_matcher(match_integers, expected_value);
}
