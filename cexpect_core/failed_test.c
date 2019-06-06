#include <stdlib.h>


#include "cexpect_list.h"
#include "cexpect.h"
#include "cexpect_formatter.h"
#include "internal/test.h"


FailedTest *make_failed_test(Test *test, char *expected_value, char *actual_value) {
	FailedTest *failed_test = calloc(1, sizeof(FailedTest));
	failed_test->expected_value = expected_value;
	failed_test->actual_value = actual_value;
	failed_test->line_number = get_line_number_for_test(test);
	failed_test->file_name = get_file_name_for_test(test);
	return failed_test;
}
