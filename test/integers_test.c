#include "cunit.h"
#include <stdio.h>
#include <stdbool.h>


void it_should_pass(Test *test) {
	assert_equal(test, 1, 1);
}


void add_suite_integer(Runner *runner) {
	add_test(runner, &it_should_pass);
}









