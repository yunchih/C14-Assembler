%{

#include <cstdio>
#include <cstdlib>
#include <string>
#include "phase1.hpp"
using namespace std;

%}

%option noyywrap
%option yylineno

%%


[ \t\n\r]+                ;  /* Ignore whitespace */

#[^\r\n]*(\r\n) ;  /* Ignore comment */

,                         ;  /* Ignore colon */

R[0-9A-Fa-f]              { 
                            yylval.int_val = (int) strtol(&(yytext[1]), NULL, 16);
                            return REGISTER;
                          }

0x[a-fA-F0-9]+            { 
                            yylval.int_val = (int) strtol(&(yytext[0]), NULL, 16);
                            return IMMEDIATE; 
                          }

-?[0-9]+                  { 
                            yylval.int_val = (int) strtol(&(yytext[0]), NULL, 10);
                            return IMMEDIATE; 
                          }

\.[a-zA-Z_0-9]+:          { 
                            /*
                             * string *tmp = new string( yytext ); 
                             * size_t dotPos = tmp->find(".");
                             * size_t colonPos = tmp->find(";");
                             * yylval.str_val = new string( tmp->substr( dotPos+1,colonPos-dotPos-1 ) ); [> Trim . and : <]
                             */
                            yylval.str_val = new string( yytext );
                            return DIRECTIVE;
                          }

[a-zA-Z_0-9]+             { 
                            yylval.str_val = new string( yytext );
                            return IDENTIFIER;
                          }

%%

