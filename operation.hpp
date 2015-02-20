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

        void format1( ObjectCode Dest,       ObjectCode SourceS, ObjectCode SourceT );
        void format2( ObjectCode Dest,       ObjectCode Addr );
        void format3( ObjectCode Addr );
        void format4( ObjectCode MemoryReg,  ObjectCode SourceS );
        void format5( ObjectCode Dest,       ObjectCode MemoryReg );
        void format6( ObjectCode MemoryAddr, ObjectCode SourceS );
        void format7( ObjectCode Dest,       ObjectCode MemoryAddr );
        void format8( ObjectCode Dest,       ObjectCode SourceS );
        void format9( ObjectCode SourceS );
        void format10( void );

    private:
        ObjectCode code;
        Format format;
        std::string name;

        void writeInstruction( ObjectCode code );
};


#endif
