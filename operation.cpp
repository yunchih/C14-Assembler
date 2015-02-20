#include "operation.hpp"

void Op::format1( ObjectCode Dest, ObjectCode SourceS, ObjectCode SourceT ){

}
void Op::format2( ObjectCode Dest, ObjectCode Addr ){

}
void Op::format3( ObjectCode Addr ){

}
void Op::format4( ObjectCode MemoryReg, ObjectCode SourceS ){

}
void Op::format5( ObjectCode Dest , ObjectCode MemoryReg ){

}
void Op::format6( ObjectCode MemoryAddr, ObjectCode SourceS ){

}
void Op::format7( ObjectCode Dest, ObjectCode MemoryAddr ){

}
void Op::format8( ObjectCode Dest, ObjectCode SourceS ){

}
void Op::format9( ObjectCode SourceS ){
    if( Op::name == "inr" ){

    }
    else if( Op::name == "dcr" ){

    }
}
void Op::format10( void ){

}

std::string Op::format_info(void){
    switch( Op::format ){
        case Format1: 
            return Op::name + "format: Op Dest SourceS SourceT";
        case Format2: 
            return Op::name + "format: Op Dest Address";
        case Format3: 
            return Op::name + "format: Op Address";
        case Format4: 
            return Op::name + "format: Op [Register] SourceS";
        case Format5: 
            return Op::name + "format: Op Dest [Register]";
        case Format6: 
            return Op::name + "format: Op [Symbol] SourceS";
        case Format7: 
            return Op::name + "format: Op Dest [Symbol]";
        case Format8: 
            return Op::name + "format: Op Dest SourceS";
        case Format9: 
            return Op::name + "format: Op SourceS";
        case Format10: 
            return Op::name + "format: Op";
    }
}
bool Op::check_format( Format format ){
    return format == Op::format;
}

void Op::writeInstruction( ObjectCode code ){
    extern FILE* out;

}
