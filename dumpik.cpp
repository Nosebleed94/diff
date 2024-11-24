#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include <iostream>
#include <assert.h>

#include "derevtso.h"
#include "dumpik.h"

void Dump_moment (struct Node_t* node)
{
    assert (node);
    
    struct timeval tv;
    gettimeofday (&tv, NULL);
    long seconds = tv.tv_sec;
    long microseconds = tv.tv_usec;
    char filename[SIZE_FILENAME] = {0};
    snprintf (filename, sizeof(filename), "file_%ld_%06ld.dot",  seconds, microseconds);
    
    FILE* file_html = fopen ("dump.html", "a+");
    assert (file_html && "file open err");

    FILE* file_dump = fopen (filename, "a+");
    assert (file_dump && "file open err");

    fprintf (file_dump, "%s", adding_html_first);

    Print_struct_node (node, file_dump);
    
    //Print_dot (node, file_dump);

    char command[SIZE_COMMAND] = {};
    snprintf (command, sizeof(command), "dot -Tpng %s -o %.22s.png", filename, filename);
    snprintf (filename, sizeof(filename), "file_%ld_%06ld.png",  seconds, microseconds);
    fprintf  (file_html, "\t<img src=\"%s\"/>\n", filename);
    fprintf  (file_dump, "}\n");
    fclose   (file_dump);   
    system   (command);
    fclose   (file_html);

    return;
}

void Print_dot (struct Node_t* node, FILE* file)
{
    assert (node);

    if (!node) return; 

    if (node->yes)
    {
        fprintf   (file,"%s:<f2> -> %s\n", node->elem, node->yes->elem);
        Print_dot (node->yes, file);
    }
    if (node->no)
    {
        fprintf   (file, "%s:<f1> -> %s\n", node->elem, node->no->elem);
        Print_dot (node->no, file);
    }
}

void Print_struct_node (struct Node_t* node, FILE* file)
{
    assert (node);

    if (!node) return; 

    if (strcmp (node->elem.operation, "@") == 0 && node->elem.number == 0)
    {
        void* pointer = (void*)(uintptr_t)node->elem.variable;
        char address[20]; 
        sprintf(address, "%p", pointer);  
        fprintf (file, "%s[shape=record, label= \"{type: %d| value: %s | {<f1> L | <f2> N}}\", style=filled, fillcolor=\"lightcyan\", color=\"cyan\"];\n", 
        address + 2, node->type, node->elem.variable);
    }

    if (strcmp (node->elem.variable, "@") == 0 && node->elem.number == 0)
    {
        void* pointer = (void*)(uintptr_t)node->elem.operation;
        char address[20]; 
        sprintf(address, "%p", pointer);  
        fprintf (file, "%s[shape=record, label= \"{type: %d| value: %s | {<f1> L | <f2> N}}\",style=filled, fillcolor=\"lightgreen\", color=\"green\"];\n", 
        address + 2, node->type, node->elem.operation);
    }

    else
    {
        void* pointer = (void*)(uintptr_t)node->elem.number;
        char address[20]; 
        sprintf(address, "%p", pointer);  
        fprintf (file, "%s[shape=record, label= \"{type: %d| value: %d | {<f1> L | <f2> N}}\",style=filled, fillcolor=\"lightpink\", color=\"pink\"];\n", 
        address+ 2, node->type, node->elem.number);
    }

    if (node->no)   {Print_struct_node (node->no, file);}
    if (node->yes)  {Print_struct_node (node->yes, file);}
}