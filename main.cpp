#include "identifier.hpp"
#include "main.hpp"
#include "instructionTable.hpp"
#include <cstdio>
#include <cstdlib>
#include <string> 
using namespace std; 
extern int yyparse( int IC, enum Pass pass, SymbolTable* table );
int main(int argc, char *argv[])
{
    initialize_op_table();

    SymbolTable table;
    int IC = 0;

    yyparse( IC,FIRST,&table ); /* First pass */
	return 0;
} 
