#include <string.h>


#include "cexpect_cmatchers.h"


/* 
 * string matchers:
 * 
 */
MatchResult *string_matcher(Matcher *matcher, void *actual_value) {
	char *actual = (char *)actual_value;
	char *expected = (char *)get_expected_value(matcher);

	MatchResult *result = make_match_result();

	if (strcmp(actual, expected) == 0) {
		return match_succeeded(result);
	}

	return match_failed(result, expected, actual);
}


Matcher *is_string_equal_to(char *expected_string) {
	return make_comparison_matcher(
		string_matcher,
		expected_string);
}
