#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "derevtso.h"
#include "differentiator.h"
#include "defining_operation.h"
#include "operation.h"
#include "copy_tree.h"
#include "dumpik.h"

struct Node_t* Differentiator (Node_t* node)
{
    if (node->type == NUMBER)      {return Derivative_const (node);}
    if (node->type == X)           {return Derivative_variable (node);}
    if (node->type == OPERATION)   {return Derivative_operation (node->elem.operation, node);}

}

struct Node_t* Derivative_const (Node_t* node)
{
    struct Node_t* main_node = Build_node (_NOTHING, "@", 0, NULL, NULL, NUMBER);
    fprintf (stderr,"в дифференциаторе [%d]\n", &(node->elem));
    return main_node;
}

struct Node_t* Derivative_variable (Node_t* node)
{
    struct Node_t* main_node = Build_node (_NOTHING, "@", 1, NULL, NULL, NUMBER);
    //fprintf (stderr,"в дифференциаторе [%d]\n", &(node->elem));
    return main_node;
}

struct Node_t* Derivative_operation (int operation, Node_t* node)
{
    if (operation == _ADD)    {return Derivative_add (node);}
    if (operation == _SUB)    {return Derivative_sub (node);}
    if (operation == _MUL)    {return Derivative_mul (node);}
    // if (operation == _DIV)    {return Derivative_div (node);}
    // if (operation == _SIN)    {return Derivative_sin (node);}
    // if (operation == _COS)    {return Derivative_cos (node);}
    // if (operation == _TG)     {return Derivative_tg (node);}
    // if (operation == _CTG)    {return Derivative_ctg (node);}
    // if (operation == _ARCSIN) {return Derivative_arcsin (node);}
    // if (operation == _ARCCOS) {return Derivative_arccos (node);}
    // if (operation == _ARCTG)  {return Derivative_arctg (node);}
    // if (operation == _ARCCTG) {return Derivative_arcctg (node);}
    // if (operation == _SH)     {return Derivative_sh (node);}
    // if (operation == _CH)     {return Derivative_ch (node);}
    // if (operation == _TH)     {return Derivative_th (node);}
    // if (operation == _CTH)    {return Derivative_cth (node);}
    // if (operation == _LOG)    {return Derivative_log (node);}
    // if (operation == _LN)     {return Derivative_ln (node);}

    // FIXME длолжна что то ретёррнуть
}

//     if (operation == _DEG)    {return;}
//     return node;
// }

struct Node_t* Build_node (int operation, char* variable, double number, 
                           Node_t* left, Node_t* right, type_Node type)
{
    struct Node_t* newNode = (struct Node_t*)calloc(1, sizeof(struct Node_t));
    newNode->elem.variable = (char*)calloc(strlen(variable) + 1, sizeof(char));
    newNode->elem.number = number;
    newNode->elem.operation = operation;
    strcpy (newNode->elem.variable, variable);
    newNode->left = left;
    newNode->right = right;
    newNode->type = type;
    fprintf (stderr,"\n\n\n\n\n\nтип узла в дифе [%d}\n\n\n\n\n\n\n", newNode->type);
    return newNode;
}

struct Node_t* Derivative_add(Node_t* node) 
{
    struct Node_t* l = Differentiator (node->left);
    struct Node_t* r = Differentiator (node->right);

    struct Node_t* main_node = Build_node (_ADD, "@", 10, l, r, OPERATION);
    return main_node; 
}

struct Node_t* Derivative_sub (Node_t* node) 
{
    struct Node_t* l = Differentiator (node->left);
    struct Node_t* r = Differentiator (node->right);

    struct Node_t* main_node = Build_node( _SUB, "@", 10, l, r, OPERATION);
    return main_node; 
}

