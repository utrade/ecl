#ifndef UT_EXCEPTIONS_H
#define UT_EXCEPTIONS_H

#include <string>
//#include "values.h"

namespace UT
{
  class Exception : public std::exception
  {
    public :
      Exception() {} 

      Exception(const std::string errorType, const std::string &what )
               : _type ( errorType), _message ( what ) 
      { 
        _returnMessage = _type ;
        _returnMessage.append( " : " ) ;
        _returnMessage.append( _message ) ;
      }

      ~Exception() throw() {}

      virtual const char* what() const
        throw()
      {
        return _returnMessage.c_str() ;
      }

    private :
      std::string _type;
      std::string _message;
      std::string _returnMessage ;
  };

  class ConfigError : public Exception
  {
    public :
      ConfigError(const std::string &what) : Exception("Config Error", what)
        {}
  };

  class FileNotFound : public Exception 
  {
    public :
      FileNotFound ( const std::string &what ) :
        Exception ( "Could not find file ", what ) 
    {}
  };

  class ExchangeNotConnected : public Exception 
  {
    public :
      ExchangeNotConnected( )
        : Exception( "Exchange Not Connected ", "" )
      {}
  };

  class LoginError : public Exception
  {
    public :
      LoginError ( const std::string &what)
        : Exception("Logon Error", what)
      { 
      }
  };

  class LoginErrorEndConnection : public Exception
  {
    public :
      LoginErrorEndConnection ( const std::string &what)
        : Exception("Logon Error", what)
    {
    }

  };

  class LoginErrorInvalidPassword : public LoginErrorEndConnection {
    public : 
      LoginErrorInvalidPassword( ) 
        : LoginErrorEndConnection( "Invalid Password " )
      {}
  };

  class LoginErrorUserAlreadyLoggedOn : public LoginErrorEndConnection {
    public : 
      LoginErrorUserAlreadyLoggedOn ( ) 
        : LoginErrorEndConnection( "User is Already Logged On" ) 
      {}
  };

  class ErrorFromExchange : public Exception
  {
    public :
      ErrorFromExchange ( const std::string &what)
        : Exception("Error From Exchange", what)
      { 
      }
  };

  class LookupComplete : public Exception
  {
    public :
      LookupComplete( )
        : Exception("Lookup complete", "disconnecting")
      { 
      }
  };

  class OrderIdDoesNotExist : public Exception 
  {
    public :
      OrderIdDoesNotExist( const std::string &orderId )
        : Exception( "Order Id does not exist", orderId )
      {}
  };


  /* File Handling */
  class InvalidLine : public Exception 
  {
    public :
     InvalidLine( const std::string &what )
      : Exception( "", what ) 
      {
      }
  };
}

#endif 
