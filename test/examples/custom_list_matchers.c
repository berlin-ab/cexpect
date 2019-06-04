#include <stdlib.h>
#include <stdio.h>

#include "custom_list_matchers.h"

#include "cexpect_list.h"


/*
 * list matcher comparisons
 */
MatchResult *is_list_empty(Matcher *matcher, void *list) {
	MatchResult *match_result = make_match_result();

	int actual_size = list_size(list);

	if (actual_size == 0) {
		match_succeeded(match_result);
		return match_result;
	}

	char *expected_message = calloc(100, sizeof(char));
	char *actual_message = calloc(100, sizeof(char));

	sprintf(expected_message, "list size of 0");
	sprintf(actual_message, "actual size of %d", actual_size);

	match_failed(match_result, expected_message, actual_message);
	return match_result;
}


MatchResult *list_size_equals(Matcher *matcher, void *actual_value) {
	MatchResult *match_result = make_match_result();

	List *list = (List *)actual_value;
	int expected_size = *(int*)get_expected_value(matcher);
	int actual_size = list_size(list);

	if (actual_size == expected_size) {
		match_succeeded(match_result);
		return match_result;
	}

	char *expected_message = calloc(100, sizeof(char));
	sprintf(expected_message, "list to have size = %d", expected_size);

	char *actual_message = calloc(100, sizeof(char));
	sprintf(actual_message, "size = %d", actual_size);

	match_failed(match_result, expected_message, actual_message);
	return match_result;
}


/*
 * List matchers
 */
Matcher *list_is_empty() {
	return make_inspection_matcher(is_list_empty);
}


Matcher *list_has_size(void *size) {
	return make_comparison_matcher(list_size_equals, size);
}

