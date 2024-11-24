#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "derevtso.h"

struct Node_t* create_node (char* data, Node_t* node)
{
    assert (data);

    struct Node_t* newNode = (struct Node_t*)calloc(1, sizeof(struct Node_t));

    if (Type_definition(data) == FIRST)
    {
        newNode->elem.variable = (char*)calloc(strlen(data) + 1, sizeof(char));
        newNode->elem.operation = (char*)calloc(2, sizeof(char)); 
        newNode->type = FIRST;
        strcpy (newNode->elem.variable, data);
        strcpy (newNode->elem.operation, "@");
        newNode->elem.number = 0;
    }
    if (Type_definition(data) == THIRD)
    {
        newNode->elem.operation = (char*)calloc(strlen(data) + 1, sizeof(char));
        newNode->elem.variable = (char*)calloc(2, sizeof(char)); 
        newNode->type = THIRD;
        strcpy (newNode->elem.operation, data);
        strcpy (newNode->elem.variable, "@");
        newNode->elem.number = 0;
    }
    else
    {
        newNode->type = SECOND;
        newNode->elem.number = atoi(data);
        newNode->elem.variable = (char*)calloc(2, sizeof(char)); 
        newNode->elem.operation = (char*)calloc(2, sizeof(char)); 
        strcpy (newNode->elem.operation, "@");
        strcpy (newNode->elem.variable, "@");
    }
    newNode->otets = node;
    newNode->no  = NULL;
    newNode->yes = NULL;
    return newNode;
}

struct Node_t* Сonverter_tree (char** arr, Node_t* otets)
{
    // assert на отца не нужен
    assert (arr);

    char word [SIZE_OBJECT] = "";
    
    Read_word (arr, word);

    struct Node_t* node = create_node (word, otets);

    arr += Quentity_letters_in_word (*arr);
    
    if (**arr == '{')
    {
        (*arr)++; 
        node->yes = Сonverter_tree(arr, node);
        (*arr)++; 
    }

    if (**arr == '{')
    {
        (*arr)++; 
        node->no = Сonverter_tree (arr, node);
        (*arr)++;
    }

    return node;
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

void Deductr (struct Node_t* node)
{   
    //assert не нужен 
    if (node)
    {
        Deductr   (node->yes);
        Deductr   (node->no);
        free      (node->elem.operation);
        free      (node->elem.variable);
        free      (node);
    }
}

enum type_node Type_definition (char* data)
{
    for (const char* p = data; *p != '\0'; p++) {if (!isdigit(*p)) {return THIRD;}}  
    if (strcmp (VARIABLE, data) == 0) {return FIRST;}
    else                              {return SECOND;}
}