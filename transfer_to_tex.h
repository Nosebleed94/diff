#ifndef TRANSFER_TO_TEX_H
#define TRANSFER_TO_TEX_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void Print_derivative_to_tex (struct Node_t* node, FILE* file_tex);
void Transfer_to_tex (struct Node_t* node, struct Node_t* diff, FILE* file_tex);

#endif //TRANSFER_TO_TEX_H

