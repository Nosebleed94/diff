#include "string.h"
#include "stdio.h"

#include "operation.h"
#include "defining_operation.h"
#include "operation.h"

enum operation Defining_operation_for_Node (char* data)
{
    printf ("data in func = {%s}\n", data);
    if (strcmp (ADD, data) == 0)     {return _ADD;}
    if (strcmp (SUB, data) == 0)     {return _SUB;}
    if (strcmp (MUL, data) == 0)     {return _MUL;}
    if (strcmp (DIV, data) == 0)     {return _DIV;}
    if (strcmp (DEG, data) == 0)     {return _DEG;}
    if (strcmp (SIN, data) == 0)     {return _SIN;}
    if (strcmp (COS, data) == 0)     {return _COS;}
    if (strcmp (TG, data) == 0)      {return _TG;}
    if (strcmp (CTG, data) == 0)     {return _CTG;}
    if (strcmp (ARCSIN, data) == 0)  {return _ARCSIN;}
    if (strcmp (ARCCOS, data) == 0)  {return _ARCCOS;}
    if (strcmp (ARCTG, data) == 0)   {return _ARCTG;}
    if (strcmp (ARCCTG, data) == 0)  {return _ARCCTG;}
    if (strcmp (SH, data) == 0)      {return _SH;}
    if (strcmp (CH, data) == 0)      {return _CH;}
    if (strcmp (TH, data) == 0)      {return _TH;}
    if (strcmp (CTH, data) == 0)     {return _CTH;}
    if (strcmp (LOG, data) == 0)     {return _LOG;}
    if (strcmp (LN, data) == 0)      {return _LN;}
    return _NOTHING;
}

const char* Defining_operations_for_dump (int operation)
{
    if (operation == _ADD)    {return ADD;}
    if (operation == _SUB)    {return SUB;}
    if (operation == _MUL)    {return MUL;}
    if (operation == _DIV)    {return DIV;}
    if (operation == _DEG)    {return DEG;}
    if (operation == _SIN)    {return SIN;}
    if (operation == _COS)    {return COS;}
    if (operation == _TG)     {return TG;}
    if (operation == _CTG)    {return CTG;}
    if (operation == _ARCSIN) {return ARCSIN;}
    if (operation == _ARCCOS) {return ARCCOS;}
    if (operation == _ARCTG)  {return ARCTG;}
    if (operation == _ARCCTG) {return ARCCTG;}
    if (operation == _SH)     {return SH;}
    if (operation == _CH)     {return CH;}
    if (operation == _TH)     {return TH;}
    if (operation == _CTH)    {return CTH;}
    if (operation == _LOG)    {return LOG;}
    if (operation == _LN)     {return LN;}
    return NOTHING;
}