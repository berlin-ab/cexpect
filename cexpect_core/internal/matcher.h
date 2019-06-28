#ifndef CEXPECT_MATCHER_H
#define CEXPECT_MATCHER_H

/*
 * execute a matcher and get back a result:
 * 
 */
extern MatchResult *perform_match(Matcher *matcher, void *actual_value);


#endif //CEXPECT_MATCHER_H
