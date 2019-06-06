#include <stdbool.h>


#include "cexpect_matchers.h"

/*
 * 
 * Provided matchers
 * 
 */

/* 
 * primitive types:
 * 
 *   expect(test, 1, is_int_equal_to(1)); # passes
 *   expect(test, 1, is_int_equal_to(2)); # fails
 *   
 */
extern Matcher *is_int_equal_to(void *expected_value);


/*
 * string matchers:
 */
extern Matcher *is_string_equal_to(char *expected_string);

/*
 * boolean matchers:
 * 
 *   expect(test, true, is_true()); # passes
 *   expect(test, false, is_false()); # passes
 *   expect(test, true, is_false()); # fails
 *   
 */
extern Matcher *is_false(void);
extern Matcher *is_true(void);

