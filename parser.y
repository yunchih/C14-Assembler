%code requires {

    #include <cstdio>
    #include <iostream>
    #include <cstdlib>
    #include <string>
    #include <map>
    #include "identifier.hpp"
    #include "main.hpp"
    #include "instructionTable.hpp"
    #include "operation.hpp"
    #include "color.hpp"
    using namespace std;

    extern int yylex(void);
    extern FILE *yyin;

    void yyerror ( int IC , enum Pass pass, SymbolTable* table, const char *s); 
    void die( string msg );
    int getSize( string name );
    Op* getOp( string op_name );
    void writeInstruction( ObjectCode code );
    void writeVariable( Identifier* var );

    static Operation operation;
    static vector<ObjectCode> args;

    #define Table (*table)

    extern int yylineno;
    #define FORMAT( format ) cout<<YELLOW<<"On line "<<yylineno-1<<" Format: "<<#format<<RESET<<endl

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
    Op* Op_ptr;
    int token;
    int comment;
}

%parse-param { int IC }{ enum Pass pass }{ SymbolTable* table }
%start Program 
%token <ObjectCode> IMMEDIATE REGISTER 
%token <comment> COMMENT
%token <token> T_EQU T_DB_QuestionMark T_DUP T_ENDL T_EOF NEW_LINE COMMA LeBraket RiBraket
/* %precedence */
%token <str_ptr>    IDENTIFIER 
%token <str_ptr>    DIRECTIVE
%token <str_ptr>    LABEL
%token <str_ptr>    OP SIZE

%type  <Op_ptr>     Op
%type  <ObjectCode> Instruction
%type  <ObjectCode> Format1 Format2 Format3 Format4 Format5 
%type  <ObjectCode> Address Dest SourceS SourceT MemorySrc MemoryDest
%type  <ObjectCode> Size 


%%
    
    Program:              Lines { FORMAT( Program ); }

    Lines:                Line  ;
                        | Lines Line ;

    Line:                 NEW_LINE            ; 
                        | COMMENT NEW_LINE    { FORMAT( Single line comment ); }
                        | Statement NEW_LINE
                        | Statement COMMENT   { FORMAT(Statement); }
                        | error               ;

    Statement:            DIRECTIVE;  
                        | Label               { FORMAT( Label ); }
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

    Instruction:          Format1 { FORMAT( Format1 ); $$ = $1; }
                        | Format2 { FORMAT( Format2 ); $$ = $1; }
                        | Format3 { FORMAT( Format3 ); $$ = $1; }
                        | Format4 { FORMAT( Format4 ); $$ = $1; }
                        | Format5 { FORMAT( Format5 ); $$ = $1; }
                    
    
    Format1:              Op  Dest COMMA SourceS COMMA SourceT { 
                            if( ($1)->check_format( Format1 ) ){ 
                                operation = ($1)->operation;
                                args.push_back($2);
                                args.push_back($4);
                                args.push_back($6);
                                $$ = operation( args );
                                args.clear();
                            }
                            else
                                die( ($1)->format_info() );  
                          }

    Format2:              Op  Dest COMMA Address {
                            if( ($1)->check_format( Format2 ) ){ 
                                operation = ($1)->operation;
                                args.push_back($2);
                                args.push_back($4);
                                $$ = operation( args );
                                args.clear();
                            }
                            else
                                die( ($1)->format_info() );  
                          }

    Format3:              Op  Address {
                            if( ($1)->check_format( Format3 ) ){ 
                                operation = ($1)->operation;
                                args.push_back($2);
                                $$ = operation( args );
                                args.clear();
                            }
                            else
                                die( ($1)->format_info() );  
                          }

    Format4:              Op  MemoryDest COMMA SourceS { 
                            if( ($1)->check_format( Format4 ) ){ 
                                operation = ($1)->operation;
                                args.push_back($2);
                                args.push_back($4);
                                $$ = operation( args );
                                args.clear();
                            }
                            else
                                die( ($1)->format_info() );  
                          }
                        | Op  Dest COMMA MemorySrc  { 
                            if( ($1)->check_format( Format4 ) ){ 
                                operation = ($1)->operation;
                                args.push_back($2);
                                args.push_back($4);
                                $$ = operation( args );
                                args.clear();
                            }
                            else
                                die( ($1)->format_info() );  
                          }
    
    Format5:              Op  Dest COMMA SourceS { 
                            if( ($1)->check_format( Format5 ) ){ 
                                operation = ($1)->operation;
                                args.push_back($2);
                                args.push_back($4);
                                $$ = operation( args );
                                args.clear();
                            }
                            else
                                die( ($1)->format_info() );  
                          }

    
    
    Op:                   OP {
                            if( pass == SECOND ){
                                $$ = getOp( *$1 );
                            }
                            else
                                $$ = 0;
                            delete $1;
                          }

    MemoryDest:           LeBraket REGISTER RiBraket { $$ = $2; } 
                        | LeBraket Address  RiBraket { $$ = $2; }

    MemorySrc:            LeBraket REGISTER RiBraket { $$ = $2; } 
                        | LeBraket Address  RiBraket { $$ = $2; }

    Address:              IDENTIFIER /* Symbol */ {
                            if( pass == SECOND )  {
                               if( table->find( *$1 ) == table->end() ) {
                                   die("Undefined symbol");
                                   $$ = 0;   
                               }
                               else
                                   $$ = (Table[ *$1 ])->eval();
                            }
                            else
                                $$ = 0;
                            delete $1;
                        }
                        | IMMEDIATE { $$ = $1;}    

    Dest:                 REGISTER { $$ = $1; }
    SourceS:              REGISTER { $$ = $1; }
    SourceT:              REGISTER { $$ = $1; }

    Size:                 SIZE { $$ = getSize(*$1); delete $1; }
 

%%

int getSize( string name ){
    cout<<"Query size: "<<name<<endl;
    if( size_table.find( name ) == size_table.end() ){
        die("Invalid size prefix" );
        return 0;
    }
    else return size_table[ name ];
}
Op* getOp( string op_name ){
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

void die( string msg ){ 
    extern int yylineno;
    cerr << RED << "line "<< yylineno-1 << ": " << msg <<endl;
}

void yyerror ( int IC , enum Pass pass, SymbolTable* table, const char *s) {
    extern int yylineno;
   fprintf (stderr, RED "On line %d, %s\n" RESET ,yylineno-1, s);
 }

