#ifndef META_H
#define META_H

/*---------Useful Constant---------*/

#define MAX_INSTRU_LEN  5
#define MAX_SYMBOL_LEN 20
#define MAX_VAR_LEN 20
#define ERROR -1

/*---------Function Prototype---------*/

void printError( char* errorMessage , int lineNumber );

/*---------Global Variable---------*/

extern int INSTRU_TABLE_SIZE;

enum 
{
	TK_SYMBOL,
	TK_INST,
	TK_REG,
	TK_HEX,
	TK_DEC,
	TK_UNIN_IMME,
	TK_NON_IMME,
	TK_ERROR
}
enum
{
	ERR_INV_REG,
	ERR_INV_IMM,
	ERR_INV_SYMBOL
}

/*---------Mode---------*/

enum { UNDEFINED , DATA , CODE } ;

typedef enum FmtType { REG,MEM,CON } FmtType ;

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
typedef struct Variable_table_struct ;
{
	char* var;
	char* value;
	int type;
	int addr;
	struct Variable_table_struct* next ;
} Variable_table ;

typedef struct
{
	int op;
	char name[ MAX_INSTRU_LEN ];
	int len;
	int fmt[3];
}Instructions_table;

#endif
