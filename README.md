# cUnit

A testing framework for C inspired by hamcrest

## Usage

```
#include "cunit.h"
#include "cunit_matchers.h"

void some_test(Test *test) {
     assert_that(test, 1, is_int_equal_to(2));
}

int main(int args[]) {
    Runner * runner = make_runner();
    add_test(runner, some_test);
    run(runner);
}
```

## Testing

```
make test
```