#include <stdio.h>
#include "math_tree_print.h"

#define MATH_TREE_PRINT_INDENTATION_EMPTY "  "
#define MATH_TREE_PRINT_INDENTATION_START "|-"
#define MATH_TREE_PRINT_INDENTATION_LINES "--"

//
// 'math_tree_print.c' declarations
//

void _math_tree_node_print(allocator_t *allocator, math_tree_node_t *node, int indentation);
const char *_math_tree_type_string(MATH_NODE_TYPE type);
void _math_tree_type_print(MATH_NODE_TYPE type);

//
// 'math_tree_print.c' implementations
//

void _math_tree_node_print(allocator_t *allocator, math_tree_node_t *node, int indentation) {
    for (int i = 0; i < indentation-1; i++) {
        printf(MATH_TREE_PRINT_INDENTATION_EMPTY);
    }
    if (indentation != 0)
        printf(MATH_TREE_PRINT_INDENTATION_START);
    _math_tree_type_print(node->type);
    if (math_node_variability(node->type) == MATH_NODE_OPERATOR) {
        math_tree_node_t *node_input = (math_tree_node_t *)allocation_get(allocator, node->operator.input_left);
        _math_tree_node_print(allocator, node_input, indentation + 1);
        node_input = (math_tree_node_t *)allocation_get(allocator, node->operator.input_right);
        _math_tree_node_print(allocator, node_input, indentation + 1);
    }
}

const char *_math_tree_type_string(MATH_NODE_TYPE type) {
    switch (type) {
        case MATH_TYPE_NUMBER:
            return "Number";
        case MATH_TYPE_VECTOR:
            return "Vector";
        case MATH_TYPE_SELECTOR:
            return "Selector";
    }
    return "No type";
}

void _math_tree_type_print(MATH_NODE_TYPE type) {
    switch (math_node_variability(type)) {
        case MATH_NODE_CONSTANT: {
            printf("Constant: %s\n", _math_tree_type_string(math_node_get_type(type)));
            break;
        }
        case MATH_NODE_OPERATOR: {
            const char *type_input_left = _math_tree_type_string(math_node_get_type_left(type));
            const char *type_input_right = _math_tree_type_string(math_node_get_type_right(type));
            const char *type_output = _math_tree_type_string(math_node_get_type(type));
            printf("Operator: %s -> %s -> %s\n", type_input_left, type_input_right, type_output);
            break;
        }
        case MATH_NODE_FIELD: {
            printf("Field: %i\n", math_node_get_type(type));
            break;
        }
        case MATH_NODE_SELECTOR: {
            printf("Selector: %i\n", math_node_get_type(type));
            break;
        }
    }
}

//
// 'math_tree_print.h' implementations
//

void math_tree_node_print(allocator_t *allocator, math_tree_node_t *node) {
    _math_tree_node_print(allocator, node, 0);
}
