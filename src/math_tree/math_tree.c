#include "math_tree.h"

//
// 'math_tree.c' declarations
//

/**
 * Returns the node's type if it's not an operator, or if it's an operator and it's left and right inputs are correctly typed.
 * Returns zero otherwise.
 */ 
MATH_NODE_TYPE _math_tree_check_types(math_tree_node_t *);

//
// 'math_tree.c' implementations
//

MATH_NODE_TYPE _math_tree_check_types(math_tree_node_t *node) {
    MATH_NODE_TYPE variability = math_node_variability(node->type);
    MATH_NODE_TYPE type = math_node_get_type(node->type);
    if (variability == MATH_NODE_OPERATOR && node->operator.input_left ) {
        
    }
}

//
// 'math_tree.h' implementations
//

MATH_NODE_TYPE math_node_variability(MATH_NODE_TYPE type) {
    return type & MATH_NODE_MASK;
}

MATH_NODE_TYPE math_node_type(MATH_NODE_TYPE variability, MATH_NODE_TYPE type_output, MATH_NODE_TYPE type_input_left, MATH_NODE_TYPE type_input_right) {
    return variability | type_output | (type_input_left << 4) | (type_input_right << 8);
}

MATH_NODE_TYPE math_node_get_type(MATH_NODE_TYPE type) {
    return type & MATH_TYPE_MASK;
}

MATH_NODE_TYPE math_node_get_type_left(MATH_NODE_TYPE type) {
    return (type >> 4) & MATH_TYPE_MASK;
}

MATH_NODE_TYPE math_node_get_type_right(MATH_NODE_TYPE type) {
    return (type >> 8) & MATH_TYPE_MASK;
}

uint64_t math_tree_check_types(math_tree_node_t *node) {

}
