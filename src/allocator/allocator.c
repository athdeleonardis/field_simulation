#include "allocator.h"

uint64_t allocate(allocator_t *allocator, size_t n_bytes) {
    return allocator->function_allocate(allocator->data, n_bytes);
}

void *allocation_get(allocator_t *allocator, uint64_t id) {
    return allocator->function_allocation_get(allocator->data, id);
}
