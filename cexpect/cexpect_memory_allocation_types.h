#ifndef CEXPECT_CEXPECT_MEMORY_ALLOCATION_TYPES_H
#define CEXPECT_CEXPECT_MEMORY_ALLOCATION_TYPES_H


#include "stddef.h"


typedef void* (*allocate_memory_func)(size_t num, size_t size);
typedef void (*free_memory_func)(void *pointer);


void *allocate_memory(size_t num, size_t size);


#endif //CEXPECT_CEXPECT_MEMORY_ALLOCATION_TYPES_H
