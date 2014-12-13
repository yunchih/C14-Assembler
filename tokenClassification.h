#ifndef TOKEN_CLASSIFICATION_H
#define TOKEN_CLASSIFICATION_H 

#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "meta.h"
#include "stringManipulation.h"

/*---------Function Prototype---------*/ 

void setMode( int* MODE,Strings_list* list);

void setVar( Variable_table** var_table,Strings_list* list);

void setLabel( Symbols_table** s_table, int IC, Strings_list* list );

void setInstruction( Instru_list** instru_list, int typeOfInstr, int IC, Strings_list* list );

int  classifyInstruction( char* token );

static int  legalLiteral( char* p );

static int  classifyToken( char* token,int lineNumber );

static int  isImmediate( char* imme );


#endif 
