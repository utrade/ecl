/*******************************************************************************
* Date      | Name   | Description                                             *
* 03 Oct 13 | Jovito | Req #1848 : Test Cases For ECL                          *
*******************************************************************************/

#ifndef UT_ECL_TEST_ROUND_TRIP_TIME
#define UT_ECL_TEST_ROUND_TRIP_TIME

#include <quickfix/Application.h>
#include <quickfix/FieldConvertors.h>
#include <quickfix/Values.h>
#include <quickfix/FileStore.h>
#include <quickfix/SessionID.h>
#include <quickfix/Session.h>
#include <quickfix/DataDictionary.h>
#include <quickfix/Parser.h>
#include <quickfix/Utility.h>
#include <quickfix/SocketAcceptor.h>
#include <quickfix/SocketInitiator.h>
#include <quickfix/ThreadedSocketAcceptor.h>
#include <quickfix/ThreadedSocketInitiator.h>
#include <quickfix/fix42/Heartbeat.h>
#include <quickfix/fix42/NewOrderSingle.h>
#include <quickfix/fix42/QuoteRequest.h>

#include "report.h"

namespace UT { namespace ECL { namespace TESTS
{
  class RTTDummyOms : public FIX::NullApplication
  {
    public:
      RTTDummyOms() : m_count(0) {}

      void fromApp( const FIX::Message& m, const FIX::SessionID& )
        throw( FIX::FieldNotFound, 
               FIX::IncorrectDataFormat, 
               FIX::IncorrectTagValue, 
               FIX::UnsupportedMessageType )
        {
          // std::cout << m.toString() << std::endl ;
          m_count++; 
        }

      int getCount() { return m_count; }

      void resetCount() { m_count = 0 ; }

    private:
      int m_count;
  };

  class RoundTripTime
  {
    public :
      RoundTripTime( const std::string &omsConfigFile ) ;
      ~RoundTripTime( ) ;

    private :
      RTTDummyOms _dummyOmsApp ;
      FIX::SessionID _sessionID ;
      FIX::SessionSettings _settings ;
      FIX::FileStoreFactory _factory ;
      FIX::ThreadedSocketInitiator _initiator ;

      UT::Report _report ;

      void processUserInput() ;
      void placeOrders( FIX42::NewOrderSingle order, int count ) ;
  };
}}}

#endif // UT_ECL_TEST_ROUND_TRIP
