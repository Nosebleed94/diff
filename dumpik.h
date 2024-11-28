#ifndef DUMPIK_H
#define DUMPIK_H

#include <stdlib.h>
#include <stdio.h>

const char right[] = "right";
const char left[] = "left";

const char adding_html_X[] = "\n"
                                "digraph structs {\n"
                                "charset = \"UTF-8\";\n"
                                "rankdir=TB;\n"
                                "bgcolor = \"#0000aa\";\n"
                                "fontcolor = black;\n"
                                "fontsize = 18;\n"
                                "style = \"rounded\";\n"
                                "margin = 0.3;\n"
                                "ranksep = 1.0;\n"
                                "Nodesep = 0.9;\n"
                                "bgcolor = \"#FFFFFF\";\n"
                                "edge [color=\"#000000\"];\n"
                                "\n";

void Dump_moment                         (struct Node_t* Node);
void Print_dot                           (struct Node_t* Node, FILE* file);
void Print_struct_Node                   (struct Node_t* Node, FILE* file);

#endif // DUMPIK_H