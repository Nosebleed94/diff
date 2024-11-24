#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "derevtso.h"
#include "filbuf.h"
#include "dumpik.h"

int main()
{
    FILE* file_derevtso = fopen ("function.txt", "r");
    assert (file_derevtso);

    char* arr =  Filling_buffer (file_derevtso, &arr);
    printf("{%s}", arr);

    arr++;

    struct Node_t* node = Сonverter_tree (&arr, NULL);
    assert (node);

    Dump_moment (node);

    Deductr (node);

    return 0;

}