#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cexpect_internal.h"
#include "cexpect_cmatchers.h"

#include "cexpect_list.h"
#include "custom_list_matchers.h"


/* 
 * Tests
 */
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


void a_list_can_iterate(Test *test) {
	List *list = make_list();

	add_to_list(list, "1");
	add_to_list(list, "2");
	add_to_list(list, "3");

	int actual_size = 0;

	for (ListItem *item = list_first(list); item; item = list_next(item)) {
		actual_size++;
	}

	expect(test, actual_size, is_int_equal_to(3));
}


void a_list_can_store_and_retrieve_values(Test *test) {
	List *list = make_list();

	add_to_list(list, "abc");
	
	char *found_value = "";

	for (ListItem *item = list_first(list); item; item = list_next(item)) {
		found_value = (char *)list_value(item);
	}
	
	expect(test, strcmp(found_value, "abc"), is_int_equal_to(0));
}


int main(int argc, char *args[]) {
	Suite *suite = create_suite("List test");
	add_test(suite, a_list_starts_as_empty);
	add_test(suite, a_list_starts_with_size_zero);
	add_test(suite, a_list_is_no_longer_empty_after_adding_to_list);
	add_test(suite, a_list_can_iterate);
	add_test(suite, a_list_can_store_and_retrieve_values);
	start_cexpect(suite);
}
