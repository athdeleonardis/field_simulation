#include "../../src/allocator/allocators.h"
#include "../../src/math_tree/math_tree_allocators.h"
#include "../../src/math_tree/math_tree_print.h"

int main(int argc, char *arv[]) {
    arena_t arena;
    arena_initialize(&arena, 1024, 1.5f);

    allocator_t allocator;
    allocator_arena(&allocator, &arena);

    uint64_t math_tree_numbers_id = math_operator_number_add(&allocator,
        math_operator_number_multiply(&allocator,
            math_constant_number(&allocator, 5),
            math_constant_number(&allocator, 2)
        ),
        math_operator_number_subtract(&allocator,
            math_constant_number(&allocator, 1),
            math_operator_number_divide(&allocator,
                math_constant_number(&allocator, 8),
                math_constant_number(&allocator, 4)
            )
        )
    );
    math_tree_node_t *math_tree_numbers = (math_tree_node_t *)allocation_get(&allocator, math_tree_numbers_id);
    math_tree_node_print(&allocator, math_tree_numbers);

    uint64_t math_tree_vectors_id = math_operator_number_vector_multiply(&allocator,
        math_operator_vector_dot(&allocator,
            math_operator_vector_add(&allocator,
                math_constant_vector(&allocator, 1, 1, 0),
                math_constant_vector(&allocator, 0, 1, 1)
            ),
            math_constant_vector(&allocator, 1, 1, 1)
        ),
        math_operator_vector_subtract(&allocator,
            math_operator_number_vector_multiply(&allocator,
                math_operator_vector_component(&allocator,
                    math_constant_vector(&allocator, 3, 4, 7),
                    MATH_VECTOR_COMPONENT_Z
                ),
                math_constant_vector(&allocator, 1, 0, 1)
            ),
            math_constant_vector(&allocator, 0, 0, 1)
        )
    );
    math_tree_node_t *math_tree_vectors = (math_tree_node_t *)allocation_get(&allocator, math_tree_vectors_id);
    math_tree_node_print(&allocator, math_tree_vectors);
}
