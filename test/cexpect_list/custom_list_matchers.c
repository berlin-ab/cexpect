#include <stdio.h>


// Dependencies
#include "cexpect_matchers.h"
#include "../../cexpect_core/internal/list.h"


// Implements
#include "custom_list_matchers.h"


/*
 * list matcher comparisons
 */
MatchResult *is_list_empty(Matcher *matcher, void *list) {
	int actual_size = list_size(list);

	if (actual_size == 0) {
		return match_succeeded();
	}

	char *expected_message = allocate_memory(100, sizeof(char));
	char *actual_message = allocate_memory(100, sizeof(char));

	snprintf(expected_message, 100, "list size of 0");
	snprintf(actual_message, 100, "actual size of %d", actual_size);

	return match_failed(expected_message, actual_message);
}


MatchResult *list_size_equals(Matcher *matcher, void *actual_value) {
	List *list = (List *)actual_value;
	int expected_size = *(int*)get_expected_value(matcher);
	int actual_size = list_size(list);

	if (actual_size == expected_size) {
		return match_succeeded();
	}

	char *expected_message = allocate_memory(100, sizeof(char));
	snprintf(expected_message, 100, "list to have size = %d", expected_size);

	char *actual_message = allocate_memory(100, sizeof(char));
	snprintf(actual_message, 100, "size = %d", actual_size);

	return match_failed(expected_message, actual_message);
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

