#ifndef CEXPECT_H
#define CEXPECT_H


#include "stddef.h"


#include "cexpect_formatter.h"
#include "cexpect_matchers.h"
#include "cexpect_memory_allocation_types.h"
#include "cexpect_suite_types.h"


/*
 * for example:
 * 
 *   expect(test, true, is_true()); # passes
 *   expect(test, false, is_false()); # passes
 *   expect(test, true, is_false()); # fails
 *   
 */
#define expect(test, actual_value, matcher)  \
	make_expectation(test, actual_value, matcher, (char *)__FUNCTION__, __LINE__, __FILE__)


extern void make_expectation(
	Test *test, 
	void *actual_value,
	Matcher *matcher, 
	const char *test_name, 
	int line_number, 
	char *file_name);

/*
 * Mark a test as pending:
 *
 * - to mean not yet implemented and should not count as a failure.
 *
 */
extern void pending(Test *test);


/*
 * Manually mark a test as a failure explicitly.
 *
 */
#define failed(test, message) \
	do { \
		make_explicit_failure(test, message, (char *)__FUNCTION__, __LINE__, __FILE__); \
		return; \
	} while(0)


extern void make_explicit_failure(Test *test,
	const char *message,
	const char *test_name,
	int line_number,
	char *file_name);


/*
 * create a new suite instance:
 *
 */
extern Suite *create_suite(char *suite_name);


/*
 * make a new suite:
 * 
 * allows for:
 *
 * - custom formatters
 * - custom memory allocation functions:
 *     * matching signature of calloc
 *     * matching signature of free
 *
 */
extern Suite *make_suite(
	char *suite_name,
	Formatter *formatter,
	allocate_memory_func allocate_memory,
	free_memory_func free);


/*
 * Free suite:
 *
 *  - clean up data created by the suite, and also
 *    the data for the formatter
 *
 */
extern void free_suite(Suite *suite);


/*
 * Add tests to a suite:
 * 
 */
extern void add_test(Suite *suite, test_function_type test_function);



/*
 * Add a function to run before each test:
 * 
 */
extern void add_before_each(Suite *suite, void (*before_each_function)());


/*
 * Add a function to run before each test:
 * 
 */
extern void add_after_each(Suite *suite, void (*after_each_function)());


/*
 * change formatter the suite uses:
 * 
 *   default = dot_formatter
 *   
 */
extern void set_formatter(Suite *suite, Formatter *formatter);


/*
 * run suite without exiting:
 * 
 */
extern int run_suite(Suite *suite);


/*
 * run suite and exit with appropriate status code:
 * 
 */
extern void start_cexpect(Suite *suite);


/* 
 * exposed for tests 
 */
extern int number_of_tests(Suite *suite);
extern int number_of_failed_tests(Suite *suite);
extern int number_of_passing_tests(Suite *suite);
extern int number_of_pending_tests(Suite *suite);


#endif // CEXPECT_H
