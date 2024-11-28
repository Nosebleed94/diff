#ifndef DIFFERENTIATOR_H
#define DIFFERENTIATOR_H

struct Node_t* Differentiator (Node_t* node);
struct Node_t* Derivative_const (Node_t* node);
struct Node_t* Derivative_variable (Node_t* node);
struct Node_t* Derivative_operation (int operation, Node_t* node);

#endif // DIFFERENTIATOR_H