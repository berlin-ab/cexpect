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

## Design goals

* xunit-like framework with extensible matchers, similar to hamcrest
* extensible reporting and formatting
* code coverage reporting enabled
* self-tested
* No magic. This includes #import of c files, or use of macros for assertions.


## Planned improvements

* individual test failure detailed reporting in summary
* dynamic test list (currently hard coded array)
* test-anything-protocol output formatter
* lcov/gcov
* make Makefile more idiomatic


## Testing

```
make -s test
```