#include <stdlib.h>
#include <stdio.h>

#include "cexpect.h"
#include "cexpect_cmatchers.h"

typedef struct ListItemData ListItem;

struct ListItemData {
	ListItem *next;
	void *value;
};

typedef struct ListData {
	ListItem *first;
} List;

/*
 * List Functions
 */
List *make_list(void) {
	List *list = calloc(1, sizeof(List));
	list->first = NULL;
	return list;
}


void add_to_list(List *list, void *value) {
	ListItem *item = calloc(1, sizeof(ListItem));
	item->next = NULL;
	item->value = value;
	
	if (list->first == NULL) {
		list->first = item;
		return;
	}

	ListItem *list_item;
	
	for(list_item = list->first; list_item->next != NULL; list_item = list_item->next) {}
	
	list_item->next = item;
}


int list_size(List *list) {
	int size = 1;

	if (list->first == NULL) 
		return 0;

	ListItem *list_item;

	for(list_item = list->first; list_item->next != NULL; list_item = list_item->next) {
		size++;
	}

	return size;
}


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


void a_list_starts_as_empty(Test *test) {
    List *list = make_list();

    expect(test, list, list_is_empty());
}


void a_list_is_no_longer_empty_after_adding_to_list(Test *test) {
	List *list = make_list();
	char *something = "a";
	
	add_to_list(list, something);
	int *expected_size = calloc(1, sizeof(int));
	*expected_size = 1;
	
	expect(test, list, list_has_size(expected_size));
}


void a_list_starts_with_size_zero(Test *test) {
	List *list = make_list();

	int *expected_size = calloc(1, sizeof(int));
	*expected_size = 0;

	expect(test, list, list_has_size(expected_size));
}


int main(int argc, char *args[]) {
  Suite *suite = make_suite("List test");
  add_test(suite, a_list_starts_as_empty);
  add_test(suite, a_list_starts_with_size_zero);
  add_test(suite, a_list_is_no_longer_empty_after_adding_to_list);
  start_cexpect(suite);
}
