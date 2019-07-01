#include <stdio.h>


#include "cexpect_cmatchers.h"


/*
 * boolean matchers:
 * 
 */
static MatchResult *match_booleans(Matcher *matcher, void *actual_value) {
	bool expected_value = *(bool*)get_expected_value(matcher);
	bool actual = *(bool *)actual_value;
	bool is_match = expected_value == actual;

	if (is_match)
		return match_succeeded();

	char *expected_message = allocate_memory(100, sizeof(char));
	char *actual_message = allocate_memory(100, sizeof(char));
	snprintf(expected_message, 100, "%s", (expected_value ? "true" : "false"));
	snprintf(actual_message, 100, "%s", (actual ? "true" : "false"));
	return match_failed(expected_message, actual_message);
}


Matcher *is_false(void) {
	bool *expected_value = allocate_memory(1, sizeof(bool));
	*expected_value = false;

	return make_comparison_matcher(match_booleans, expected_value);
}


Matcher *is_true(void) {
	bool *expected_value = allocate_memory(1, sizeof(bool));
	*expected_value = true;
	return make_comparison_matcher(match_booleans, expected_value);
}