struct Node_t* Derivative_mul (Node_t* node)
{
    struct Node_t* r_l = Differentiator (node->right);
    struct Node_t* r_r = Copy_tree (node->left);
    struct Node_t* l_l = Differentiator (node->left);
    struct Node_t* l_r = Copy_tree (node->right);
    Dump_moment (l_r);
    struct Node_t* l =  Build_node ( _MUL, "@", 10, r_l, r_r, OPERATION);
    Dump_moment (r_r);
    struct Node_t* r =  Build_node ( _MUL, "@", 10, l_l, l_r, OPERATION);

    struct Node_t* main_node = Build_node (_ADD, "@", 10, l, r, OPERATION);
    return main_node;
}

// struct Node_t* Derivative_div (Node_t* node)
// {
//     struct Node_t* l_r_r = Copy_tree (node->right);
//     struct Node_t* l_r_l =  Differentiator (node->right);
//     struct Node_t* l_l_r = Copy_tree (node->right);
//     struct Node_t* l_l_l = Differentiator (node->left);

//     struct Node_t* r_r = Build_node (_NOTHING, "@", 2, NULL, NULL, NUMBER);
//     struct Node_t* r_l = Copy_tree (node->left);
//     struct Node_t* l_r = Build_node ( _MUL, "@", 10, l_r_l, l_r_r, OPERATION);
//     struct Node_t* l_l = Build_node ( _MUL, "@", 10, l_l_l, l_l_r, OPERATION);

//     struct Node_t* r = Build_node (_DEG, "@", 10, r_l, r_r, OPERATION);    
//     struct Node_t* l = Build_node (_SUB, "@", 10, l_l, l_r, OPERATION);

//     struct Node_t* main_node = Build_node (_DIV, "@", 10, l, r, OPERATION);
// }

// struct Node_t* Derivative_sin (Node_t* node)
// {
//     struct Node_t* l_r = Copy_tree (node->right);
//     struct Node_t* l_l = Build_node ( _NOTHING, "@", 10, NULL, NULL, OPERATION);

//     struct Node_t* r = Differentiator (node->right);
//     struct Node_t* l = Build_node (_COS, "@", 10, l_l, l_r, OPERATION);

//     struct Node_t* main_node = Build_node (_MUL, "@", 10, l, r, OPERATION);
// }

// struct Node_t* Derivative_cos (Node_t* node)
// {
//     struct Node_t* l_r_r = Copy_tree (node->right);
//     struct Node_t* l_r_l = Build_node ( _NOTHING, "@", 10, NULL, NULL, OPERATION);

//     struct Node_t* l_r = Build_node (_SIN, "@", 10, l_r_l, l_r_r, OPERATION);
//     struct Node_t* l_l = Build_node ( _NOTHING, "@", 10, NULL, NULL, OPERATION);

//     struct Node_t* r = Differentiator (node->right);
//     struct Node_t* l = Build_node (_SUB, "@", 10, l_l, l_r, OPERATION);

//     struct Node_t* main_node = Build_node (_MUL, "@", 10, l, r, OPERATION);
// }

// struct Node_t* Derivative_tg  (Node_t* node)
// {
//     struct Node_t* l_r_l_l = Build_node (_NOTHING, "@", 10, NULL, NULL, NUMBER);
//     struct Node_t* l_r_l_r = Copy_tree (node->right);

//     struct Node_t* l_r_r = Build_node (_COS, "@", 10, l_r_l_l, l_r_l_r, OPERATION);
//     struct Node_t* l_r_l = Build_node (_NOTHING, "@", 2, NULL, NULL, NUMBER);

//     struct Node_t* l_r = Build_node (_DEG, "@", 10, l_r_l, l_r_r, OPERATION);
//     struct Node_t* l_l = Build_node (_NOTHING, "@", 1, NULL, NULL, NUMBER);

//     struct Node_t* r = Differentiator (node->right);
//     struct Node_t* l = Build_node (_DIV, "@", 10, l_l, l_r, OPERATION);

//     struct Node_t* main_node = Build_node (_MUL, "@", 10, l, r, OPERATION);
// }

