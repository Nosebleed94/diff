#ifndef FILBUF_H
#define FILBUF_H

#include <stdlib.h>
#include <stdio.h>

size_t Get_file_size   (FILE* file_derevtso);
char* Filling_buffer   (FILE* file_derevtso, char** arr);

#endif // FILBUF_H