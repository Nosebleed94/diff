#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "derevtso.h"
#include "filbuf.h"
#include "dumpik.h"
#include "optimisation.h"
#include "copy_tree.h"
#include "differentiator.h"
#include "transfer_to_tex.h"

int main()
{
    FILE* file_derevtso = fopen ("function.txt", "r");
    assert (file_derevtso);

    char* arr =  Filling_buffer (file_derevtso, &arr);

    arr++;

    struct Node_t* Node = Сonverter_tree (&arr, NULL);
    assert (Node);

    Dump_moment (Node);

    First_optimisation (Node);

    // // Dump_moment (Node);

    Second_optimisation (Node);

    // Dump_moment (Node);

    struct Node_t* Diff = Differentiator (Node);

    Dump_moment (Diff);

    First_optimisation (Diff);

    Second_optimisation (Diff);

    First_optimisation (Diff);

    Second_optimisation (Diff);

    Dump_moment (Diff);

    FILE* file_tex = fopen ("derivative.txt", "w");

    Transfer_to_tex (Node, Diff, file_tex);

    fclose (file_tex);

    Deductr (Node);

    Deductr (Diff);

    return 0;

}