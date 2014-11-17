#ifndef META_H
#define META_H

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

/* Mode */
enum { UNDEFINED , DATA , CODE } ;


typedef struct Token_struct 
{
	char* token;
	int type;
	struct Token_struct* next;
} Token;
typedef struct Tokens_list_struct 
{
	int lineNum;
	token* first_token;
	struct Tokens_list_struct* next ;
} Tokens_list;
typedef struct Symbols_table_struct
{
	char* symbol;
	int index;
	int lineNum;
	struct Symbols_table_struct* next ;
} Symbols_table;
typedef struct Variable_table_struct ;
{
	char* var;
	char* value;
	struct Variable_table_struct* next ;
} Variable_table ;
#endif
