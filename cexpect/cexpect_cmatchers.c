#include <stdlib.h>
#include <stdio.h>

#include "cexpect.h"
#include "cexpect_cmatchers.h"


typedef struct MatchResultData {
    bool is_match;
    char *expected_message;
    char *actual_message;
} MatchResult;

  
struct MatcherData {
    MatchResult *(*match)(Matcher *matcher, void *actual_value);
    void *expected_value;
};


MatchResult *match_integers(Matcher *matcher, void *actual_value) {
    MatchResult *result = calloc(1, sizeof(MatchResult));
    result->is_match = (int)matcher->expected_value == (int)actual_value;

    if (result->is_match)
        return result;

    char *expected_message = calloc(100, sizeof(char));
    char *actual_message = calloc(100, sizeof(char)); 
    sprintf(expected_message, "%d", (int)matcher->expected_value);
    sprintf(actual_message, "%d", (int)actual_value);
    result->expected_message = expected_message;
    result->actual_message = actual_message;

    return result;
}


MatchResult *match_booleans(Matcher *matcher, void *actual_value) {
    bool expected_value = *(bool*)matcher->expected_value;
    bool actual = *(bool *)actual_value;

    MatchResult *result = calloc(1, sizeof(MatchResult));
    result->is_match = expected_value == actual;

    if (result->is_match)
        return result;
    
    char *expected_message = calloc(100, sizeof(char));
    char *actual_message = calloc(100, sizeof(char));
    sprintf(expected_message, "%s", (expected_value ? "true" : "false"));
    sprintf(actual_message, "%s", (actual ? "true" : "false"));
    result->expected_message = expected_message;
    result->actual_message = actual_message;
    return result;
}


void expect(Test *test, void *actual_value, Matcher *matcher) {
    MatchResult *result = matcher->match(matcher, actual_value);

    if (result->is_match) {
		pass_test(test);
    } else {
        fail_test(test,
		  result->expected_message,
		  result->actual_message);
    }
}


Matcher *is_false(void) {
    Matcher *matcher = calloc(1, sizeof(Matcher));
    bool *expected_value = calloc(1, sizeof(bool));
    *expected_value = false;
    matcher->match = match_booleans;
    matcher->expected_value = expected_value;
    return matcher;
}


Matcher *is_true(void) {
    Matcher *matcher = calloc(1, sizeof(Matcher));
    bool *expected_value = calloc(1, sizeof(bool));
    *expected_value = true;
    matcher->match = match_booleans;
    matcher->expected_value = ((void *) expected_value);
    return matcher;
}


Matcher *is_int_equal_to(void *expected_value) {
    Matcher *matcher = calloc(1, sizeof(Matcher));
    matcher->match = match_integers;
    matcher->expected_value = expected_value;
    return matcher;
}


Matcher *make_inspection_matcher(MatchResult *(*inspection_function)(Matcher *matcher, void *actual_value)) {
    Matcher *matcher = calloc(1, sizeof(Matcher));
    matcher->match = inspection_function;
    return matcher;
}


Matcher *make_comparison_matcher(MatchResult *(*comparison_function)(Matcher *matcher, void *actual_value), void *expected_value) {
	Matcher *matcher = calloc(1, sizeof(Matcher));
	matcher->match = comparison_function;
	matcher->expected_value = expected_value;
	return matcher;
}


MatchResult *make_match_result() {
	MatchResult *match_result = calloc(1, sizeof(MatchResult));
	return match_result;
}


MatchResult *match_failed(MatchResult* match_result, char *expected_message, char *actual_message) {
	match_result->is_match = false;
	match_result->expected_message = expected_message;
	match_result->actual_message = actual_message;
};


MatchResult *match_succeeded(MatchResult *match_result) {
	match_result->is_match = true;
}

void *get_expected_value(Matcher *matcher) {
	return matcher->expected_value;
}
