#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H 

#include "meta.h"
#include "debug.h"

#define ToInt( value ) ((int) strtol( value , NULL , 0 ) )

/*---------Function Prototype---------*/

void generate_code(FILE* out, Instru_list* instru_list, Symbols_table* s_table, Variable_table* var_table );

static void write_variable( FILE* out, Variable_table* var_table, int* IC );
static void write_instructions(
	FILE* out,
	Instru_list* instru_list,
	Symbols_table* s_table,
	Variable_table* var_table,
    int IC );
static int findVariable( char* token , int* addr , Variable_table* var_table );
static int findSymbol( char* token , int* addr , Symbols_table* s_table );

#endif

