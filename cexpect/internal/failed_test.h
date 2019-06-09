#ifndef CEXPECT_FAILED_TEST_H
#define CEXPECT_FAILED_TEST_H


/*
 * make an instance that stores data about a failed test:
 * 
 */
FailedTest *make_failed_test(
	char *expected_value, 
	char *actual_value, 
	int line_number, 
	char *file_name);


#endif //CEXPECT_FAILED_TEST_H
