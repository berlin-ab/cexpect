#include "cexpect.h"
#include "internal/memory_allocation.h"


static allocate_memory_func allocate_memory_internal;
static free_memory_func deallocate_memory_internal;


/*
 * Allow a custom memory allocation mechanism:
 *
 */
void set_memory_allocation(
	allocate_memory_func func,
	free_memory_func free) {
	allocate_memory_internal = func;
	deallocate_memory_internal = free;
}


void *allocate_memory(size_t num, size_t size) {
	return allocate_memory_internal(num, size);
}


void deallocate_memory(void *pointer) {
	deallocate_memory_internal(pointer);
}
