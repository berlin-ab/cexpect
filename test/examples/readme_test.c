#include "cexpect.h"
#include "cexpect_cmatchers.h"


void some_failing_test(Test *test) {
     expect(test, 1, is_int_equal_to(2));
}


void some_passing_test(Test *test) {
     expect(test, 1, is_int_equal_to(1));
}


int main(int argc, char *args[]) {
    Suite * suite = create_suite("Readme suite");
    add_test(suite, some_passing_test);
    add_test(suite, some_failing_test);
    start_cexpect(suite);
}









