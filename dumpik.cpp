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
    long seconds = tv.tv_sec;
    long microseconds = tv.tv_usec;
    char filename[SIZE_FILENAME] = {0};
    snprintf (filename, sizeof(filename), "file_%ld_%06ld.dot",  seconds, microseconds);
    
    FILE* file_html = fopen ("dump.html", "a+");
    assert (file_html && "file open err");

    FILE* file_dump = fopen (filename, "a+");
    assert (file_dump && "file open err");

    fprintf (file_dump, "%s", adding_html_first);

    Print_struct_Node (Node, file_dump);
    
    Print_dot (Node, file_dump);

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

void Print_dot (struct Node_t* Node, FILE* file)
{
    assert (Node);

    if (!Node) return; 

    if (Node->right)
    {
        fprintf   (file,"%s:<f2> -> %s\n", Node->name_Node, Node->right->name_Node);
        Print_dot (Node->right, file);
    }
    if (Node->left)
    {
        fprintf   (file, "%s:<f1> -> %s\n", Node->name_Node, Node->left->name_Node);
        Print_dot (Node->left, file);
    }
}

void Print_struct_Node (struct Node_t* Node, FILE* file)
{
    assert (Node);
    if (!Node) return;
    
    if (Node->type == FIRST)
    {
        printf ("type one = [%s]\n", Node->elem.variable);
        void* pointer = (void*)(uintptr_t)Node->elem.variable;  
        fprintf (file, "%s[shape=record, label= \"{type: %d| value: %s | {<f1> L | <f2> R}}\", style=filled, fillcolor=\"lightcyan\", color=\"cyan\"];\n", 
        Node->name_Node, Node->type, Node->elem.variable);
    }

    if (Node->type == THIRD)
    {
        fprintf (stderr,"Node = [%d]\n", Node->elem.operation);
        void* pointer = (void*)(uintptr_t)Node->elem.operation;
        fprintf (file, "%s[shape=record, label= \"{type: %d| value: %s | {<f1> L | <f2> R}}\",style=filled, fillcolor=\"lightgreen\", color=\"green\"];\n", 
        Node->name_Node, Node->type, Defining_operations_for_dump (Node->elem.operation));
    }

    if (Node->type == SECOND)
    {
        void* pointer = (void*)(uintptr_t)Node->elem.number;
        fprintf (file, "%s[shape=record, label= \"{type: %d| value: %d | {<f1> L | <f2> R}}\",style=filled, fillcolor=\"lightpink\", color=\"pink\"];\n", 
        Node->name_Node, Node->type, Node->elem.number);
    }

    if (Node->left)   {Print_struct_Node (Node->left, file);}
    if (Node->right)  {Print_struct_Node (Node->right, file);}
    
}
