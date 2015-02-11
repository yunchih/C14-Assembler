#include "identifier.hpp"
#include "main.hpp"
#include "instructionTable.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern int yyparse( int IC, enum Pass pass, SymbolTable* table );
extern FILE* yyin;

FILE* out;

void initialize_input_file( const char* filename );
void initialize_output_file( const char* filename );

int main(int argc, char *argv[])
{
    initialize_table();
    initialize_input_file( argv[1] );
    initialize_output_file( argv[1] );

#ifdef DEBUG
        extern int yydebug;
        yydebug = 1;
#endif

    int IC;
    SymbolTable table;

    IC = 0;
    yyparse( IC, FIRST,  &table ); /* First pass */

    IC = 0;
    yyparse( IC, SECOND, &table ); /* Second pass */

	return 0;
} 

void initialize_input_file( const char* filename ){
    yyin = fopen(filename,"r");
    if( yyin == NULL ){
        printf(" Fail to open %s\n",filename);
        exit(1);
    }
}
void initialize_output_file( const char* filename ){
    
    const char* suffix = ".bin";
    char* output = (char*) malloc( strlen(filename)+strlen(suffix)+1 );
    strcpy( output , filename );
    strcat( output ,  suffix  ); 

    out = fopen(output,"wb");

    free( output );

    if( out == NULL ){
        printf(" Fail to write %s\n",filename);
        exit(1);
    }
}
