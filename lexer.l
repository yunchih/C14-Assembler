identifier  [a-zA-Z_][a-zA-Z_0-9]*
digit       [0-9]
hex         [a-fA-F0-9]

%{

#include <cstdio>
#include <cstdlib>
#include <string>
#include "parser.hpp"
#include "main.hpp"
using namespace std;

#define TYPE( type ) if(1==0)printf("Type: " #type "\n")
%}

%option noyywrap
%option yylineno

%%

"EQU"                     { TYPE( EQU ); return T_EQU;}
"DUP"                     { return T_DUP;             }
"??"                      { return T_DB_QuestionMark; }
<<EOF>>                   { TYPE( EOF );  yyterminate(); return T_EOF; }
"\n"                      { TYPE( NEW LINE ); return NEW_LINE; }

#.*$                      { TYPE( Comment ); return COMMENT; }  /* Ignore comment */


[ \t]+                    ;  /* Ignore whitespace */

R{hex}                    { 
                            yylval.ObjectCode = (ObjectCode) strtol(&(yytext[1]), NULL, 16);
                            return REGISTER;
                          }

0x{hex}+                  { 
                            yylval.ObjectCode = (ObjectCode) strtol(&(yytext[0]), NULL, 16);
                            return IMMEDIATE; 
                          }

-?{digit}+                  { 
                            TYPE( IMMEDIATE );
                            yylval.ObjectCode = (ObjectCode) strtol(&(yytext[0]), NULL, 10);
                            return IMMEDIATE; 
                          }

{identifier}              { 
                            TYPE( IDENTIFIER );
                            yylval.str_ptr  = new string( yytext );
                            return IDENTIFIER;
                          }

\.{identifier}:           {
                            TYPE( DIRECTIVE );
                            yylval.str_ptr  = new string( yytext );
                            return DIRECTIVE;
                          }

{identifier}:             {
                            TYPE( LABEL );
                            yylval.str_ptr  = new string( yytext );
                            return LABEL;
                          }

%%

