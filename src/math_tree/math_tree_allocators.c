#include "math_tree_allocators.h"
#include "math_tree_functions.h"

//
// 'math_tree_allocators.c' declarations
//

uint64_t _allocate_math_tree_node(allocator_t *, MATH_NODE_TYPE);
uint64_t _allocate_math_tree_operator(allocator_t *, MATH_NODE_TYPE, uint64_t left, uint64_t right, void *(*)(allocator_t *, void *, void *));
uint64_t _allocate_math_tree_selector(allocator_t *, MATH_NODE_TYPE selector);

//
// 'math_tree_allocators.c' implementations
//

uint64_t _allocate_math_tree_node(allocator_t *allocator, MATH_NODE_TYPE type) {
    uint64_t node_id = allocate(allocator, sizeof(math_tree_node_t));
    math_tree_node_t *node = (math_tree_node_t *)allocation_get(allocator, node_id);
    node->type = type;
    return node_id;
}

uint64_t _allocate_math_tree_operator(allocator_t *allocator, MATH_NODE_TYPE type, uint64_t left, uint64_t right, void *(*function)(allocator_t *, void *, void*)) {
    uint64_t node_id = allocate(allocator, sizeof(math_tree_node_t));
    math_tree_node_t *node = (math_tree_node_t *)allocation_get(allocator, node_id);
    node->type = type | MATH_NODE_OPERATOR;
    node->operator.function = function;
    node->operator.input_left = left;
    node->operator.input_right = right;
    return node_id;
}

uint64_t _allocate_math_tree_selector(allocator_t *allocator, MATH_NODE_TYPE selector) {
    uint64_t node_id = allocate(allocator, sizeof(math_tree_node_t));
    math_tree_node_t *node = (math_tree_node_t *)allocation_get(allocator, node_id);
    node->type = MATH_NODE_SELECTOR | selector;
    return node_id;
}

//
// 'math_tree_allocators.h' implementations
//

uint64_t math_constant_number(allocator_t *allocator, MATH_NUMBER number) {
    uint64_t node_id = _allocate_math_tree_node(allocator, MATH_NODE_CONSTANT | MATH_TYPE_NUMBER);
    math_tree_node_t *node = (math_tree_node_t *)allocation_get(allocator, node_id);
    node->number = number;
    return node_id;
}

uint64_t math_constant_vector(allocator_t *allocator, MATH_NUMBER x, MATH_NUMBER y, MATH_NUMBER z) {
    uint64_t node_id = _allocate_math_tree_node(allocator, MATH_NODE_CONSTANT | MATH_TYPE_VECTOR);
    math_tree_node_t *node = (math_tree_node_t *)allocation_get(allocator, node_id);
    node->vector[0] = x;
    node->vector[1] = y;
    node->vector[2] = z;
    return node_id;
}

uint64_t math_variable_number(allocator_t *, MATH_NAME, MATH_NUMBER initial_value);
uint64_t math_variable_vector(allocator_t *, MATH_NAME, MATH_NUMBER initial_x, MATH_NUMBER initial_y, MATH_NUMBER initial_z);

uint64_t math_field_number(allocator_t *, MATH_NAME);
uint64_t math_field_vector(allocator_t *, MATH_NAME);

uint64_t math_operator_number_add(allocator_t *allocator, uint64_t left, uint64_t right) {
    MATH_NODE_TYPE type = math_node_type(MATH_NODE_OPERATOR, MATH_TYPE_NUMBER, MATH_TYPE_NUMBER, MATH_TYPE_NUMBER);
    return _allocate_math_tree_operator(allocator, type, left, right, math_function_number_add);
}
uint64_t math_operator_number_subtract(allocator_t *allocator, uint64_t left, uint64_t right) {
    MATH_NODE_TYPE type = math_node_type(MATH_NODE_OPERATOR, MATH_TYPE_NUMBER, MATH_TYPE_NUMBER, MATH_TYPE_NUMBER);
    return _allocate_math_tree_operator(allocator, type, left, right, math_function_number_subtract);
}
uint64_t math_operator_number_multiply(allocator_t *allocator, uint64_t left, uint64_t right) {
    MATH_NODE_TYPE type = math_node_type(MATH_NODE_OPERATOR, MATH_TYPE_NUMBER, MATH_TYPE_NUMBER, MATH_TYPE_NUMBER);
    return _allocate_math_tree_operator(allocator, type, left, right, math_function_number_multiply);
}
uint64_t math_operator_number_divide(allocator_t *allocator, uint64_t left, uint64_t right) {
    MATH_NODE_TYPE type = math_node_type(MATH_NODE_OPERATOR, MATH_TYPE_NUMBER, MATH_TYPE_NUMBER, MATH_TYPE_NUMBER);
    return _allocate_math_tree_operator(allocator, type, left, right, math_function_number_divide);
}

uint64_t math_operator_vector_add(allocator_t *allocator, uint64_t left, uint64_t right) {
    MATH_NODE_TYPE type = math_node_type(MATH_NODE_OPERATOR, MATH_TYPE_VECTOR, MATH_TYPE_VECTOR, MATH_TYPE_VECTOR);
    return _allocate_math_tree_operator(allocator, type, left, right, math_function_vector_add);
}
uint64_t math_operator_vector_subtract(allocator_t *allocator, uint64_t left, uint64_t right) {
    MATH_NODE_TYPE type = math_node_type(MATH_NODE_OPERATOR, MATH_TYPE_VECTOR, MATH_TYPE_VECTOR, MATH_TYPE_VECTOR);
    return _allocate_math_tree_operator(allocator, type, left, right, math_function_vector_subtract);
}
uint64_t math_operator_vector_dot(allocator_t *allocator, uint64_t left, uint64_t right) {
    MATH_NODE_TYPE type = math_node_type(MATH_NODE_OPERATOR, MATH_TYPE_NUMBER, MATH_TYPE_VECTOR, MATH_TYPE_VECTOR);
    return _allocate_math_tree_operator(allocator, type, left, right, math_function_vector_dot);
}
uint64_t math_operator_vector_cross(allocator_t *allocator, uint64_t left, uint64_t right) {
    MATH_NODE_TYPE type = math_node_type(MATH_NODE_OPERATOR, MATH_TYPE_VECTOR, MATH_TYPE_VECTOR, MATH_TYPE_VECTOR);
    return _allocate_math_tree_operator(allocator, type, left, right, math_function_vector_cross);
}
uint64_t math_operator_vector_component(allocator_t *allocator, uint64_t vector, MATH_VECTOR_COMPONENT component) {
    uint64_t selector = _allocate_math_tree_selector(allocator, component);
    return _allocate_math_tree_operator(allocator, MATH_TYPE_NUMBER, vector, selector, math_function_vector_component);
}

uint64_t math_operator_number_vector_multiply(allocator_t *allocator, uint64_t number, uint64_t vector) {
    MATH_NODE_TYPE type = math_node_type(MATH_NODE_OPERATOR, MATH_TYPE_VECTOR, MATH_TYPE_NUMBER, MATH_TYPE_VECTOR);
    return _allocate_math_tree_operator(allocator, type, number, vector, math_function_number_vector_multiply);
}
