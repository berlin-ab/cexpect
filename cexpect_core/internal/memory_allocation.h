#ifndef CEXPECT_INTERNAL_MEMORY_ALLOCATION_H
#define CEXPECT_INTERNAL_MEMORY_ALLOCATION_H


#include "cexpect.h"


void set_memory_allocation(allocate_memory_func func, free_memory_func free);
void deallocate_memory(void *pointer);


#endif //CEXPECT_INTERNAL_MEMORY_ALLOCATION_H
