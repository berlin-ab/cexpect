#include "cunit_cmatchers.h"
#include <stdlib.h>


struct MatcherData {
  bool (*match)(Matcher *matcher, void *actual_value);
  void *expected_value;
};


bool match_integers(Matcher *matcher, void *actual_value) {
  return (int)matcher->expected_value == (int)actual_value;
}


bool match_booleans(Matcher *matcher, void *actual_value) {
  bool expected_value = *(bool*)matcher->expected_value;
  bool actual = *(bool *)actual_value;

  return expected_value == actual;
}


void assert_that(Test *test, void *actual_value, Matcher *matcher) {
    bool result = matcher->match(matcher, actual_value);

    if (result) {
	pass_test(test);
    } else {
	fail_test(test);
    }
}


Matcher *is_false(void) {
    Matcher *matcher = calloc(1, sizeof(Matcher));
    bool *expected_value = calloc(1, sizeof(bool));
    *expected_value = false;
    matcher->match = match_booleans;
    matcher->expected_value = expected_value;
    return matcher;
}


Matcher *is_true(void) {
    Matcher *matcher = calloc(1, sizeof(Matcher));
    bool *expected_value = calloc(1, sizeof(bool));
    *expected_value = true;
    matcher->match = match_booleans;
    matcher->expected_value = ((void *) expected_value);
    return matcher;
}


Matcher *is_int_equal_to(void *expected_value) {
    Matcher *matcher = calloc(1, sizeof(Matcher));
    matcher->match = match_integers;
    matcher->expected_value = expected_value;
    return matcher;
}

