#ifndef OPERATION_HPP
#define OPERATION_HPP 

#include <vector>
#include <string>
#include "main.hpp"

class Op {
    public:
        std::string format_info(void);

        bool check_format( Format format );

        Op( std::string name , ObjectCode code , Format format ){ 
            Op::name      = name;
            Op::code      = code;
            Op::format    = format;
        }

    private:
        ObjectCode code;
        Format format;
        std::string name;

};

#endif
