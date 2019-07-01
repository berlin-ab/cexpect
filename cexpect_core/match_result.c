#include <stdbool.h>


#include "cexpect_matchers.h"
#include "internal/memory_allocation.h"


struct MatchResultData {
	bool is_match;
	char *expected_message;
	char *actual_message;
};


MatchResult *make_match_result() {
	MatchResult *match_result = allocate_memory(1, sizeof(MatchResult));
	return match_result;
}


MatchResult *match_failed(char *expected_message, char *actual_message) {
	MatchResult *match_result = make_match_result();
	match_result->is_match = false;
	match_result->expected_message = expected_message;
	match_result->actual_message = actual_message;
	return match_result;
}


MatchResult *match_succeeded() {
	MatchResult *match_result = make_match_result();
	match_result->is_match = true;
	return match_result;
}


char *expected_message(MatchResult *result) {
	return result->expected_message;
}


char *actual_message(MatchResult *result) {
	return result->actual_message;
}


bool is_match(MatchResult *result) {
	return result->is_match;
}