// struct Node_t* Derivative_ctg  (Node_t* node)
// {
//     struct Node_t* l_r_l_l = Build_node (_NOTHING, "@", 1, NULL, NULL, NUMBER);
//     struct Node_t* l_r_l_r = Copy_tree (node->right);

//     struct Node_t* l_r_r = Build_node (_NOTHING, "@", 2, NULL, NULL, NUMBER);
//     struct Node_t* l_r_l = Build_node (_SIN, "@", 10, l_r_l_l, l_r_l_r, OPERATION);
//     struct Node_t* l_l_r = Build_node (_NOTHING, "@", 1, NULL, NULL, NUMBER);
//     struct Node_t* l_l_l = Build_node (_SUB, "@", 10, NULL, NULL, OPERATION);

//     struct Node_t* l_r = Build_node (_DEG, "@", 10, l_r_l, l_r_r, OPERATION);
//     struct Node_t* l_l =  Build_node (_MUL, "@", 10, l_l_l, l_l_r, NUMBER);

//     struct Node_t* r = Differentiator (node->right);
//     struct Node_t* l = Build_node (_DIV, "@", 0, l_l, l_r, OPERATION);

//     struct Node_t* main_node = Build_node (_MUL, "@", 0, l, r, OPERATION);
// }

// struct Node_t* Derivative_arcsin (Node_t* node)
// {
//     struct Node_t* l_r_l_r_r = Build_node (_NOTHING, "@", 2, NULL, NULL, NUMBER);
//     struct Node_t* l_r_l_r_l = Copy_tree (node->right);

//     struct Node_t* l_r_l_r = Build_node (_DEG, "@", 10, l_r_l_r_l, l_r_l_r_r, OPERATION);
//     struct Node_t* l_r_l_l = Build_node (_NOTHING, "@", 1, NULL, NULL, NUMBER);
//     struct Node_t* l_r_r_l = Build_node (_NOTHING, "@", 1, NULL, NULL, NUMBER);
//     struct Node_t* l_r_r_r = Build_node (_NOTHING, "@", 2, NULL, NULL, NUMBER);

//     struct Node_t* l_r_r = Build_node (_DIV, "@", 10, l_r_r_l, l_r_r_r, OPERATION);
//     struct Node_t* l_r_l = Build_node (_SUB, "@", 10, l_r_l_l, l_r_l_r, OPERATION);

//     struct Node_t* l_r = Build_node (_DEG, "@", 10, l_r_l, l_r_r, OPERATION);
//     struct Node_t* l_l = Build_node (_NOTHING, "@", 1, NULL, NULL, NUMBER);

//     struct Node_t* r = Differentiator (node->right);
//     struct Node_t* l = Build_node (_DIV, "@", 0, l_l, l_r, OPERATION);

//     struct Node_t* main_node = Build_node (_MUL, "@", 0, l, r, OPERATION);
// }

// struct Node_t* Derivative_arccos (Node_t* node)
// {
//     struct Node_t* l_r_l_r_r = Build_node (_NOTHING, "@", 2, NULL, NULL, NUMBER);
//     struct Node_t* l_r_l_r_l = Copy_tree (node->right);

//     struct Node_t* l_r_l_r = Build_node (_DEG, "@", 10, l_r_l_r_l, l_r_l_r_r, OPERATION);
//     struct Node_t* l_r_l_l = Build_node (_NOTHING, "@", 1, NULL, NULL, NUMBER);
//     struct Node_t* l_r_r_l = Build_node (_NOTHING, "@", 1, NULL, NULL, NUMBER);
//     struct Node_t* l_r_r_r = Build_node (_NOTHING, "@", 2, NULL, NULL, NUMBER);

//     struct Node_t* l_r_r = Build_node (_DIV, "@", 10, l_r_r_l, l_r_r_r, OPERATION);
//     struct Node_t* l_r_l = Build_node (_SUB, "@", 10, l_r_l_l, l_r_l_r, OPERATION);
//     struct Node_t* l_l_l = Build_node (_SUB, "@", 10, NULL, NULL, OPERATION);
//     struct Node_t* l_l_r = Build_node (_NOTHING, "@", 1, NULL, NULL, NUMBER);

