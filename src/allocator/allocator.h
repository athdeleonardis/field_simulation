#ifndef ALLOCATOR
#define ALLOCATOR

#include <stddef.h>
#include <stdint.h>

typedef struct allocator {
    uint64_t (*function_allocate)(void *data, size_t n_bytes);
    void *(*function_allocation_get)(void *data, uint64_t id);
    void *data;
} allocator_t;

uint64_t allocate(allocator_t *allocator, size_t n_bytes);
void *allocation_get(allocator_t *allocator, uint64_t id);

#endif
