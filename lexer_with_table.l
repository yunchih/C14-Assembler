identifier  [a-zA-Z_][a-zA-Z_0-9]*
digit       [0-9]
hex         [a-fA-F0-9]
new_line    \n

/* ---- Start Of Table ---- */

op (INR|DCR|INRM|DCRM|LDI|STI|MOV|MOVR|MOVM|ADD|ADC|SUB|SBB|AND|XOR|OR|NT|CMP|SHLA|SHRA|SHLL|SHRL|MUL|DIV|MULI|DIVI|RLI|RRI|CALL|CC|CNC|CZ|CNZ|CG|CNG|CE|CNE|CL|CNL|CP|CM|RET|RC|RNC|RZ|RNZ|RG|RNG|RE|RNE|RL|RNL|RP|RM|JMP|JC|JNC|JZ|JNZ|JG|JNG|JE|JNE|JL|JNL|JP|JM|TA|LDA|MVI|MVIM|ADI|ACI|SUI|SBI|ANI|XRI|ORI|CPI|OUI|PUSH|POP|IN|OU|HLT)
size (DW|DD|DS)


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

"EQU"                     { TYPE( EQU ); return T_EQU;}
"DUP"                     { return T_DUP;             }
"??"                      { return T_DB_QuestionMark; }
<<EOF>>                   { TYPE( EOF );  yyterminate(); return T_EOF; }
{new_line}                { TYPE( NEW LINE ); return NEW_LINE; }

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

-?{digit}+                { 
                            TYPE( IMMEDIATE );
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

