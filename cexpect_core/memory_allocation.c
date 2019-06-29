#include "cexpect.h"
#include "internal/memory_allocation.h"

static allocate_memory_func allocate_memory_internal;

/*
 * Allow a custom memory allocation mechanism:
 *
 */
void set_memory_allocation(allocate_memory_func func) {
	allocate_memory_internal = func;
}

void *allocate_memory(size_t num, size_t size) {
	return allocate_memory_internal(num, size);
}

