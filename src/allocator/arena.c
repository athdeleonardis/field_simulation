#include <stdlib.h>
#include <string.h>
#include "arena.h"

//
// 'arena.c' declarations
//

uint64_t _arena_capacity_resize(arena_t *, uint64_t capacity);

//
// 'arena.c' implementations
//

uint64_t _arena_capacity_resize(arena_t *arena, uint64_t capacity) {
    return (int)(capacity * arena->resize_factor);
}

//
// 'arena.h' implementations
//

void arena_initialize(arena_t *arena, uint64_t initial_capacity, float resize_factor) {
    arena->capacity = initial_capacity;
    arena->allocated = 0;
    arena->remaining = initial_capacity;
    arena->resize_factor = resize_factor;
    arena->data = (unsigned char *)malloc(sizeof(unsigned char));
}

void arena_empty(arena_t *arena) {
    arena->allocated = 0;
    arena->remaining = arena->capacity;
}

void arena_resize(arena_t *arena, uint64_t new_capacity) {
    unsigned char *data_new = (unsigned char *)malloc(new_capacity * sizeof(unsigned char));
    memcpy(data_new, arena->data, arena->allocated);
    free(arena->data);
    arena->data = data_new;
    arena->capacity = new_capacity;
}

uint64_t arena_allocate(arena_t *arena, size_t n_bytes) {
    if (arena->remaining < n_bytes) {
        int new_capacity = _arena_capacity_resize(arena, arena->capacity);
        while (new_capacity - arena->allocated < n_bytes) {
            new_capacity = _arena_capacity_resize(arena, new_capacity);
        }
        arena_resize(arena, new_capacity);
    }
    uint64_t allocation = arena->allocated;
    arena->allocated += n_bytes;
    arena->remaining = arena->capacity - arena->allocated;
    return allocation;
}

void *arena_allocation_get(arena_t *arena, uint64_t allocation_id) {
    return (void *)(arena->data + allocation_id);
}
