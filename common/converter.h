#ifndef UT_CONVERTER_H
#define UT_CONVERTER_H

#include "types.h"
#include "exceptions.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <limits>

namespace UT
{

  class IntConverter
  {
    public:

      static bool convert( const std::string& value, long& result )
      {
        const char* str = value.c_str();
        bool isNegative = false;
        long x = 0;

        if( *str == '-' )
        {
          isNegative = true;
          ++str;
        }

        do
        {
          const int c = *str - '0';
          if( c < 0 || 9 < c ) return false;
          x = 10 * x + c;
        } while (*++str);

        if( isNegative )
          x = -x;

        result = x;
        return true;
      }

      static long convert( const std::string& value )
      {
        long result = 0;
        if( !convert( value, result ) )
          throw UT::Exception( "Error During Conversion", "Cannot Convert" ) ;
        else
          return result;
      }

      template<class T>
        static inline char* integer_to_string( char* buf, const size_t len, T t)
        {
          const bool isNegative = t < 0;
          char* p = buf + len;

          *--p = '\0';

          if( isNegative )
          {
            if( t == (std::numeric_limits<T>::min)() )
            {
              *--p = '0' + (char)((10-t%10)%10);
              t/=10;
            }
            t = -t;
            do
            {
              *--p = '0' + (char)(t % 10);
              t /= 10;
            } while (t > 0);
            *--p = '-';
          }
          else
          {
            do
            {
              *--p = '0' + (char)(t % 10);
              t /= 10;
            } while( t > 0 );
          }
          return p;
        }


      static std::string convert( long value )
      {
        // buffer is big enough for significant digits and extra digit,
        // minus and null
        char buffer[std::numeric_limits<long>::digits10 + 3];
        const char* const start
          = integer_to_string<long>( buffer, sizeof (buffer), value );
        return std::string( start, buffer + sizeof (buffer) - start - 1 );
      }

      

      static INT toInt16( const std::string &strValue ) {
        return atoi( strValue.c_str() ) ;
      }

      static INT toIntShort( const std::string &strValue ) {
        return atoi( strValue.c_str() ) ;
      }

      static INT toInt( const std::string &strValue ) {
        return atoi( strValue.c_str() ) ;
      }

      static INT toInt32( const std::string &strValue ) {
        return atoi( strValue.c_str() ) ;
      }

      static LONG toLong( const std::string &strValue ) {
        return atoi( strValue.c_str() ) ;
      }

      static LONGLONG toLongLong( const std::string &strValue ) {
        return toInt64( strValue ) ;
      }

      static ULONGLONG toULongLong( const std::string &strValue ) {
#if defined(WIN32)
        return _strtoui64( strValue.c_str(), NULL, 10 ) ;
#else
        return atol( strValue.c_str() ) ;
#endif
      }

      static LONGLONG toInt64( const std::string &strValue ) {
#if defined(WIN32)
        return _atoi64( strValue.c_str() ) ;
#else
        return atol( strValue.c_str() ) ;
#endif
      }

      static double toDouble( const std::string &strValue ) {
        return atof( strValue.c_str() ) ;
      }

      static double toFloat( const std::string &strValue ) {
        return atof( strValue.c_str() ) ;
      }
  };

  class StringConverter 
  {
    public:

      static void toString( LONG lValue, std::string &strValue )
      {
        char cValue[20] ;
        //sprintf( cValue, "%ld", lValue ) ;
        sprintf( cValue, "%d", lValue ) ;
        strValue.assign( cValue ) ;
      }

      static std::string toString( const LONG &lValue ) {
        std::string strValue ;
        toString( lValue, strValue ) ;
        return strValue ;
      }

      static void toString( LONGLONG lValue, std::string &strValue ) {
        char cValue[20] ;
#ifdef WIN32
        sprintf( cValue, "%lld", lValue ) ; // In windows ld = int32
#else
        sprintf( cValue, "%ld", lValue ) ; // Linux gives a warning on lld
#endif
        strValue.assign( cValue ) ;
      }

      static std::string toString( LONGLONG lValue ) {
        std::string strValue ;
        toString( lValue, strValue ) ;
        return strValue ;
      }
      
      static void toString( ULONGLONG lValue, std::string &strValue ) {
        char cValue[20] ;
        //sprintf( cValue, "%lld", lValue ) ;
        sprintf( cValue, "%llu", ( long long unsigned int ) lValue ) ;
        strValue.assign( cValue ) ;
      }

      static std::string toString( ULONGLONG lValue ) {
        std::string strValue ;
        toString( lValue, strValue ) ;
        return strValue ;
      }

      static void toString( double lValue, std::string &strValue )
      {
        toString( (LONGLONG) lValue, strValue ) ;
      }

      static std::string toString( double lValue ) {
        std::string strValue ;
        toString( lValue, strValue ) ;
        return strValue ;
      }

  };

}
#endif
