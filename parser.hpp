/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "parser.y" /* yacc.c:1909  */


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

    extern int yylineno;
    #define FORMAT( format ) cout<<YELLOW<<"On line "<<yylineno<<" Format: "<<#format<<RESET<<endl
    #define SPLIT_LINE() printf("------------------------\n");

#ifdef YYERROR_VERBOSE
     #undef YYERROR_VERBOSE
#endif
#ifdef YYDEBUG
     #undef YYDEBUG
#endif

#define YYERROR_VERBOSE 1
#define YYDEBUG 1

#line 85 "parser.hpp" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IMMEDIATE = 258,
    REGISTER = 259,
    IDENTIFIER = 260,
    DIRECTIVE = 261,
    LABEL = 262,
    COMMENT = 263,
    T_EQU = 264,
    T_DB_QuestionMark = 265,
    T_DUP = 266,
    T_ENDL = 267,
    T_EOF = 268,
    NEW_LINE = 269
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 41 "parser.y" /* yacc.c:1909  */

    std::string* str_ptr;
    unsigned long ObjectCode;
    int token;
    int comment;

#line 119 "parser.hpp" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (int IC, enum Pass pass, SymbolTable* table);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
