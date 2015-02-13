#include "operation.hpp"

namespace op {
    int format1( );
}

/* 
 *
 * fetch_op returns a function according to `Format` 
 * that returns an ObjectCode
 *
 *
 */

Operation Op::fetch_op( Format format ){

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
            return Op::name + "format: Op Dest SourceS";
    }
}
bool Op::check_format( Format format ){
    return format == Op::format;
}
