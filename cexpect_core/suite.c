#include <stdlib.h>


#include "cexpect_list.h"
#include "cexpect.h"
#include "cexpect_formatter.h"

#include "internal/suite.h"


struct SuiteData {
	char *name;
	Cexpect_List *tests;
	Cexpect_List *failed_tests;
	int number_of_passing_tests;
	int number_of_pending_tests;
	Formatter *formatter;
	void (*before_each)();
	void (*after_each)();
};


static void default_before_each() {}
static void default_after_each() {}


/*
 * Suite
 */
Suite *make_suite(char *suite_name, Formatter *formatter) {
	Suite *suite = calloc(1, sizeof(Suite));
	suite->formatter = formatter;
	suite->name = suite_name;
	suite->tests = make_list();
	suite->failed_tests = make_list();
	suite->before_each = default_before_each;
	suite->after_each = default_after_each;

	return suite;
}


void set_formatter_for_suite(Suite *suite, Formatter *formatter) {
	suite->formatter = formatter;
}


void add_before_each_to_suite(Suite *suite, void (*before_each_function)()) {
	suite->before_each = before_each_function;
}


void add_after_each_to_suite(Suite *suite, void (*after_each_function)()) {
	suite->after_each = after_each_function;
}


char *get_suite_name(Suite *suite) {
	return suite->name;
}


int number_of_tests(Suite *suite) {
	return list_size(suite->tests);
}


int number_of_failed_tests(Suite *suite) {
	return list_size(suite->failed_tests);
}


int number_of_passing_tests(Suite *suite) {
	return suite->number_of_passing_tests;
}


int number_of_pending_tests(Suite *suite) {
	return suite->number_of_pending_tests;
}


void before_each(Suite *suite) {
	suite->before_each();
}


void after_each(Suite *suite) {
	suite->after_each();
}


void increment_passing_tests(Suite *suite) {
	suite->number_of_passing_tests++;
}


void increment_pending_tests(Suite *suite) {
	suite->number_of_pending_tests++;
}


Formatter *get_formatter(Suite *suite) {
	return suite->formatter;
}


Cexpect_List *get_tests(Suite *suite) {
	return suite->tests;
}


Cexpect_List *get_failed_tests(Suite *suite) {
	return suite->failed_tests;
}
