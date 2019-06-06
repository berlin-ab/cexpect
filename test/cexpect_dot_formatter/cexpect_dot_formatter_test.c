#include "cexpect.h"
#include "cexpect_dot_formatter.h"
#include <string.h>
#include "cexpect_cmatchers.h"

static char *printed_message = "something invalid";


static int printer(const char *format, ...) {
	printed_message = (char *)format;
	return 0;
} 


void before_each(void) {
	printed_message = "something invalid";
}


void a_failing_test_prints_an_F(Test *test) {
	Formatter *formatter = make_dot_formatter(printer);
	do_format_failure(formatter);
	
	expect(test, printed_message, is_string_equal_to("F"));
}


void a_passing_test_prints_a_dot(Test *test) {
	Formatter *formatter = make_dot_formatter(printer);
	do_format_success(formatter);
	
	expect(test, printed_message, is_string_equal_to("."));
}


int main(int argsc, char *args[]) {
	Suite *suite = create_suite("Dot formatter");

	add_before_each(suite, before_each);
	add_test(suite, a_failing_test_prints_an_F);
	add_test(suite, a_passing_test_prints_a_dot);

	start_cexpect(suite);
}