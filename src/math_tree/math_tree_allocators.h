#ifndef MATH_TREE_ALLOCATORS
#define MATH_TREE_ALLOCATORS

#include "math_tree.h"
#include "../allocator/allocator.h"

//
// 'math_tree_allocators.h' declarations
//

uint64_t math_constant_number(allocator_t *, MATH_NUMBER);
uint64_t math_constant_vector(allocator_t *, MATH_NUMBER x, MATH_NUMBER y, MATH_NUMBER z);

uint64_t math_variable_number(allocator_t *, MATH_NAME, MATH_NUMBER initial_value);
uint64_t math_variable_vector(allocator_t *, MATH_NAME, MATH_NUMBER initial_x, MATH_NUMBER initial_y, MATH_NUMBER initial_z);

uint64_t math_field_number(allocator_t *, MATH_NAME);
uint64_t math_field_vector(allocator_t *, MATH_NAME);

uint64_t math_operator_number_add(allocator_t *, uint64_t left, uint64_t right);
uint64_t math_operator_number_subtract(allocator_t *, uint64_t left, uint64_t right);
uint64_t math_operator_number_multiply(allocator_t *, uint64_t left, uint64_t right);
uint64_t math_operator_number_divide(allocator_t *, uint64_t left, uint64_t right);

uint64_t math_operator_vector_add(allocator_t *, uint64_t left, uint64_t right);
uint64_t math_operator_vector_subtract(allocator_t *, uint64_t left, uint64_t right);
uint64_t math_operator_vector_dot(allocator_t *, uint64_t left, uint64_t right);
uint64_t math_operator_vector_cross(allocator_t *, uint64_t left, uint64_t right);
uint64_t math_operator_vector_component(allocator_t *, uint64_t vector, MATH_VECTOR_COMPONENT);

uint64_t math_operator_number_vector_multiply(allocator_t *, uint64_t number, uint64_t vector);

#endif
