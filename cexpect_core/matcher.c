#include <stdlib.h>
#include <stdbool.h>


#include "cexpect_matchers.h"


#include "internal/matcher.h"
#include "internal/matcher_result.h"


struct MatcherData {
	MatchResult *(*match)(Matcher *matcher, void *actual_value);
	void *expected_value;
};


/*
 * base expectation:
 * 
 */
void expect(Test *test, void *actual_value, Matcher *matcher) {
	MatchResult *result = matcher->match(matcher, actual_value);

	if (is_match(result)) {
		pass_test(test);
	} else {
		fail_test(test, 
			expected_message(result), 
			actual_message(result));
	}
}

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


void *get_expected_value(Matcher *matcher) {
	return matcher->expected_value;
}


