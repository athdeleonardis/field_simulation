#include "math_tree_functions.h"
#include "math_tree.h"

//
// 'math_tree_functions.c' declarations
//

void *_allocate_math_number(allocator_t *, MATH_NUMBER);
void *_allocate_math_vector(allocator_t *, MATH_NUMBER x, MATH_NUMBER y, MATH_NUMBER z);

//
// 'math_tree_functions.c' implementations
//

void *_allocate_math_number(allocator_t *allocator, MATH_NUMBER value) {
    uint64_t allocation_id = allocate(allocator, sizeof(MATH_NUMBER));
    MATH_NUMBER *number = allocation_get(allocator, allocation_id);
    *number = value;
    return (void *)number;
}

void *_allocate_math_vector(allocator_t *allocator, MATH_NUMBER x, MATH_NUMBER y, MATH_NUMBER z) {
    uint64_t allocation_id = allocate(allocator, 3 * sizeof(MATH_NUMBER));
    MATH_NUMBER *vector = allocation_get(allocator, allocation_id);
    vector[0] = x;
    vector[1] = y;
    vector[2] = z;
    return (void *)vector;
}

//
// 'math_tree_functions.h' implementations
//

void *math_function_number_add(allocator_t *allocator, void *left, void *right) {
    return _allocate_math_number(allocator, *(MATH_NUMBER *)left + *(MATH_NUMBER *)right);
}
void *math_function_number_subtract(allocator_t *allocator, void *left, void *right) {
    return _allocate_math_number(allocator, *(MATH_NUMBER *)left - *(MATH_NUMBER *)right);
}
void *math_function_number_multiply(allocator_t *allocator, void *left, void *right) {
    return _allocate_math_number(allocator, (*(MATH_NUMBER *)left) * (*(MATH_NUMBER *)right));
}
void *math_function_number_divide(allocator_t *allocator, void *left, void *right) {
    return _allocate_math_number(allocator, (*(MATH_NUMBER *)left) / (*(MATH_NUMBER *)right));
}

void *math_function_vector_add(allocator_t *allocator, void *left, void *right) {
    MATH_NUMBER *vleft = (MATH_NUMBER *)vleft;
    MATH_NUMBER *vright = (MATH_NUMBER *)vright;
    return _allocate_math_vector(allocator, vleft[0]+vright[0], vleft[1]+vright[1], vleft[2]+vright[2]);
}
void *math_function_vector_subtract(allocator_t *allocator, void *left, void *right) {
    MATH_NUMBER *vleft = (MATH_NUMBER *)vleft;
    MATH_NUMBER *vright = (MATH_NUMBER *)vright;
    return _allocate_math_vector(allocator, vleft[0]-vright[0], vleft[1]-vright[1], vleft[1]-vright[1]);
}
void *math_function_vector_dot(allocator_t *allocator, void *left, void *right) {
    MATH_NUMBER *vleft = (MATH_NUMBER *)vleft;
    MATH_NUMBER *vright = (MATH_NUMBER *)vright;
    return _allocate_math_number(allocator, vleft[0]*vright[0] + vleft[1]*vright[1] + vleft[2]*vright[2]);
}
void *math_function_vector_cross(allocator_t *allocator, void *left, void *right) {
    // TODO
}
void *math_function_vector_component(allocator_t *allocator, void *vector, void *component) {
    return (void *)((MATH_NUMBER *)vector + *(uint32_t *)component);
}

void *math_function_number_vector_multiply(allocator_t *allocator, void *number, void *vector) {
    MATH_NUMBER num = *(MATH_NUMBER *)number;
    MATH_NUMBER *vec = (MATH_NUMBER *)vector;
    return _allocate_math_vector(allocator, num*vec[0], num*vec[1], num*vec[2]);
}
