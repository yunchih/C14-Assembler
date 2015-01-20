#ifndef META_H
#define META_H

#include "bitsOperation.h"

/*---------Useful Constant---------*/

#define MAX_TOKEN_LEN 30
#define MAX_INSTRU_LEN  5
#define MAX_SYMBOL_LEN 20
#define MAX_VAR_LEN 20
#define ERROR -1

/*---------Struct Declaration---------*/

typedef struct Token_struct 
{
	char* token;
	int type;
	struct Token_struct* next;
} Opr;
typedef struct Tokens_list_struct 
{
	int type;
	Opr* first_opr;
	int addr;
	struct Tokens_list_struct* next ;
} Instru_list;
typedef struct Symbols_table_struct
{
	char* symbol;
	int addr;
	struct Symbols_table_struct* next ;
} Symbols_table;
typedef struct Variable_table_struct 
{
	char* var;
	char* value;
	int addr;
	short size;
	struct Variable_table_struct* next ;
} Variable_table ;

typedef struct
{
	int op;
	char name[ MAX_INSTRU_LEN ];
	// int len;
	enum Format format;
}Instructions_table;

/*---------Function Prototype---------*/

void printError( char* errorMessage , int lineNumber );

/*---------Global Variable---------*/

extern Instructions_table instructions_table[]; 

extern int ErrorCount;

extern int instructions_table_size;

enum 
{
	TK_LITERAL,
	TK_VAR,
	TK_CONST,
	TK_IMME,
	TK_REG,
	TK_MEM,
	TK_UNIN_IMME,
	TK_NON_IMME,
	TK_ERROR
};

/*---------Mode---------*/

enum { UNDEFINED , DATA , CODE } ;


#endif
