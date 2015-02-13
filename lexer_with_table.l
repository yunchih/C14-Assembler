identifier  [a-zA-Z_][a-zA-Z_0-9]*
digit       [0-9]
hex         [a-fA-F0-9]
new_line    \n

/* ---- Start Of Table ---- */

op (inr" ] = new Op( "inr|dcr" ] = new Op( "dcr|inrm" ] = new Op( "inrm|dcrm" ] = new Op( "dcrm|ldi" ] = new Op( "ldi|sti" ] = new Op( "sti|mov" ] = new Op( "mov|movr" ] = new Op( "movr|movm" ] = new Op( "movm|add" ] = new Op( "add|adc" ] = new Op( "adc|sub" ] = new Op( "sub|sbb" ] = new Op( "sbb|and" ] = new Op( "and|xor" ] = new Op( "xor|or" ] = new Op( "or|nt" ] = new Op( "nt|cmp" ] = new Op( "cmp|shla" ] = new Op( "shla|shra" ] = new Op( "shra|shll" ] = new Op( "shll|shrl" ] = new Op( "shrl|mul" ] = new Op( "mul|div" ] = new Op( "div|muli" ] = new Op( "muli|divi" ] = new Op( "divi|rli" ] = new Op( "rli|rri" ] = new Op( "rri|call" ] = new Op( "call|cc" ] = new Op( "cc|cnc" ] = new Op( "cnc|cz" ] = new Op( "cz|cnz" ] = new Op( "cnz|cg" ] = new Op( "cg|cng" ] = new Op( "cng|ce" ] = new Op( "ce|cne" ] = new Op( "cne|cl" ] = new Op( "cl|cnl" ] = new Op( "cnl|cp" ] = new Op( "cp|cm" ] = new Op( "cm|ret" ] = new Op( "ret|rc" ] = new Op( "rc|rnc" ] = new Op( "rnc|rz" ] = new Op( "rz|rnz" ] = new Op( "rnz|rg" ] = new Op( "rg|rng" ] = new Op( "rng|re" ] = new Op( "re|rne" ] = new Op( "rne|rl" ] = new Op( "rl|rnl" ] = new Op( "rnl|rp" ] = new Op( "rp|rm" ] = new Op( "rm|jmp" ] = new Op( "jmp|jc" ] = new Op( "jc|jnc" ] = new Op( "jnc|jz" ] = new Op( "jz|jnz" ] = new Op( "jnz|jg" ] = new Op( "jg|jng" ] = new Op( "jng|je" ] = new Op( "je|jne" ] = new Op( "jne|jl" ] = new Op( "jl|jnl" ] = new Op( "jnl|jp" ] = new Op( "jp|jm" ] = new Op( "jm|ta" ] = new Op( "ta|lda" ] = new Op( "lda|mvi" ] = new Op( "mvi|mvim" ] = new Op( "mvim|adi" ] = new Op( "adi|aci" ] = new Op( "aci|sui" ] = new Op( "sui|sbi" ] = new Op( "sbi|ani" ] = new Op( "ani|xri" ] = new Op( "xri|ori" ] = new Op( "ori|cpi" ] = new Op( "cpi|oui" ] = new Op( "oui|push" ] = new Op( "push|pop" ] = new Op( "pop|in" ] = new Op( "in|ou" ] = new Op( "ou|hlt" ] = new Op( "hlt)
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

