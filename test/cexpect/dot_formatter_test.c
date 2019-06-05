#include "cexpect.h"
#include "cexpect_dot_formatter.h"

#include "cexpect_cmatchers.h"
#include <stdlib.h>
#include <string.h>


static char *printed_value = "something invalid";


void a_failing_test(Test *test) {
	expect(test, 1, is_int_equal_to(2));
}


int some_printing_function(const char *format, ...) {
	printed_value = (char *)format;

	return 0;
}
	



void a_dot_formatter_prints_dots_for_success(Test *test) {
	printed_value = "something invalid";
	printer_function_type printer = some_printing_function;
	Formatter *formatter = make_dot_formatter(printer);
	format_successful_test(formatter, test);
	expect(test, printed_value, is_string_equal_to("F"));
}


int main(int argc, char *args[]) {
	Suite *suite = make_suite("dot formatter");

	add_test(suite, a_dot_formatter_prints_dots_for_success);

	start_cexpect(suite);
}
