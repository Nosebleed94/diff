#ifndef OPTIMISATION_H
#define OPTIMISATION_H

#include "derevtso.h"
#include "operation.h"
#include "enum_operation.h"

void First_optimisation                           (Node_t* Node);
void Second_optimisation                          (Node_t* node);
void First_deducr_certain_node                    (Node_t* node);
Node_t* First_optimisation_operation_with_node    (Node_t* node);
Node_t* Second_optimisation_operation_with_node   (Node_t* node);

#endif // OPTIMISATION_H