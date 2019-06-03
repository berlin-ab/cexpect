#include <stdlib.h>
#include <stdio.h>

#include "cexpect.h"
#include "cexpect_cmatchers.h"

#include "list.h"
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


int main(int argc, char *args[]) {
	Suite *suite = make_suite("List test");
	add_test(suite, a_list_starts_as_empty);
	add_test(suite, a_list_starts_with_size_zero);
	add_test(suite, a_list_is_no_longer_empty_after_adding_to_list);
	start_cexpect(suite);
}
