#ifndef CEXPECT_DOT_FORMATTER_H
#define CEXPECT_DOT_FORMATTER_H

#include "cexpect_formatter.h"


typedef int (*printer_function_type)(const char *format, ...);


extern Formatter *make_dot_formatter(
	printer_function_type new_printer,
	allocate_formatter_memory_func calloc_func,
	free_formatter_func free_func);


#endif //CEXPECT_DOT_FORMATTER_H
