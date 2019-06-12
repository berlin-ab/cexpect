#include <stdlib.h>

#include "cexpect_formatter.h"
#include "internal/test.h"
#include "internal/failed_test.h"


FailedTest *make_failed_test(char *test_name, char *expected_value, char *actual_value, int line_number, char *file_name) {
	FailedTest *failed_test = calloc(1, sizeof(FailedTest));
	failed_test->test_name = test_name;
	failed_test->expected_value = expected_value;
	failed_test->actual_value = actual_value;
	failed_test->line_number = line_number;
	failed_test->file_name = file_name;
	return failed_test;
}