//     struct Node_t* l_r = Build_node (_DEG, "@", 10, l_r_l, l_r_r, OPERATION);
//     struct Node_t* l_l = Build_node (_MUL, "@", 1, l_l_l, l_l_r, OPERATION);

//     struct Node_t* r = Differentiator (node->right);
//     struct Node_t* l = Build_node (_DIV, "@", 0, l_l, l_r, OPERATION);

//     struct Node_t* main_node = Build_node (_MUL, "@", 0, l, r, OPERATION);
// }

// struct Node_t* Derivative_arctg (Node_t* node)
// {
//     struct Node_t* l_r_r_l = Copy_tree (node->right);
//     struct Node_t* l_r_r_r = Build_node (_NOTHING, "@", 2, NULL, NULL, NUMBER);

//     struct Node_t* l_r_l = Build_node (_NOTHING, "@", 1, NULL, NULL, NUMBER);
//     struct Node_t* l_r_r = Build_node (_DEG, "@", 10, l_r_r_l, l_r_r_r, OPERATION);

//     struct Node_t* l_l = Build_node (_NOTHING, "@", 1, NULL, NULL, NUMBER);
//     struct Node_t* l_r = Build_node (_ADD, "@", 1, l_r_l, l_r_r, OPERATION);

//     struct Node_t* r = Differentiator (node->right);
//     struct Node_t* l = Build_node (_DIV, "@", 0, l_l, l_r, OPERATION);

//     struct Node_t* main_node = Build_node (_MUL, "@", 0, l, r, OPERATION);
// }

// struct Node_t* Derivative_arcctg (Node_t* node)
// {
//     struct Node_t* l_r_r_l = Copy_tree (node->right);
//     struct Node_t* l_r_r_r = Build_node (_NOTHING, "@", 2, NULL, NULL, NUMBER);

//     struct Node_t* l_r_l = Build_node (_NOTHING, "@", 1, NULL, NULL, OPERATION);
//     struct Node_t* l_r_r = Build_node (_DEG, "@", 10, l_r_r_l, l_r_r_r, OPERATION);
//     struct Node_t* l_l_l = Build_node (_SUB, "@", 10, NULL, NULL, OPERATION);
//     struct Node_t* l_l_r = Build_node (_NOTHING, "@", 1, NULL, NULL, NUMBER);

//     struct Node_t* l_l = Build_node (_MUL, "@", 10, l_l_l, l_l_r, OPERATION);
//     struct Node_t* l_r = Build_node (_ADD, "@", 10, l_r_l, l_r_r, OPERATION);

//     struct Node_t* r = Differentiator (node->right);
//     struct Node_t* l = Build_node (_DIV, "@", 0, l_l, l_r, OPERATION);

//     struct Node_t* main_node = Build_node (_MUL, "@", 0, l, r, OPERATION);
// }

// struct Node_t* Derivative_sh (Node_t* node)
// {
//     struct Node_t* l_r = Copy_tree (node->right);
//     struct Node_t* l_l = Build_node ( _NOTHING, "@", 10, NULL, NULL, OPERATION);

//     struct Node_t* r = Differentiator (node->right);
//     struct Node_t* l = Build_node (_CH, "@", 10, l_l, l_r, OPERATION);

//     struct Node_t* main_node = Build_node (_MUL, "@", 10, l, r, OPERATION);
// }

// struct Node_t* Derivative_ch (Node_t* node)
// {
//     struct Node_t* l_r = Copy_tree (node->right);
//     struct Node_t* l_l = Build_node (_NOTHING, "@", 10, NULL, NULL, OPERATION);

//     struct Node_t* r = Differentiator (node->right);
//     struct Node_t* l = Build_node (_SH, "@", 10, l_l, l_r, OPERATION);

