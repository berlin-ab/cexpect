#include "cexpect.h"
#include "cexpect_cmatchers.h"
#include "cexpect_dot_formatter.h"


void it_should_pass(Test *test) {
    expect(test, 1, is_int_equal_to(1));
}


void add_suite_integer(Suite *suite) {
    add_test(suite, it_should_pass);
}


int main(int argc, char *args[]) {
    Suite *suite = make_suite("Matchers suite");
    add_suite_integer(suite);
    start_cexpect(suite);
}









