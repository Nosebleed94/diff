#ifndef DEREVTSO_H
#define DEREVTSO_H

const int SIZE_FILENAME = 100;
const int SIZE_COMMAND  = 256;
const int SIZE_ANSWER   = 4;
const int SIZE_SING     = 100;
const int SIZE_OBJECT   = 25;

enum type_node 
{
    FIRST   = 1,     //x
    SECOND  = 2,     //число
    THIRD   = 3,     //операция
};

struct Elem_t
{
    char* operation;
    char* variable;
    int number;
};

struct Node_t
{
    char* data_node;
    Node_t* no;
    Node_t* yes;
    Node_t* otets;
    type_node type;
};

struct Node_t* Сonverter_tree     (char** arr, Node_t* otets);
void Read_word                    (char** arr, char* word);
Node_t* create_node               (char* data, Node_t* node);
int Quentity_letters_in_word      (char* arr);
void Deductr                      (struct Node_t* node);

#endif // DEREVTSO_H