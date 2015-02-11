%code requires {

    #include <cstdio>
    #include <iostream>
    #include <cstdlib>
    #include <string>
    #include <map>
    #include "identifier.hpp"
    #include "main.hpp"
    #include "instructionTable.hpp"
    #include "color.hpp"
    using namespace std;

    extern int yylex(void);
    extern FILE *yyin;

    void yyerror ( int IC , enum Pass pass, SymbolTable* table, const char *s); 
    void die(const char* msg );
    int getSize( string name );
    ObjectCode getOp( string op_name );
    void writeInstruction( ObjectCode code );
    void writeVariable( Identifier* var );

    #define Table (*table)
    #define SHIFT( field ) shift_table[ #field ]

#ifdef DEBUG
    extern int yylineno;
    #define FORMAT( format ) cout<<YELLOW<<"On line "<<yylineno<<" Format: "<<#format<<RESET<<endl
    #define SPLIT_LINE() printf("------------------------\n");
#endif

#ifdef YYERROR_VERBOSE
     #undef YYERROR_VERBOSE
#endif
#ifdef YYDEBUG
     #undef YYDEBUG
#endif

#define YYERROR_VERBOSE 1
#define YYDEBUG 1
}
%union {
    std::string* str_ptr;
    unsigned long ObjectCode;
    int token;
    int comment;
}

%parse-param { int IC }{ enum Pass pass }{ SymbolTable* table }
%start Program 
%token <ObjectCode> IMMEDIATE REGISTER 
%token <str_ptr>    IDENTIFIER DIRECTIVE LABEL
%token <comment> COMMENT
%token <token> T_EQU T_DB_QuestionMark T_DUP T_ENDL T_EOF NEW_LINE

%type  <ObjectCode> Instruction
%type  <ObjectCode> Format1 Format2 Format3 Format4 Format5 
%type  <ObjectCode> Op Address Dest SourceS SourceT MemorySrc MemoryDest
%type  <ObjectCode> Size 


