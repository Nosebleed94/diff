#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "derevtso.h"
#include "filbuf.h"
#include "dumpik.h"
#include "optimisation.h"
#include "copy_tree.h"

int main()
{
    FILE* file_derevtso = fopen ("function.txt", "r");
    assert (file_derevtso);

    char* arr =  Filling_buffer (file_derevtso, &arr);

    arr++;

    struct Node_t* Node = Сonverter_tree (&arr, NULL);
    assert (Node);

    struct Node_t* CopyNode = Copy_tree (Node);

    Dump_moment (CopyNode);

    Dump_moment (Node);

    First_optimisation (Node);

    Dump_moment (Node);

    Second_optimisation (Node);

    Dump_moment (Node);

    Deductr (Node);

    return 0;

}