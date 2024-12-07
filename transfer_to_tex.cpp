#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "derevtso.h"
#include "defining_operation.h"
#include "optimisation.h"
#include "transfer_to_tex.h"

void Transfer_to_tex (struct Node_t* node, struct Node_t* diff, FILE* file_tex)
{
    fprintf(file_tex, "\\documentclass{article}\n"
                  "\\usepackage{graphicx} %% Required for inserting images\n"
                  "\\usepackage[russian]{babel}\n"
                  "\\usepackage[T1]{fontenc}\n"
                  "\\usepackage[utf8]{inputenc}\n"
                  "\\usepackage{amsmath,amssymb}\n"
                  "\\usepackage[russian,english]{babel}\n"
                  "%% Картинки\n"
                  "\\graphicspath{{images/}}\n"
                  "\\DeclareGraphicsExtensions{.pdf,.png,.jpg}\n"
                  "\\usepackage{wrapfig}\n"
                  "\\begin{document}\n");
    fprintf (file_tex, "Здравствуй, пользователь.\\\\\n" 
                        "Вижу, тебе нужна помощь со взятием производной.\\\\\n"
                        "Ну что-ж, давай приступим\\\\\n"
                        "Твоя функция выглядит так\\\\\n");

    fprintf (file_tex, "\\[\n");
    fprintf (file_tex, "f(x) = ");
    Print_derivative_to_tex (node, file_tex); 
    fprintf (file_tex, "\n\\]\n"); 

    fprintf (file_tex, "Производная от твой функции будет выглядеть вот так:\\\\\n");

    fprintf (file_tex, "\\[\n");
    fprintf (file_tex, "(f(x))' = ");
    Print_derivative_to_tex (diff, file_tex); 
    fprintf (file_tex, "\n\\]\n");

    fprintf (file_tex, "Спасибо, что воспользовался моей программой, удачи\\\\\n"
                       "\\end{document}");

} 
void Print_derivative_to_tex (struct Node_t* node, FILE* file_tex) 
{
    if (node == NULL) 
    {
        return;
    }

    if (node->type == OPERATION && node->elem.operation == _DIV) 
    {
        fprintf (file_tex, "{"); 
        
        Print_derivative_to_tex (node->left, file_tex);
        
        fprintf(file_tex, "\\over "); 
        
        Print_derivative_to_tex (node->right, file_tex);
        
        fprintf(file_tex, "}"); 
    } 

    if (node->type == OPERATION && node->elem.operation == _DEG) 
    {
        
        Print_derivative_to_tex (node->left, file_tex);
        
        fprintf(file_tex, "^{");
        
        Print_derivative_to_tex (node->right, file_tex);
        
        fprintf(file_tex, "}"); 
    } 

    if (node->type == OPERATION && node->elem.operation != _ADD 
                                && node->elem.operation != _SUB
                                && node->elem.operation != _MUL
                                && node->elem.operation != _DIV
                                && node->elem.operation != _DEG)
    {
        fprintf(file_tex, "\\%s (", Defining_operations_for_dump(node->elem.operation));
        Print_derivative_to_tex (node->left, file_tex);
        Print_derivative_to_tex (node->right, file_tex);
        fprintf(file_tex, ") "); 
    }

    else 
    {
        if (node->type == NUMBER) {fprintf(file_tex, "%0.2lf ", node->elem.number);}
        if (node->type == X)      {fprintf(file_tex, "%s", node->elem.variable);}
        if (node->type == OPERATION && node->elem.operation != _DIV && node->elem.operation != _DEG) 
        {
            Print_derivative_to_tex (node->left, file_tex);
            fprintf (file_tex, "%s ", Defining_operations_for_dump(node->elem.operation));
            Print_derivative_to_tex (node->right, file_tex);
        }
    }
}

