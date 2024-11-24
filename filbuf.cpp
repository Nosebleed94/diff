#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "filbuf.h"
#include "derevtso.h"

size_t Get_file_size (FILE* file_derevtso)
{
    assert (file_derevtso);

    fseek (file_derevtso, 0, SEEK_END);
    long int position = ftell (file_derevtso);
    size_t quentity_symbols = (size_t)position / sizeof(char);
    fseek (file_derevtso, 0, SEEK_SET);

    return quentity_symbols;
}

char* Filling_buffer (FILE* file_derevtso, char** arr)
{
    size_t size_arr = Get_file_size (file_derevtso);
    
    assert (file_derevtso);
    assert (**arr);

    *arr = (char*)calloc(size_arr + 1, sizeof(char));
    assert (*arr);

    fread (*arr, sizeof(char), size_arr, file_derevtso);
    return *arr;
}