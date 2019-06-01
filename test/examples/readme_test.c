#include "cunit.h"
#include "cunit_cmatchers.h"


void some_failing_test(Test *test) {
     expect(test, 1, is_int_equal_to(2));
}


void some_passing_test(Test *test) {
     expect(test, 1, is_int_equal_to(1));
}


int main(int args[]) {
    Suite * suite = make_suite("Readme suite");
    add_test(suite, some_passing_test);
    add_test(suite, some_failing_test);
    cunit_start(suite);
}
