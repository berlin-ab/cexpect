#include "cexpect.h"
#include "cexpect_cmatchers.h"


void some_failing_test(Test *test) {
     expect(test, 1, is_int_equal_to(2));
}


void some_passing_test(Test *test) {
     expect(test, 1, is_int_equal_to(1));

     bool actual_value = true;
     expect(test, &actual_value, is_false());

     expect_equal(test, 100, 2);
}


int main(int argc, char *args[]) {
    Suite * suite = make_suite("Readme suite");
    add_test(suite, some_passing_test);
    add_test(suite, some_failing_test);
    cexpect_start(suite);
}









