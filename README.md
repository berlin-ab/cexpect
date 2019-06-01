# cUnit

A testing framework for C inspired by hamcrest

## Usage

```
#include "cunit.h"
#include "cunit_cmatchers.h"

void some_failing_test(Test *test) {
     assert_that(test, 1, is_int_equal_to(2));
}

void some_passing_test(Test *test) {
     assert_that(test, 1, is_int_equal_to(1));
}

int main(int args[]) {
    Suite *suite = make_suite();
    add_test(suite, some_failing_test);
    add_test(suite, some_passing_test);
    cunit_start(suite);
}
```

```
make -s readme_test
Running suite: Readme suite
.F

Summary:

Ran 2 test(s).

1 passed, 1 failed



Makefile:48: recipe for target 'readme_test' failed
make: *** [readme_test] Error 1```
```

## Testing

```
make -s test
```