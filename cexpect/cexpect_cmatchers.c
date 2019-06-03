#include "cexpect_cmatchers.h"
#include <stdlib.h>
#include <stdio.h>

struct MatchResult {
    bool is_match;
    char *expected_message;
    char *actual_message;
};

  
struct MatcherData {
    struct MatchResult (*match)(Matcher *matcher, void *actual_value);
    void *expected_value;
};


struct MatchResult match_integers(Matcher *matcher, void *actual_value) {
    struct MatchResult result;
    result.is_match = (int)matcher->expected_value == (int)actual_value;

    if (result.is_match)
        return result;

    char *expected_message = calloc(100, sizeof(char));
    char *actual_message = calloc(100, sizeof(char)); 
    sprintf(expected_message, "%d", (int)matcher->expected_value);
    sprintf(actual_message, "%d", (int)actual_value);
    result.expected_message = expected_message;
    result.actual_message = actual_message;

    return result;
}


struct MatchResult match_booleans(Matcher *matcher, void *actual_value) {
    bool expected_value = *(bool*)matcher->expected_value;
    bool actual = *(bool *)actual_value;

    struct MatchResult result;
    result.is_match = expected_value == actual;

    if (result.is_match)
        return result;
    
    char *expected_message = calloc(100, sizeof(char));
    char *actual_message = calloc(100, sizeof(char));
    sprintf(expected_message, "%s", (expected_value ? "true" : "false"));
    sprintf(actual_message, "%s", (actual ? "true" : "false"));
    result.expected_message = expected_message;
    result.actual_message = actual_message;
    return result;
}


void expect(Test *test, void *actual_value, Matcher *matcher) {
    struct MatchResult result = matcher->match(matcher, actual_value);

    if (result.is_match) {
	pass_test(test);
    } else {
        fail_test(test,
		  result.expected_message,
		  result.actual_message);
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

