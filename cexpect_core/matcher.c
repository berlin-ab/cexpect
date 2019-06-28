#include <stdbool.h>


#include "cexpect_matchers.h"

#include "internal/test.h"
#include "internal/matcher.h"
#include "internal/match_result.h"
#include "internal/memory_allocation.h"


struct MatcherData {
	MatchResult *(*match)(Matcher *matcher, void *actual_value);
	void *expected_value;
};


/* 
 * library extension functions:
 * 
 */
Matcher *make_inspection_matcher(MatchResult *(*inspection_function)(Matcher *matcher, void *actual_value)) {
	Matcher *matcher = allocate_memory(1, sizeof(Matcher));
	matcher->match = inspection_function;
	return matcher;
}


Matcher *make_comparison_matcher(MatchResult *(*comparison_function)(Matcher *matcher, void *actual_value), void *expected_value) {
	Matcher *matcher = allocate_memory(1, sizeof(Matcher));
	matcher->match = comparison_function;
	matcher->expected_value = expected_value;
	return matcher;
}

MatchResult *perform_match(Matcher *matcher, void *actual_value) {
	return matcher->match(matcher, actual_value);
}


void *get_expected_value(Matcher *matcher) {
	return matcher->expected_value;
}


