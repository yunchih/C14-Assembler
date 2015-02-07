%code requires {
    #include <cstdio>
    #include <cstdlib>
    #include <string>
    #include <map>
    #include "identifier.hpp"
    #include "main.hpp"
    #include "instructionTable.hpp"
    using namespace std;

    extern FILE* output_file;
    extern int yylex(void);
    void yyerror ( int IC , enum Pass pass, SymbolTable* table, const char *s); 
    void die(const char* msg );
    int getSize( string name );
    void writeInstruction( ObjectCode code );
    void writeVariable( Identifier* var );

    #define Table (*table)

}
%union {
    int int_val;
    std::string* str_val;
    unsigned long ObjectCode;
}

%parse-param { int IC }{ enum Pass pass }{ SymbolTable* table }
%start Program 
%token <int_val> IMMEDIATE REGISTER 
%token <str_val> IDENTIFIER DIRECTIVE
%type  <ObjectCode> Instruction
%type  <int_val> Format1 Format2 Format3 Format4 Format5 
%type  <int_val> Op Address Dest SourceS SourceT Memory 
%type  <int_val> Size 


%%
    
    Program:              Lines;

    Lines:                Line; 
                        | Lines Line;

    Line:                 DIRECTIVE;  
                        | Label;
                        | ConstantDeclaration;
                        | VariableDeclaration { IC++; }
                        | Instruction { 
                            if( pass == SECOND )
                                writeInstruction($1); 
                            IC++; 
                          }

    ConstantDeclaration:  IDENTIFIER "EQU" IMMEDIATE  {
                            if( pass == FIRST ) /* Do nothing on second pass */
                                Table[ *$1 ] = new Constant( $3 ); 
                            delete $1;
                          }

    VariableDeclaration:  IDENTIFIER Size IMMEDIATE { 
                            if( pass == FIRST )
                                Table[ *$1 ] = new Variable( $2 , $3 , IC , 1 );
                            else
                                writeVariable( Table[ *$1 ] );
                            delete $1;
                          }
                        | IDENTIFIER Size "?" { /* Uninitialized variable */
                            if( pass == FIRST )
                                Table[ *$1 ] = new Variable( $2 , 0 , IC , 1 );
                            else
                                writeVariable( Table[ *$1 ] );
                            delete $1;
                          }
                        | IDENTIFIER Size "DUP" "(" IMMEDIATE IMMEDIATE ")" { /* Array declaration */
                            if( pass == FIRST )
                                Table[ *$1 ] = new Variable( $2 , $6 , IC , $5 );
                            else
                                writeVariable( Table[ *$1 ] );
                            delete $1;
                          }

    Label:                IDENTIFIER ":" {
                            if( pass == FIRST ) /* Do nothing on second pass */
                                Table[ *$1 ] = new Symbol( IC );
                            delete $1;
                          }

    Instruction:          Format1 { $$ = $1; }
                        | Format2 { $$ = $1; }
                        | Format3 { $$ = $1; }
                        | Format4 { $$ = $1; }
                        | Format5 { $$ = $1; }
                    
    
    Format1:              Op "," Dest "," SourceS "," SourceT { $$ = $1 + $3 + $5 + $7; }

    Format2:              Op "," Dest "," Address { $$ = $1 + $3 + $5; }

    Format3:              Op "," Address { $$ = $1 + $3; }

    Format4:              Op "," Memory "," SourceS { $$ = $1 + $3 + $5; }
                        | Op "," Dest "," Memory  { $$ = $1 + $3 + $5; }
    
    Format5:              Op "," Dest "," SourceS { $$ = $1 + $3 + $5; }

    
    
    Op:                   IDENTIFIER {
                            if( pass == SECOND ) {
                                if( op_table.find( *$1 ) == op_table.end() )
                                    die("Undefined instruction");
                                else 
                                    $$ = op_table[ *$1 ];
                            }
                            else
                                return 0;
                            delete $1;
                          }

    Memory:               "[" REGISTER "]" { $$ = $2; } 
                        | "[" Address  "]" { $$ = $2; }

    Address:              IDENTIFIER /* Symbol */ {
                            if( pass == SECOND )  {
                               if( table->find( *$1 ) == table->end() ) 
                                   die("Undefined symbol");
                               else
                                   $$ = (Table[ *$1 ])->eval();
                            }
                            else
                                return 0;
                            delete $1;
                        }
                        | IMMEDIATE { $$ = $1; }    

    Dest:                 REGISTER { $$ = $1; }
    SourceS:              REGISTER { $$ = $1; }
    SourceT:              REGISTER { $$ = $1; }

    Size:                 IDENTIFIER { $$ = getSize(*$1); }
 

%%

int getSize( string name ){
    if( name == "DW" ) return 4;
    else if( name == "DD" ) return 8;
    else die("Invalid size prefix" );
}

void writeInstruction( ObjectCode code ){

}

void writeVariable( Identifier* var ){

}

void die(const char * msg ){ 
    extern int yylineno;
    fprintf(stderr, "line %d: %s\n", yylineno, msg);
}

void yyerror ( int IC , enum Pass pass, SymbolTable* table, const char *s) {
   fprintf (stderr, "%s\n", s);
 }