%%
    
    Program:              Lines { FORMAT( Program ); }

    Lines:                Line  ;
                        | Lines Line ;

    Line:                 NEW_LINE { /*FORMAT( New line );*/ } 
                        | COMMENT { FORMAT( Single line comment ); }
                        | Statement Line { FORMAT(Statement); }

    Statement:            DIRECTIVE;  
                        | Label { FORMAT( Label ); }
                        | ConstantDeclaration { FORMAT( Constant ); }
                        | VariableDeclaration { FORMAT( Variable ); IC++; }
                        | Instruction { 
                            FORMAT( Instruction );
                            if( pass == SECOND )
                                writeInstruction($1); 
                            IC++; 
                          }

    ConstantDeclaration:  IDENTIFIER T_EQU IMMEDIATE  {
                            FORMAT( IDENTIFIER EQU IMMEDIATE );
                            if( pass == FIRST ) /* Do nothing on second pass */
                                Table[ *$1 ] = new Constant( $3 ); 
                            delete $1;
                          }
                        | IDENTIFIER T_EQU T_DB_QuestionMark  {
                            FORMAT( IDENTIFIER EQU ?? );
                            if( pass == FIRST ) /* Do nothing on second pass */
                                Table[ *$1 ] = new Constant( 0 ); 
                            delete $1;
                          }

    VariableDeclaration:  IDENTIFIER Size IMMEDIATE { 
                            FORMAT( IDENTIFIER Size IMMEDIATE );
                            if( pass == FIRST )
                                Table[ *$1 ] = new Variable( $2 , $3 , IC , 1 );
                            else
                                writeVariable( Table[ *$1 ] );
                            delete $1;
                          }
                        | IDENTIFIER Size '?' { /* Uninitialized variable */
                            FORMAT( IDENTIFIER Size ? );
                            if( pass == FIRST )
                                Table[ *$1 ] = new Variable( $2 , 0 , IC , 1 );
                            else
                                writeVariable( Table[ *$1 ] );
                            delete $1;
                          }
                        | IDENTIFIER Size T_DUP '(' IMMEDIATE IMMEDIATE ')' { /* Array declaration */
                            FORMAT( Array );
                            if( pass == FIRST )
                                Table[ *$1 ] = new Variable( $2 , $6 , IC , $5 );
                            else
                                writeVariable( Table[ *$1 ] );
                            delete $1;
                          }

    Label:                LABEL {
                            if( pass == FIRST ) /* Do nothing on second pass */
                                Table[ *$1 ] = new Symbol( IC );
                            delete $1;
                          }

    Instruction:          Format1 { $$ = $1; }
                        | Format2 { $$ = $1; }
                        | Format3 { $$ = $1; }
                        | Format4 { $$ = $1; }
                        | Format5 { $$ = $1; }
                    
    
    Format1:              Op  Dest ',' SourceS ',' SourceT { $$ = $1 + $2 + $4 + $6; }

    Format2:              Op  Dest ',' Address { $$ = $1 + $2 + $4; }

    Format3:              Op  Address { $$ = $1 + $2; }

    Format4:              Op  MemoryDest ',' SourceS { $$ = $1 + $2 + $4; }
                        | Op  Dest ',' MemorySrc  { $$ = $1 + $2 + $4; }
    
    Format5:              Op  Dest ',' SourceS { $$ = $1 + $2 + $4; }

    
    
    Op:                   IDENTIFIER {
                            if( pass == SECOND ){
                                $$ = getOp( *$1 );
                                $$ <<= SHIFT( Op );
                            }
                            else
                                $$ = 0;
                            delete $1;
                          }

    MemoryDest:           '[' REGISTER ']' { $$ = $2 << SHIFT(  Dest   ); } 
                        | '[' Address  ']' { $$ = $2 << SHIFT( Address ); }

    MemorySrc:            '[' REGISTER ']' { $$ = $2 << SHIFT( SourceS ); } 
                        | '[' Address  ']' { $$ = $2 << SHIFT( Address ); }

    Address:              IDENTIFIER /* Symbol */ {
                            if( pass == SECOND )  {
                               if( table->find( *$1 ) == table->end() ) {
                                   die("Undefined symbol");
                                   $$ = 0;   
                               }
                               else
                                   $$ = (Table[ *$1 ])->eval();
                               $$ <<= SHIFT( Address );
                            }
                            else
                                $$ = 0;
                            delete $1;
                        }
                        | IMMEDIATE { $$ = $1 << SHIFT( Address );}    

    Dest:                 REGISTER { $$ = $1 << SHIFT( Dest ); }
    SourceS:              REGISTER { $$ = $1 << SHIFT( SourceS ); }
    SourceT:              REGISTER { $$ = $1 << SHIFT( SourceT ); }

    Size:                 IDENTIFIER { $$ = getSize(*$1); }
 

%%

int getSize( string name ){
    cout<<"Query size: "<<name<<endl;
    if( size_table.find( name ) == size_table.end() ){
        die("Invalid size prefix" );
        return 0;
    }
    else return size_table[ name ];
}
ObjectCode getOp( string op_name ){
    if( op_table.find( op_name ) == op_table.end() ){
        die("Undefined instruction");
        return 0;
    }
    else 
        return op_table[ op_name ];
}

void writeInstruction( ObjectCode code ){
    extern FILE* out;

}

void writeVariable( Identifier* var ){
    extern FILE* out;

}

void die(const char * msg ){ 
    extern int yylineno;
    fprintf(stderr, RED "line %d: %s\n" RESET, yylineno, msg);
}

void yyerror ( int IC , enum Pass pass, SymbolTable* table, const char *s) {
    extern int yylineno;
   fprintf (stderr, RED "On line %d, %s\n" RESET ,yylineno, s);
 }

