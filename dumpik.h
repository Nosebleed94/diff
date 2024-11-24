#ifndef DUMPIK_H
#define DUMPIK_H

#include <stdlib.h>
#include <stdio.h>

const char yes[] = "yes";
const char no[] = "no";

const char adding_html_first[] = "\n"
                                "digraph structs {\n"
                                "charset = \"UTF-8\";\n"
                                "rankdir=TB;\n"
                                "bgcolor = \"#0000aa\";\n"
                                "fontcolor = black;\n"
                                "fontsize = 18;\n"
                                "style = \"rounded\";\n"
                                "margin = 0.3;\n"
                                "ranksep = 1.0;\n"
                                "nodesep = 0.9;\n"
                                "bgcolor = \"#FFFFFF\";\n"
                                "edge [color=\"#FFFFFF\"];\n"
                                "\n";

void Dump_moment         (struct Node_t* node);
void Print_dot           (struct Node_t* node, FILE* file);
void Print_struct_node   (struct Node_t* node, FILE* file);

#endif // DUMPIK_H