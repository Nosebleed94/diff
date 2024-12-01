#include "string.h"
#include "stdio.h"
#include <iostream>
#include <cstdlib>

#include "derevtso.h"
#include  "copy_tree.h"

struct Node_t* Copy_tree (Node_t* node)
{
    if (node == NULL)
    {
        return NULL;
    }
    fprintf (stderr,"принимаемый адрес [%p]\n", node);

    Node_t* copynode = (struct Node_t*)calloc(1, sizeof(struct Node_t));
    copynode->elem.variable = (char*)calloc(2, sizeof(char));
    copynode->elem.number = node->elem.number;
    //fprintf (stderr,"адрес копиноуд намбера [%d]\n", &(copynode->elem.number));
    //fprintf (stderr,"адрес намбера [%d]\n", &(node->elem.number));
    copynode->elem.operation = node->elem.operation;
    //fprintf (stderr,"адрес копиноуд оператиона [%d]\n", &(copynode->elem.operation));
    //fprintf (stderr,"адрес оператион [%d]\n", &(node->elem.operation));
    strcpy (copynode->elem.variable, node->elem.variable); 
    //fprintf (stderr,"адрес копиноуд вариэбла [%d]\n", &(copynode->elem.variable));
    //fprintf (stderr,"адрес вариэбл [%d]\n", &(node->elem.variable));
    copynode->type = node->type;
    copynode->left = Copy_tree(node->left);
    copynode->right = Copy_tree (node->right);

    fprintf (stderr,"возвращаемый адрес в копии [%p]\n", copynode);
    return copynode;

}