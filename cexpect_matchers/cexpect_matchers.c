#include <stdlib.h>


#include "cexpect_cmatchers.h"


struct MatchResultData {
	bool is_match;
	char *expected_message;
	char *actual_message;
};


struct MatcherData {
	MatchResult *(*match)(Matcher *matcher, void *actual_value);
	void *expected_value;
};


/* 
 * library extension functions:
 * 
 */
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
	return match_result;
};


MatchResult *match_succeeded(MatchResult *match_result) {
	match_result->is_match = true;
	return match_result;
}

void *get_expected_value(Matcher *matcher) {
	return matcher->expected_value;
}


/*
 * base expectation:
 * 
 */
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

void set_match_failure(MatchResult *result, char *expected_message, char *actual_message) {
	result->expected_message = expected_message;
	result->actual_message = actual_message;
}
