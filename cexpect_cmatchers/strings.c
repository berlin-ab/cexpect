#include <string.h>


#include "cexpect_cmatchers.h"


/* 
 * string matchers:
 * 
 */
static MatchResult *string_matcher(Matcher *matcher, void *actual_value) {
	char *actual = (char *)actual_value;
	char *expected = (char *)get_expected_value(matcher);

	if (strcmp(actual, expected) == 0) {
		return match_succeeded();
	}

	return match_failed(expected, actual);
}


Matcher *is_string_equal_to(char *expected_string) {
	return make_comparison_matcher(
		string_matcher,
		expected_string);
}