//     struct Node_t* main_node = Build_node (_MUL, "@", 10, l, r, OPERATION);
// }

// struct Node_t* Derivative_th (Node_t* node)
// {
//     struct Node_t* l_r_l_l = Build_node (_NOTHING, "@", 10, NULL, NULL, OPERATION);
//     struct Node_t* l_r_l_r = Copy_tree (node->right);

//     struct Node_t* l_r_r = Build_node (_NOTHING, "@", 2, NULL, NULL, NUMBER);
//     struct Node_t* l_r_l = Build_node (_CH, "@", 10, l_r_l_l, l_r_l_r, OPERATION);

//     struct Node_t* l_r = Build_node (_DEG, "@", 10, l_r_l, l_r_r, OPERATION);
//     struct Node_t* l_l = Build_node (_NOTHING, "@", 1, NULL, NULL, NUMBER);

//     struct Node_t* r = Differentiator (node->right);
//     struct Node_t* l = Build_node (_DIV, "@", 0, l_l, l_r, OPERATION);

//     struct Node_t* main_node = Build_node (_MUL, "@", 0, l, r, OPERATION);
// }

// struct Node_t* Derivative_cth (Node_t* node)
// {
//     struct Node_t* l_r_l_l = Build_node (_NOTHING, "@", 10, NULL, NULL, OPERATION);
//     struct Node_t* l_r_l_r = Copy_tree (node->right);

//     struct Node_t* l_r_r = Build_node (_NOTHING, "@", 2, NULL, NULL, NUMBER);
//     struct Node_t* l_r_l = Build_node (_SH, "@", 10, l_r_l_l, l_r_l_r, OPERATION);
//     struct Node_t* l_l_l = Build_node (_SUB, "@", 10, NULL, NULL, OPERATION);
//     struct Node_t* l_l_r = Build_node (_NOTHING, "@", 1, NULL, NULL, NUMBER);

//     struct Node_t* l_r = Build_node (_DEG, "@", 10, l_r_l, l_r_r, OPERATION);
//     struct Node_t* l_l = Build_node (_MUL, "@", 10, l_l_l, l_l_r, OPERATION);

//     struct Node_t* r = Differentiator (node->right);
//     struct Node_t* l = Build_node (_DIV, "@", 0, l_l, l_r, OPERATION);

//     struct Node_t* main_node = Build_node (_MUL, "@", 10, l, r, OPERATION);
// }

// struct Node_t* Derivative_log (Node_t* node)
// {
//     struct Node_t* l_r_r_l = Build_node (_NOTHING, "@", 10, NULL, NULL, OPERATION);
//     struct Node_t* l_r_r_r = Copy_tree (node->left);

//     struct Node_t* l_r_r = Build_node (_LN, "@", 0, l_r_r_l, l_r_r_r, OPERATION);
//     struct Node_t* l_r_l = Copy_tree (node->left);

//     struct Node_t* l_r = Build_node (_MUL, "@", 0, l_r_l, l_r_r, OPERATION); 
//     struct Node_t* l_l = Build_node (_NOTHING, "@", 1, NULL, NULL, NUMBER);

//     struct Node_t* r = Differentiator (node->right);
//     struct Node_t* l = Build_node (_DIV, "@", 0, l_l, l_r, OPERATION);

//     struct Node_t* main_node = Build_node (_MUL, "@", 0, l, r, OPERATION);
// }

// struct Node_t* Derivative_ln (Node_t* node)
// {
//     struct Node_t* l_r = Copy_tree (node->right); 
//     struct Node_t* l_l = Build_node (_NOTHING, "@", 1, NULL, NULL, NUMBER);

//     struct Node_t* r = Differentiator (node->right);
//     struct Node_t* l = Build_node (_DIV, "@", 0, l_l, l_r, OPERATION);

//     struct Node_t* main_node = Build_node (_MUL, "@", 0, l, r, OPERATION);
// }