#include "cunit.h"
#include "cunit_cmatchers.h"


void some_test(Test *test) {
     assert_that(test, 1, is_int_equal_to(2));
}


int main(int args[]) {
    Runner * runner = make_runner();
    set_formatter(runner, make_dot_formatter());
    add_test(runner, some_test);
    run(runner);
}
