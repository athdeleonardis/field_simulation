#include "math_tree.h"

//
// 'math_tree.c' declarations
//

/**
 * Returns the node's type if it's not an operator, or if it's an operator and it's left and right inputs are correctly typed.
 * Returns zero otherwise.
 */ 
MATH_NODE_TYPE _math_tree_check_types(allocator_t *, math_tree_node_t *, MATH_NODE_TYPE type_expected);

//
// 'math_tree.c' implementations
//

MATH_NODE_TYPE _math_tree_check_types(allocator_t *allocator, math_tree_node_t *node, MATH_NODE_TYPE type_expected) {
    MATH_NODE_TYPE type = math_node_get_type(node->type);
    if (type != type_expected)
        return 0;
    MATH_NODE_TYPE variability = math_node_get_variability(node->type);

    if (variability == MATH_VARIABILITY_OPERATOR) {
        MATH_NODE_TYPE type_left = math_node_get_type_left(node->type);
        math_tree_node_t *node_left = (math_tree_node_t *)allocation_get(allocator, node->operator.input_left);
        if (!_math_tree_check_types(allocator, node_left, type_left))
            return 0;
        
        MATH_NODE_TYPE type_right = math_node_get_type_right(node->type);
        math_tree_node_t *node_right = (math_tree_node_t *)allocation_get(allocator, node->operator.input_right);
        if (!_math_tree_check_types(allocator, node_right, type_right))
            return 0;
    }

    return 1;
}

//
// 'math_tree.h' implementations
//

MATH_NODE_TYPE math_node_type(MATH_NODE_TYPE variability, MATH_NODE_TYPE type_output, MATH_NODE_TYPE type_input_left, MATH_NODE_TYPE type_input_right) {
    return variability | (type_output << 8) | (type_input_left << 4) | type_input_right;
}


MATH_NODE_TYPE math_node_get_variability(MATH_NODE_TYPE type) {
    return type & MATH_MASK_VARIABILITY;
}

MATH_NODE_TYPE math_node_get_type(MATH_NODE_TYPE type) {
    return (type & MATH_MASK_TYPE) >> 8;
}

MATH_NODE_TYPE math_node_get_type_left(MATH_NODE_TYPE type) {
    return (type & MATH_MASK_TYPE_LEFT) >> 4;
}

MATH_NODE_TYPE math_node_get_type_right(MATH_NODE_TYPE type) {
    return type & MATH_MASK_TYPE_RIGHT;
}

uint32_t math_tree_check_types(allocator_t *allocator, math_tree_node_t *node) {
    _math_tree_check_types(allocator, node, math_node_get_type(node->type));
}
