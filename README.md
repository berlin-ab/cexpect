# cexpect

A testing framework for C inspired by hamcrest

## Usage

```
#include "cexpect.h"
#include "cexpect_cmatchers.h"


void some_failing_test(Test *test) {
    expect(test, 1, is_int_equal_to(2));
}


void some_passing_test(Test *test) {
    expect(test, 1, is_int_equal_to(1));
}


int main(int argc, char *args[]) {
    Suite *suite = make_suite();
    add_test(suite, some_failing_test);
    add_test(suite, some_passing_test);
    start_cexpect(suite);
}
```


## Matchers

* is_int_equal_to
* is_true
* is_false


### Creating your own matcher:

See `test/cexpect_list/` for an example of how to create domain specific matchers.

```clang
	List *list = make_list();

	expect(test, list, list_is_empty());
```

## Example output

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


* xUnit-like framework similar to hamcrest
* Extensible matchers
* Extensible formatting
* Self-tested. No additional frameworks.
* No magic. 
* Should be useable in isolated unit tests and also in integrated system tests.


## Features


* Ability to custom matchers 
* Ability to create custom formatters
* Dot formatting by default
* Individual test failure detailed reporting in summary


## Planned improvements

* test-anything-protocol output formatter
* lcov/gcov
* make Makefile more idiomatic
* matchers for all standard C primative data types
* colorized output
* report only one passing test per test function.


## Testing

```
make test
```