#ifndef OPERATION_HPP
#define OPERATION_HPP 

#include <vector>
#include <string>
#include "main.hpp"

typedef int (*Operation)(std::vector<ObjectCode>);
/* 
 *
 * Type `Operation` is a pointer to a function 
 * that has a vector of `ObjectCode` as 
 * parameter.  The vector stores a list of
 * ObjectCode to be processed by the function
 *
 */

class Op {
    public:
        Operation operation;
        Operation fetch_op( Format );
        std::string format_info(void);

        Op( std::string name , ObjectCode code , Format format ){ 
            Op::name      = name;
            Op::code      = code;
            Op::format    = format;
            Op::operation = fetch_op( format );
        }

        bool check_format( Format format );
        /* 
         * fetch_op returns a pointer to 
         * function (according to `Format`)
         * that returns an ObjectCode
         *
         */
    private:
        ObjectCode code;
        Format format;
        std::string name;

};

#endif
