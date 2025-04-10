#ifndef ARENA
#define ARENA

#include "stdint.h"

typedef struct arena {
    uint64_t capacity;
    uint64_t allocated;
    uint64_t remaining;
    float resize_factor;
    unsigned char *data;
} arena_t;

void arena_initialize(arena_t *, uint64_t initial_capacity, float resize_factor);
void arena_empty(arena_t *);
void arena_resize(arena_t *, uint64_t new_capacity);
uint64_t arena_allocate(arena_t *, size_t n_bytes);
void *arena_allocation_get(arena_t *, uint64_t allocation_id);

#endif