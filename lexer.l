%{

#include <cstdio>
#include <cstdlib>
#include <string>
#include "parser.hpp"
#include "main.hpp"
using namespace std;

%}

%option noyywrap
%option yylineno

%%

"EQU"                     { return T_EQU;             }
"DUP"                     { return T_DUP;             }
"??"                      { return T_DB_QuestionMark; }

#[^\r\n]*(\r\n)           ;  /* Ignore comment */

[ \t\n\r]+                ;  /* Ignore whitespace */

R[0-9A-Fa-f]              { 
                            yylval.ObjectCode = (ObjectCode) strtol(&(yytext[1]), NULL, 16);
                            return REGISTER;
                          }

0x[a-fA-F0-9]+            { 
                            yylval.ObjectCode = (ObjectCode) strtol(&(yytext[0]), NULL, 16);
                            return IMMEDIATE; 
                          }

-?[0-9]+                  { 
                            yylval.ObjectCode = (ObjectCode) strtol(&(yytext[0]), NULL, 10);
                            return IMMEDIATE; 
                          }

[a-zA-Z_0-9]+             { 
                            yylval.str_ptr  = new string( yytext );
                            return IDENTIFIER;
                          }

%%

