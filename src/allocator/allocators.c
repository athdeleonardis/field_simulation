
#include "allocators.h"

//
// 'allocators.h' implementations
//

void allocator_arena(allocator_t *allocator, arena_t *arena) {
    allocator->data = arena;
    allocator->function_allocate = (uint64_t (*)(void *, size_t))arena_allocate;
    allocator->function_allocation_get = (void *(*)(void *, uint64_t))arena_allocation_get;
}
