#include "cunit.h"
#include "cmatchers.h"


void it_should_pass(Test *test) {
    assert_that(test, 1, is_int_equal_to(1));
}


void add_suite_integer(Runner *runner) {
    add_test(runner, it_should_pass);
}


int main(int args[]) {
    Runner *runner = make_runner();
    set_formatter(runner, make_dot_formatter());
    add_suite_integer(runner);
    run(runner);
}

