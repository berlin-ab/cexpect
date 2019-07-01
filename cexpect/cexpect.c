#include <stdlib.h>
#include <stdio.h>


#include "cexpect.h"
#include "cexpect_dot_formatter.h"


Suite *create_suite(char *suite_name) {
	Formatter *formatter = make_dot_formatter(&printf, calloc, free);
	return make_suite(suite_name, formatter, calloc, free);
}


void start_cexpect(Suite *suite) {
	int status_code = run_suite(suite);

	free_suite(suite);

	exit(status_code);
}

