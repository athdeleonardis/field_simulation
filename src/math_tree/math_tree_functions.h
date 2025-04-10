#ifndef MATH_TREE_FUNCTIONS
#define MATH_TREE_FUNCTIONS

#include "../allocator/allocator.h"

//
// 'math_tree_functions.h' declarations
//

void *math_function_number_add(allocator_t *, void *left, void *right);
void *math_function_number_subtract(allocator_t *, void *left, void *right);
void *math_function_number_multiply(allocator_t *, void *left, void *right);
void *math_function_number_divide(allocator_t *, void *left, void *right);

void *math_function_vector_add(allocator_t *, void *left, void *right);
void *math_function_vector_subtract(allocator_t *, void *left, void *right);
void *math_function_vector_dot(allocator_t *, void *left, void *right);
void *math_function_vector_cross(allocator_t *, void *left, void *right);
void *math_function_vector_component(allocator_t *allocator, void *vector, void *component);

void *math_function_number_vector_multiply(allocator_t *, void *number, void *vector);

#endif
