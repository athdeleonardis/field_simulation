#include "../test.h"
#include "../../src/allocator/allocators.h"
#include "../../src/math_tree/math_tree_allocators.h"
#include "../../src/math_tree/math_tree_print.h"

int main(int argc, char *argv[]) {
    test_t test = { .name = "MATH TREE" };
    test_initialize(&test, argc, argv);

    arena_t arena;
    arena_initialize(&arena, 1024, 1.5f);

    allocator_t allocator;
    allocator_arena(&allocator, &arena);
    allocator_t *al = &allocator;

    uint64_t math_tree_numbers_id = math_operator_number_add(al,
        math_operator_number_multiply(al,
            math_constant_number(al, 5),
            math_constant_number(al, 2)
        ),
        math_operator_number_subtract(al,
            math_constant_number(al, 1),
            math_operator_number_divide(al,
                math_constant_number(al, 8),
                math_constant_number(al, 4)
            )
        )
    );
    math_tree_node_t *math_tree_numbers = (math_tree_node_t *)allocation_get(al, math_tree_numbers_id);
    if (test.do_log) {
        math_tree_node_print(al, math_tree_numbers);
    }
    test_assert_equal_int(&test, math_tree_check_types(al, math_tree_numbers), 1, "Numbers Tree Type Check");

    uint64_t math_tree_vectors_id = math_operator_number_vector_multiply(al,
        math_operator_vector_dot(al,
            math_operator_vector_add(al,
                math_constant_vector(al, 1, 1, 0),
                math_constant_vector(al, 0, 1, 1)
            ),
            math_constant_vector(al, 1, 1, 1)
        ),
        math_operator_vector_subtract(al,
            math_operator_number_vector_multiply(al,
                math_operator_vector_component(al,
                    math_constant_vector(al, 3, 4, 7),
                    MATH_VECTOR_COMPONENT_Z
                ),
                math_constant_vector(al, 1, 0, 1)
            ),
            math_constant_vector(al, 0, 0, 1)
        )
    );
    math_tree_node_t *math_tree_vectors = (math_tree_node_t *)allocation_get(al, math_tree_vectors_id);
    if (test.do_log) {
        math_tree_node_print(al, math_tree_vectors);
    }
    test_assert_equal_int(&test, math_tree_check_types(al, math_tree_vectors), 1, "Vectors Tree Type Check");
}
