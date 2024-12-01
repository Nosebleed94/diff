#ifndef DIFFERENTIATOR_H
#define DIFFERENTIATOR_H

#include "derevtso.h"

struct Node_t* Differentiator (Node_t* node);
struct Node_t* Derivative_const (Node_t* node);
struct Node_t* Derivative_variable (Node_t* node);
struct Node_t* Derivative_operation (int operation, Node_t* node);
struct Node_t* Build_node (int operation, char* variable, double umber, Node_t* left, Node_t* right, type_Node type);
struct Node_t* Derivative_add (Node_t* node);
struct Node_t* Derivative_sub (Node_t* node);
struct Node_t* Derivative_mul (Node_t* node);
struct Node_t* Derivative_div (Node_t* node);
struct Node_t* Derivative_sin (Node_t* node);
struct Node_t* Derivative_cos (Node_t* node);
struct Node_t* Derivative_tg  (Node_t* node);
struct Node_t* Derivative_ctg (Node_t* node);
struct Node_t* Derivative_arcsin (Node_t* node);
struct Node_t* Derivative_arccos (Node_t* node);
struct Node_t* Derivative_arctg (Node_t* node);
struct Node_t* Derivative_arcctg (Node_t* node);
struct Node_t* Derivative_sh (Node_t* node);
struct Node_t* Derivative_ch (Node_t* node);
struct Node_t* Derivative_th (Node_t* node);
struct Node_t* Derivative_cth (Node_t* node);
struct Node_t* Derivative_log (Node_t* node);
struct Node_t* Derivative_ln (Node_t* node);

#endif // DIFFERENTIATOR_H