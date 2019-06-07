#ifndef CEXPECT_MATCHER_RESULT_H
#define CEXPECT_MATCHER_RESULT_H


#include <stdbool.h>


bool is_match(MatchResult *result);
char *expected_message(MatchResult *result);
char *actual_message(MatchResult *result);


#endif //CEXPECT_MATCHER_RESULT_H
