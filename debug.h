#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define Test(NAME, args... ) void Test_##NAME( args )

#define TEST(FUNC, args...) do{ printf( ANSI_COLOR_GREEN "---" #FUNC "---\n" ANSI_COLOR_RESET ); Test_##FUNC( args ); }while(0)

#ifdef DEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...) fprintf(stderr, ANSI_COLOR_RED "[ERROR] (%s:%d: errno: %s) " M "\n" ANSI_COLOR_RESET, __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, ANSI_COLOR_YELLOW "[INFO] (%s:%d) " M "\n" ANSI_COLOR_RESET, __FILE__, __LINE__, ##__VA_ARGS__)

// #define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define not_null(A) if((A)==NULL) log_err(" --> " #A " is NULL") 

#define check(A, M, ...) if(!(A))log_err(M, ##__VA_ARGS__)

#define assert_str(A,B) check( strcmp(A,B)==0 ,"expected: %s , got: %s",B,A )

#define assert(A) if(!(A)) log_err(" --> " #A " fails.")

#define assert_int_equal(A,B) if( A != B ) log_err(" expected: %d , got: %d",B,A);

#define sentinel(M, ...)  { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define check_mem(A) check((A), "Out of memory.")

#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }

/*
 * void printSymbolList( Symbols_table* table );
 * 
 * void printInstructionList( Instru_list* list );
 * void printInstructionList( Instru_list* list );
 * void printVarTable(Variable_table* table);
 * void printStrList(Strings_list* list);
 */
#endif
