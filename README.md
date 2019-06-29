# cexpect

A BDD-style testing framework for C

## Usage

```
#include "cexpect.h"
#include "cexpect_cmatchers.h"


void before_each() {
	// before each hook
}


void after_each() {
	// after each hook
}


void some_failing_test(Test *test) {
	expect(test, 1, is_int_equal_to(2));
}


void some_passing_test(Test *test) {
	expect(test, 1, is_int_equal_to(1));
}


void empty_tests_are_pending_tests(Test *test) {
	// marked as pending
}


void tests_can_be_marked_pending(Test *test) {
	// considered a pending test
	pending(test);

	// not considered a failing test
	expect(test, true, is_false());
}


int main(int argc, char *args[]) {
	Suite *suite = create_suite("Some suite name");
	add_before_each(suite, before_each);
	add_test(suite, some_failing_test);
	add_test(suite, some_passing_test);
	add_test(suite, empty_tests_are_pending_tests);
	add_test(suite, tests_can_be_marked_pending);
	add_after_each(suite, after_each);
	start_cexpect(suite);
}
```


## Matchers

### booleans

* is_true()
* is_false()


### primitives

* is_int_equal_to(expected)


### strings

* is_string_equal_to(expected)


### Creating your own matcher:

See `test/cexpect_list/` for an example of how to create domain specific matchers.

```clang
void a_list_starts_as_empty(Test *test) {
	List *list = make_list();

	expect(test, list, list_is_empty());
}
```

## Example output

```
make -s readme_test
Running suite: Readme suite
.F

Summary:

Ran 2 test(s).

1 passed, 1 failed, 0 pending



Makefile:48: recipe for target 'readme_test' failed
make: *** [readme_test] Error 1```
```

## Design goals


* BDD-style xUnit framework
* Extensible matchers
* Extensible formatting
* No global state.
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
* make Makefile more idiomatic
* matchers for all standard C primative data types
* colorized output for dot formatter
* report only one passing test per test function.

## Testing

```
make check
```