#ifndef MATH_TREE
#define MATH_TREE

#include <stdint.h>
#include "../allocator/allocator.h"

//
// 'math_tree.h' declarations
//

#ifndef MATH_NUMBER
    #define MATH_NUMBER float
#endif
#define MATH_NAME const char*
#define MATH_NODE_TYPE uint32_t

#define MATH_NODE_MASK 0xF000
#define MATH_NODE_CONSTANT 0x1000
#define MATH_NODE_OPERATOR 0x2000
#define MATH_NODE_SELECTOR 0x3000
#define MATH_NODE_FIELD 0x4000

#define MATH_TYPE_MASK 0x000F
#define MATH_TYPE_NUMBER 0x0001
#define MATH_TYPE_VECTOR 0x0002
#define MATH_TYPE_SELECTOR 0x003

#define MATH_OPERATOR_ID unsigned char
#define MATH_OPERATOR_PLUS 1
#define MATH_OPERATOR_MINUS 2
#define MATH_OPERATOR_MULTIPLY 3
#define MATH_OPERATOR_DIVIDE 4
#define MATH_OPERATOR_DOT 5
#define MATH_OPERATOR_CROSS 6
#define MATH_OPERATOR_VECTOR_ELEM 7

#define MATH_VECTOR_COMPONENT unsigned char
#define MATH_VECTOR_COMPONENT_X 0
#define MATH_VECTOR_COMPONENT_Y 1
#define MATH_VECTOR_COMPONENT_Z 2

typedef struct math_tree_node math_tree_node_t;

struct math_operator {
    void *(*function)(allocator_t *, void *, void *);
    uint64_t input_left;
    uint64_t input_right;
};

struct math_tree_node {
    MATH_NODE_TYPE type;
    union {
        MATH_NUMBER number;
        MATH_NUMBER vector[3];
        struct math_operator operator;
    };
};

MATH_NODE_TYPE math_node_type(MATH_NODE_TYPE variability, MATH_NODE_TYPE type_output, MATH_NODE_TYPE type_input_left, MATH_NODE_TYPE type_input_right);
/** Returns the variability of the node. */
MATH_NODE_TYPE math_node_variability(MATH_NODE_TYPE type);
/** Returns the type of the node. */
MATH_NODE_TYPE math_node_get_type(MATH_NODE_TYPE type);
/** Returns the type of the left input of the operator node. */
MATH_NODE_TYPE math_node_get_type_left(MATH_NODE_TYPE type);
/** Returns the type of the right input of the operator node. */
MATH_NODE_TYPE math_node_get_type_right(MATH_NODE_TYPE type);

/** Returns 1 if the types are correct, and 0 otherwise. */
uint32_t math_tree_check_types(allocator_t *, math_tree_node_t *);

#endif
