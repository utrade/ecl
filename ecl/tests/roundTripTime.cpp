/*******************************************************************************
* Date      | Name   | Description                                             *
* 03 Oct 13 | Jovito | Req #1848 : Test Cases For ECL                          *
*******************************************************************************/

#include "roundTripTime.h"
#include "staticOrder.h"

namespace UT { namespace ECL { namespace TESTS
{
  RoundTripTime::RoundTripTime( const std::string &omsConfigFile ) 
    : _sessionID( "FIX.4.2", "oms-ecl-utrade", "ecl-utrade" ),
    _settings( omsConfigFile ) ,
    _factory( _settings ),
    _initiator( _dummyOmsApp, _factory, _settings )
  {
    _initiator.start();
    FIX::process_sleep( 1 );

    processUserInput() ;
  }

  RoundTripTime::~RoundTripTime( ) 
  {
    _initiator.stop() ;
  }

  void RoundTripTime::processUserInput() 
  {
    _dummyOmsApp.resetCount() ;

    int count ;
    std::cout << "Enter Number of orders : " ;
    std::cin >> count ;

    std::string command( "" ) ;
    while ( command != "0" )
    {
      std::cout
        << "\nOptions are : \n"
        << " 1. Test Nse CM RTT \n"
        << " 2. Test Nse FO RTT \n"
        << " 3. Test Nse CD RTT \n"
        << " 0. Return To Previous Menu "
        << std::endl;

      getline( std::cin, command ) ;

      if( command == "1" )
      {
        placeOrders( StaticOrder::getNseCmOrder(), count ) ;
        _report.report( "Oms To Ecl Round Trip Time For NSECM : ", count ) ;
      } 
      else if( command == "2" )
      {
        placeOrders( StaticOrder::getNseFoOrder(), count ) ;
        _report.report( "Oms To Ecl Round Trip Time For NSECM : ", count ) ;
      } 
      else if( command == "3" )
      {
        placeOrders( StaticOrder::getNseCdsOrder(), count ) ;
        _report.report( "Oms To Ecl Round Trip Time For NSECM : ", count ) ;
      } 
    }
  }

  void RoundTripTime::placeOrders( FIX42::NewOrderSingle order, int count ) 
  {
    _report.reset() ;

    for ( int i = 0; i < count; ++i )
    {
      FIX::Session::sendToTarget( order, _sessionID );
    }

    while( _dummyOmsApp.getCount() < count )
      FIX::process_sleep( 0.1 );
  }

}}}
