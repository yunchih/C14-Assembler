#include "identifier.hpp"
#include "main.hpp"
#include "instructionTable.hpp"
#include <cstdio>
#include <cstdlib>
#include <string> using namespace std; 
extern int yyparse( int IC, enum Pass pass, SymbolTable* table, Op_table* op_table );

int main(int argc, char *argv[])
{
    Op_table op_table;
    initialize( &op_table );

    int IC = 0;
    yyparse( IC,FIRST ); /* First pass */
	return 0;
} 
