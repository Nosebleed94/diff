#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "optimisation.h"
#include "dumpik.h"
#include "macros.h"

void First_optimisation (Node_t* node)
{
    if (NODE_NOT_OPERATION)
    {
        printf ("<Warning> node is not the operation\n");
        return;
    }

    if (NODES_NOT_NUMBER)
    {
        First_optimisation (node->left);
    }

    if (ALL_TYPE_NUMBER)
    { 
        First_optimisation_operation_with_node (node);
        return;
    }

    if (NODES_NOT_NUMBER)
    {
        First_optimisation (node->right);
    }
    
    if (ALL_TYPE_NUMBER)
    {
        First_optimisation_operation_with_node (node);
        return;
    }
    
    return;
}

Node_t* First_optimisation_operation_with_node (Node_t* node)
{
    int result = 0;

    if (node->elem.operation == _ADD) {FIRST_OPTIMISATION (node->left->elem.number + node->right->elem.number);}
    if (node->elem.operation == _SUB) {FIRST_OPTIMISATION (node->left->elem.number - node->right->elem.number);}
    if (node->elem.operation == _MUL) {FIRST_OPTIMISATION (node->left->elem.number * node->right->elem.number);}
    if (node->elem.operation == _DIV) {FIRST_OPTIMISATION (node->left->elem.number / node->right->elem.number);}
    if (node->elem.operation == _DEG) {FIRST_OPTIMISATION (pow (node->left->elem.number, node->right->elem.number));}

    return node;
}

void Second_optimisation (Node_t* node)
{
    if (NODE_NOT_OPERATION)
    {
        printf ("<Warning> node is not the operation\n");
        return;
    }

    if (TYPES_NO_NUMBER_AND_X)
    {
        Second_optimisation (node->left);
    }

    if (TYPES_NUMBER_AND_X)
    { 
        Second_optimisation_operation_with_node (node);
        return;
    }

    if (TYPES_NO_NUMBER_AND_X)
    {
        Second_optimisation (node->right);
    }
    
    if (TYPES_NUMBER_AND_X)
    {
        Second_optimisation_operation_with_node (node);
        return;
    }
    
    return;
}

Node_t* Second_optimisation_operation_with_node (Node_t* node)
{
    if (CONDITION_FOR_START_SECOND_OPTIMIZATION)
    {
        if ((node->right->elem.number == 0 || node->right->elem.number == 0) && node->elem.operation == _ADD) {RESULT(X, 0)}
        if (node->elem.operation == _SUB) {RESULT(X, 0)}
        if (node->elem.operation == _MUL) {RESULT(NUMBER, 0)}
        
        if (node->elem.operation == _DIV)
        {
            if (node->right->type == NUMBER)
            {
                printf ("Error, you can't divide by zero");
                abort;
            }

            else {RESULT(NUMBER, 0)}
            
        }

        if (node->elem.operation == _DEG)
        {
            if (node->right->elem.number == 0) {RESULT(NUMBER, 1)}

            else {RESULT(NUMBER, 0)}
            
        }
        return node;
    }
    return node;
}

void First_deducr_certain_node (Node_t* node)
{
    free (node->left->elem.variable);
    free (node->right->elem.variable);
    free (node->left);
    free (node->right );
    node->left = NULL;
    node->right = NULL;
}