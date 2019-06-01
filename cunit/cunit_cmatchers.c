#include "cunit_cmatchers.h"
#include <stdlib.h>


struct MatcherData {
  bool (*match)(Matcher *matcher, void *actual_value);
  void *expected_value;
};


bool match_integers(Matcher *matcher, void *actual_value) {
  return (int)matcher->expected_value == (int)actual_value;
}


void assert_that(Test *test, void *actual_value, Matcher *matcher) {
    bool result = matcher->match(matcher, actual_value);

    if (result) {
	pass_test(test);
    } else {
	fail_test(test);
    }
}


Matcher *is_int_equal_to(void *expected_value) {
  Matcher *matcher = calloc(1, sizeof(Matcher));
  matcher->match = match_integers;
  matcher->expected_value = expected_value;
  return matcher;
}

