#ifndef TOKEN_CLASSIFICATION_H
#define TOKEN_CLASSIFICATION_H 

#include "meta.h"
#include "stringManipulation.h"

/*---------Function Prototype---------*/ 

void setMode( int* MODE,Strings_list* list);

void setVar( Variable_table** var_table,Strings_list* list);

void setLabel( Symbols_table** s_table, int IC, Strings_list* list );

void setInstruction( Instru_list** instru_list, int typeOfInstr, int IC, Strings_list* list );

int  legalLiteral( char* p );

int  classifyInstruction( char* token );

int  classifyToken( char* token,int lineNumber );

int  classifyImmediate( char* imme, int lineNumber );

#endif 
