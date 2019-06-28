#ifndef CEXPECT_MATCH_RESULT_H
#define CEXPECT_MATCH_RESULT_H


#include <stdbool.h>

/*
 * get information about a match result:
 * 
 */
bool is_match(MatchResult *result);
char *expected_message(MatchResult *result);
char *actual_message(MatchResult *result);


#endif //CEXPECT_MATCH_RESULT_H
