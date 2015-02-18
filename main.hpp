#ifndef MAIN_H
#define MAIN_H

enum Pass { FIRST , SECOND };

enum Format { Format1,Format2,Format3,
              Format4,Format5,Format6,
              Format7,Format8,Format9,
              Format10 
            };

typedef unsigned long ObjectCode;

#define sizeOfByte 8

#define sizeOfObjectCode sizeOfByte*sizeof(ObjectCode)

#define      Op_pos 3
#define Address_pos 0
#define    Dest_pos 2
#define SourceS_pos 1
#define SourceT_pos 0

/*
 * 
 *     Format1:              Op  Dest , SourceS , SourceT  
 *     Format2:              Op  Dest , Address 
 *     Format3:              Op  Address 
 *     Format4:              Op  MemoryDest , SourceS  
 *     Format5:              Op  Dest , MemorySrc  
 *     Format6:              Op  Dest , SourceS  
 *     Format7:              Op  Src 
 *
 *     
 */
#endif
