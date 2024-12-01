#ifndef MACROS_H
#define MACROS_H

#include "derevtso.h"

#define FIRST_OPTIMISATION(operation_) \
{ \
    result = (operation_); \
    node->elem.number = result; \
    node->type = NUMBER; \
    node->elem.operation = 0; \
    First_deducr_certain_node(node); \
} 

#define NODES_NOT_NUMBER (node->left->type != NUMBER || node->right->type != NUMBER)
#define ALL_TYPE_NUMBER  (node->left->type == NUMBER && node->right->type == NUMBER) //FIXME
#define CONDITION_FOR_START_SECOND_OPTIMIZATION (node->left->elem.number == 0 || node->left->elem.number == 1 || \
                                                 node->right->elem.number == 0 || node->right->elem.number == 1)
#define NODE_NOT_OPERATION (node->type == NUMBER || node->type == X)
#define TYPES_NO_NUMBER_AND_X (!(node->left->type == NUMBER && node->right->type == X) || \
                               !(node->right->type == NUMBER && node->left->type == X))
#define TYPES_NUMBER_AND_X ((node->left->type == NUMBER && node->right->type == X) || \
                            (node->right->type == NUMBER && node->left->type == X))

#define RESULT(type_, value_) \
{ \
    node->type = type_; \
    node->elem.operation = 0; \
    if (type_ == X) \
    { \
        strcpy(node->elem.variable, VARIABLE); \
    } \
    else if (type_ == NUMBER) \
    { \
        node->elem.number = value_; \
    } \
    First_deducr_certain_node(node); \
    return node; \
}
#endif //MACROS_H
