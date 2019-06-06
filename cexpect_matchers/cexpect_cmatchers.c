#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "cexpect.h"
#include "cexpect_cmatchers.h"


/* 
 * primitive matchers:
 * 
 */
MatchResult *match_integers(Matcher *matcher, void *actual_value) {
    MatchResult *result = make_match_result();
    
    bool is_match = (int)get_expected_value(matcher) == (int)actual_value;

    if (is_match)
        return match_succeeded(result);

    char *expected_message = calloc(100, sizeof(char));
    char *actual_message = calloc(100, sizeof(char)); 
    sprintf(expected_message, "%d", (int)get_expected_value(matcher));
    sprintf(actual_message, "%d", (int)actual_value);
    return match_failed(result, expected_message, actual_message);
}


Matcher *is_int_equal_to(void *expected_value) {
	return make_comparison_matcher(match_integers, expected_value);
}


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


