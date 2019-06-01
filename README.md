# cUnit

A testing framework for C inspired by hamcrest

## Usage

```
#include "cunit.h"
#include "cunit_cmatchers.h"

void some_test(Test *test) {
     assert_that(test, 1, is_int_equal_to(2));
}

int main(int args[]) {
    Suite *suite = make_suite();
    set_formatter(suite, make_dot_formatter());
    add_test(suite, some_test);
    run(suite);
}
```

## Testing

```
make -s test
```