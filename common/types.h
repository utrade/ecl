/*
:%s/ C( / UT_CREATE_NNF_CHAR( /g
:%s/ S( / UT_CREATE_NNF_SHORT( /g
:%s/ ULL( / UT_CREATE_NNF_LONGLONG( /g
:%s/ LL( / UT_CREATE_NNF_LONGLONG( /g
:%s/ L( / UT_CREATE_NNF_LONG( /g
:%s/ D( / UT_CREATE_NNF_DOUBLE( /g
:%s/ STR( / UT_CREATE_NNF_STRING( /g

:%s/ C( / UT_CREATE_CHAR( /g
:%s/ S( / UT_CREATE_SHORT( /g
:%s/ ULL( / UT_CREATE_ULONGLONG( /g
:%s/ LL( / UT_CREATE_LONGLONG( /g
:%s/ L( / UT_CREATE_LONG( /g
:%s/ D( / UT_CREATE_DOUBLE( /g
:%s/ STR( / UT_CREATE_STRING( /g
*/

#ifndef UT_TYPES_H
#define UT_TYPES_H

#include <stdint.h>
#include <string>
#include <string.h>

namespace UT
{
  typedef signed char CHAR ;
  typedef unsigned char UCHAR ;
  typedef int16_t SHORT ;
  typedef uint32_t UINT ;
  typedef int32_t LONG ;
  typedef int32_t INT ;
  typedef int64_t LONGLONG ;
  typedef uint64_t ULONGLONG ;

  union DOUBLE { 
    double value ; 
    int64_t longValue ; 
    DOUBLE() {}
    DOUBLE( double d ) : value( d ) {} 
  } ;

  //typedef int32_t PRICE ;
  typedef double PRICE ;
}

// Note sizes in Bits
#define UT_CHAR_SIZE 8
#define UT_UCHAR_SIZE 8
#define UT_SHORT_SIZE 16
#define UT_UINT_SIZE 32
#define UT_LONG_SIZE 32
#define UT_INT_SIZE 32
#define UT_PRICE_SIZE 32
#define UT_LONGLONG_SIZE 64
#define UT_ULONGLONG_SIZE 64
#define UT_DOUBLE_SIZE 64

#endif
