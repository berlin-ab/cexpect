#include <stdlib.h>


#include "cexpect.h"

/*
 * Allow a custom memory allocation mechanism:
 *
 */
allocate_memory_func allocate_memory = calloc;
