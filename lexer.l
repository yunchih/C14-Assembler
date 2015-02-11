identifier  [a-zA-Z_][a-zA-Z_0-9]*
digit       [0-9]
hex         [a-fA-F0-9]
new_line    \n

/* ---- Start Of Table ---- */


/* ---- End Of Table ---- */
%{

#include <cstdio>
#include <cstdlib>
#include <string>
#include "parser.hpp"
#include "main.hpp"
#include "color.hpp"
using namespace std;

#define TYPE( type ) if(1==0)printf("Type: " #type "\n")
#define TRACE printf( GREEN "Found token '%s'" RESET "\n" ,yytext)
%}

%option noyywrap
%option yylineno

%%

","                       { return COMMA;             }
"["                       { return LeBraket;          }
"]"                       { return RiBraket;          }
"EQU"                     { TYPE( EQU ); return T_EQU;}
"DUP"                     { return T_DUP;             }
"??"                      { return T_DB_QuestionMark; }
<<EOF>>                   { TYPE( EOF );  yyterminate(); return T_EOF; }
{new_line}                { TYPE( NEW LINE ); return NEW_LINE; }

#.*$                      { TYPE( Comment ); return COMMENT; }  /* Ignore comment */


[ \t]+                    ;  /* Ignore whitespace */

R{hex}                    { 
                            TRACE;
                            yylval.ObjectCode = (ObjectCode) strtol(&(yytext[1]), NULL, 16);
                            return REGISTER;
                          }

0x{hex}+                  { 
                            TRACE;
                            yylval.ObjectCode = (ObjectCode) strtol(&(yytext[0]), NULL, 16);
                            return IMMEDIATE; 
                          }

-?{digit}+                { 
                            TYPE( IMMEDIATE );
                            TRACE;
                            yylval.ObjectCode = (ObjectCode) strtol(&(yytext[0]), NULL, 10);
                            return IMMEDIATE; 
                          }

{size}                    { 
                            TYPE( Size );TRACE;
                            yylval.str_ptr  = new string( yytext );
                            return SIZE;
                          }

{op}                      { 
                            TYPE( OP );TRACE;
                            yylval.str_ptr  = new string( yytext );
                            return OP;
                          }

{identifier}              { 
                            TYPE( IDENTIFIER );TRACE;
                            yylval.str_ptr  = new string( yytext );
                            return IDENTIFIER;
                          }

\.{identifier}:           {
                            TYPE( DIRECTIVE );TRACE;
                            yylval.str_ptr  = new string( yytext );
                            return DIRECTIVE;
                          }

{identifier}:             {
                            TYPE( LABEL );TRACE;
                            yylval.str_ptr  = new string( yytext );
                            return LABEL;
                          }

%%

