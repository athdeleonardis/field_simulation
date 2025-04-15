#include <stdio.h>
#include "../test.h"
#include "../../src/allocator/allocators.h"

struct _test_arena_struct {
    uint32_t number;
};

uint64_t _test_arena_allocate(allocator_t *allocator, uint32_t number) {
    uint64_t allocation_id = allocate(allocator, sizeof(struct _test_arena_struct));
    struct _test_arena_struct *allocation = allocation_get(allocator, allocation_id);
    allocation->number = number;
    return allocation_id;
}

int main(int argc, char *argv[]) {
    test_t test = { .name="ARENA" };
    test_initialize(&test, argc, argv);
    uint32_t struct_size = sizeof(struct _test_arena_struct);

    arena_t arena1;
    arena_initialize(&arena1, 16, 1.5f);

    allocator_t allocator;
    allocator_arena(&allocator, &arena1);

    uint64_t numbers[5] = { 10, 15, 18, 4, 7 };
    for (int i = 0; i < 4; i++) {
        uint64_t allocation_id = _test_arena_allocate(&allocator, numbers[i]);
        struct _test_arena_struct *allocation = allocation_get(&allocator, allocation_id);
        char message[32];
        sprintf(message, "allocation %i number", i, numbers[i]);
        test_assert_equal_int(&test, numbers[i], allocation->number, message);
        sprintf(message, "allocation %i capacity", i);
        test_assert_equal_int(&test, arena1.capacity, 16, message);
        sprintf(message, "allocation %i allocated", i);
        test_assert_equal_int(&test, arena1.allocated, struct_size * (i+1), message);
        sprintf(message, "allocation %i remaining", i);
        test_assert_equal_int(&test, arena1.remaining, 16 - struct_size * (i+1), message);
    }

    uint64_t allocation_id = _test_arena_allocate(&allocator, numbers[4]);
    struct _test_arena_struct *allocation = allocation_get(&allocator, allocation_id);
    test_assert_equal_int(&test, numbers[4], allocation->number, "allocation 4 number");
    test_assert_equal_int(&test, arena1.capacity, 24, "allocation 4 capacity");
    test_assert_equal_int(&test, arena1.allocated, 5 * struct_size, "allocation 4 allocated");
    test_assert_equal_int(&test, arena1.remaining, 24 - 5 * struct_size, "allocation 4 remaining");

    arena_empty(&arena1);
    test_assert_equal_int(&test, arena1.allocated, 0, "arena empty allocated");

    test_log_success(&test);
}
