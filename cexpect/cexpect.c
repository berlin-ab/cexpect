#include <stdlib.h>
#include <stdio.h>


#include "cexpect.h"
#include "cexpect_dot_formatter.h"


Suite *create_suite(char *suite_name) {
	return make_suite(suite_name, make_dot_formatter(&printf), calloc);
}


void start_cexpect(Suite *suite) {
	int status_code = run_suite(suite);

	exit(status_code);
}

