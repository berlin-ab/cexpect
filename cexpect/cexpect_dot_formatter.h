#ifndef CEXPECT_DOT_FORMATTER_H
#define CEXPECT_DOT_FORMATTER_H

#include "cexpect.h"

typedef int (*printer_function_type)(const char* format, ...);
extern Formatter *make_dot_formatter(printer_function_type printer);

#endif //CEXPECT_DOT_FORMATTER_H
