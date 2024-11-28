#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "derevtso.h"
#include "differentiator.h"

struct Node_t* Differentiator (Node_t* node)
{
    if (node->type == NUMBER)      {return Derivative_const (node);}
    if (node->type == X)           {return Derivative_variable (node);}
    if (node->type == OPERATION)   {return Derivative_operation (node->elem.operation, node);}
}

struct Node_t* Derivative_const (Node_t* node)
{
    node->elem.number = 0;
    return node;
}

struct Node_t* Derivative_variable (Node_t* node)
{
    node->elem.number = 1;
    node->elem.variable = "@";
}

struct Node_t* Derivative_operation (int operation, Node_t* node)
{
    if (operation == ) 
}