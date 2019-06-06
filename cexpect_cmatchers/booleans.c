#include <stdlib.h>
#include <stdio.h>


#include "cexpect.h"
#include "cexpect_cmatchers.h"


/*
 * boolean matchers:
 * 
 */
MatchResult *match_booleans(Matcher *matcher, void *actual_value) {
	bool expected_value = *(bool*)get_expected_value(matcher);
	bool actual = *(bool *)actual_value;

	MatchResult *result = make_match_result();
	bool is_match = expected_value == actual;

	if (is_match)
		return match_succeeded(result);

	char *expected_message = calloc(100, sizeof(char));
	char *actual_message = calloc(100, sizeof(char));
	sprintf(expected_message, "%s", (expected_value ? "true" : "false"));
	sprintf(actual_message, "%s", (actual ? "true" : "false"));
	return match_failed(result, expected_message, actual_message);;
}


Matcher *is_false(void) {
	bool *expected_value = calloc(1, sizeof(bool));
	*expected_value = false;

	return make_comparison_matcher(match_booleans, expected_value);
}


Matcher *is_true(void) {
	bool *expected_value = calloc(1, sizeof(bool));
	*expected_value = true;
	return make_comparison_matcher(match_booleans, expected_value);
}
