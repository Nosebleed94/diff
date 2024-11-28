#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include <iostream>
#include <assert.h>

#include "derevtso.h"
#include "dumpik.h"
#include "defining_operation.h"

void Dump_moment (struct Node_t* Node)
{
    assert (Node);
    
    struct timeval tv;
    gettimeofday (&tv, NULL);
    long NUMBERs = tv.tv_sec;
    long microNUMBERs = tv.tv_usec;
    char filename[SIZE_FILENAME] = {0};
    snprintf (filename, sizeof(filename), "file_%ld_%06ld.dot",  NUMBERs, microNUMBERs);
    
    FILE* file_html = fopen ("dump.html", "a+");
    assert (file_html && "file open err");

    FILE* file_dump = fopen (filename, "a+");
    assert (file_dump && "file open err");

    fprintf (file_dump, "%s", adding_html_X);

    Print_struct_Node (Node, file_dump);
    
    Print_dot (Node, file_dump);

    char command[SIZE_COMMAND] = {};
    snprintf (command, sizeof(command), "dot -Tpng %s -o %.22s.png", filename, filename);
    snprintf (filename, sizeof(filename), "file_%ld_%06ld.png",  NUMBERs, microNUMBERs);
    fprintf  (file_html, "\t<img src=\"%s\"/>\n", filename);
    fprintf  (file_dump, "}\n");
    fclose   (file_dump);   
    system   (command);
    fclose   (file_html);

    return;
}

void Print_dot (struct Node_t* Node, FILE* file)
{
    assert (Node);

    if (!Node) return; 

    if (Node->right)
    {
        fprintf   (file,"%d:<f2> -> %d\n", &(Node->elem), &(Node->right->elem));
        Print_dot (Node->right, file);
    }
    if (Node->left)
    {
        fprintf   (file, "%d:<f1> -> %d\n", &(Node->elem), &(Node->left->elem));
        Print_dot (Node->left, file);
    }
}

void Print_struct_Node (struct Node_t* Node, FILE* file)
{
    assert (Node);
    if (!Node) return;
    
    if (Node->type == X)
    {
        void* pointer = (void*)(uintptr_t)Node->elem.variable;  
        fprintf (file, "%d[width=2, shape=record, label= \"{ip: %p| type: %d| value: %s | {<f1> L | <f2> R}}\", style=filled, fillcolor=\"lightcyan\", color=\"cyan\"];\n", 
        &(Node->elem),  Node->elem.variable, Node->type, Node->elem.variable);
    }

    if (Node->type == OPERATION)
    {
        void* pointer = (void*)(uintptr_t)Node->elem.operation;
        fprintf (file, "%d[width=2, shape=record, label= \"{ip: %p| type: %d| value: %s | {<f1> L | <f2> R}}\",style=filled, fillcolor=\"lightgreen\", color=\"green\"];\n", 
        &(Node->elem), Node->elem.operation,  Node->type, Defining_operations_for_dump (Node->elem.operation));
    }

    if (Node->type == NUMBER)
    {
        void* pointer = (void*)(uintptr_t)Node->elem.number;
        fprintf (file, "%d[width=2, shape=record, label= \"{ip: %p| type: %d| value: %d | {<f1> L | <f2> R}}\",style=filled, fillcolor=\"lightpink\", color=\"pink\"];\n", 
        &(Node->elem), Node->elem.number, Node->type, Node->elem.number);
    }

    if (Node->left)   {Print_struct_Node (Node->left, file);}
    if (Node->right)  {Print_struct_Node (Node->right, file);}
    
}