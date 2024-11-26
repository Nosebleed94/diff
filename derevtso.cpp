#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "derevtso.h"
#include "defining_operation.h"

struct Node_t* create_Node (char* data, Node_t* Node)
{
    assert (data);

    struct Node_t* newNode = (struct Node_t*)calloc(1, sizeof(struct Node_t));
    if (Type_definition(data) == FIRST)
    {
        newNode->elem.variable = (char*)calloc(strlen(data) + 1, sizeof(char));
        newNode->type = FIRST;
        newNode->elem.number = 0;
        newNode->elem.operation = 0;

        strcpy (newNode->elem.variable, data); 
        
    }
    if (Type_definition(data) == THIRD)
    {
        newNode->elem.variable = (char*)calloc(2, sizeof(char)); 
        newNode->type = THIRD;
        newNode->elem.number = 0;
        
        newNode->elem.operation = Defining_operation_for_Node (data); 
        printf ("Node = [%s]  ", data);
        printf ("operation = [%d]\n", newNode->elem.operation);
        strcpy (newNode->elem.variable, "@");
    }
    if (Type_definition(data) == SECOND)
    {
        newNode->type = SECOND;
        newNode->elem.number = atoi(data);
        newNode->elem.variable = (char*)calloc(2, sizeof(char)); 
        newNode->elem.operation = 0;
        strcpy (newNode->elem.variable, "@");
    }
    newNode->otets = Node;

    assign_random_number_to_name(newNode);

    newNode->left  = NULL;
    newNode->right = NULL;

    return newNode;
}

struct Node_t* Сonverter_tree (char** arr, Node_t* otets)
{
    // assert на отца не нужен
    assert (arr);

    char word [SIZE_OBJECT] = "";
    
    Read_word (arr, word);

    struct Node_t* Node = create_Node (word, otets);

    arr += Quentity_letters_in_word (*arr);
    
    if (**arr == '{')
    {
        (*arr)++; 
        Node->left = Сonverter_tree(arr, Node);
        (*arr)++; 
    }

    if (**arr == '{')
    {
        (*arr)++; 
        Node->right = Сonverter_tree (arr, Node);
        (*arr)++;
    }

    return Node;
}

void Read_word (char** arr, char* word)
{
    assert (arr && word);

    char* remember_position = *arr;

    while (**arr != '{' && **arr != '}' && **arr != '\0')
    {
        (*arr)++;
    }
    
    strncpy (word, remember_position, *arr - remember_position);
}

int Quentity_letters_in_word (char* arr)
{
    assert (arr);

    int i = 0;
    while (arr[i] != '{' && arr[i] != '}' && arr[i] != '\0')
    {
        i++;
    }

    return i;
}

void Deductr (struct Node_t* Node)
{   
    //assert не нужен 
    if (Node)
    {
        Deductr   (Node->right);
        Deductr   (Node->left);
        free      (Node->elem.variable);
        free      (Node);
    }
}

enum type_Node Type_definition (char* data)
{
    if (strcmp (VARIABLE, data) == 0) 
    {
        return FIRST;
    }
    for (const char* p = data; *p != '\0'; p++) {if (!isdigit(*p)) {return THIRD;}}  
    return SECOND;
}

void assign_random_number_to_name(Node_t* Node) {
    if (Node == NULL) {
        return;
    }
    int random_number = rand() % 1000000 + 1;
    char buffer[10]; 
    sprintf(buffer, "%d", random_number);
    Node->name_Node = (char*)calloc(strlen(buffer) + 1, sizeof(char));
    strcpy(Node->name_Node, buffer);
}
