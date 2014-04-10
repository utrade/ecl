#include "plusAdapter.h"
#include "omsHandler.h"

#include "eclConstants.h"
#include "fixConverter.h"

#include "../common/dismantleFix.h"
#include "../common/errorMessages.h"
#include "../common/exceptions.h"

#include <quickfix/fix42/BusinessMessageReject.h>
#include <quickfix/fix42/OrderCancelReject.h>

#include <quickfix/fix44/NewOrderSingle.h>
#include <quickfix/fix44/OrderCancelRequest.h>
#include <quickfix/fix44/OrderCancelReplaceRequest.h>
#include <quickfix/fix44/ExecutionReport.h>
#include <quickfix/fix44/OrderCancelReject.h>
#include <quickfix/fix44/BusinessMessageReject.h>

namespace UT { namespace ECL
{
  PlusAdapter *PlusAdapter::_instance = NULL ;

  boost::mutex PlusAdapter::_mutexOnInstance ;

  PlusAdapter::PlusAdapter() 
  {
  }

  PlusAdapter::PlusAdapter( const PlusAdapter& ) 
  {
  }

  PlusAdapter &PlusAdapter::operator = ( const PlusAdapter & ) 
  {
    return PlusAdapter::getInstance() ;
  }

  PlusAdapter &PlusAdapter::getInstance() 
  {
    if( _instance != NULL )
      return *_instance ;

    _mutexOnInstance.lock() ;

    if( _instance != NULL )
      return *_instance ;

    _instance = new PlusAdapter() ;
    return *_instance ;

    _mutexOnInstance.unlock() ;
  }

  bool PlusAdapter::reset( const FIX::SessionSettings &settings ) 
  {
    return fetchDestinations( settings ) ;
  }

  bool PlusAdapter::fetchDestinations( const FIX::SessionSettings &settings ) 
  {
    try
    {  
      std::set< FIX::SessionID > sessions = settings.getSessions() ;
      std::set< FIX::SessionID >::iterator iSessions  = sessions.begin() ;

      for( ; iSessions != sessions.end() ; ++iSessions )
      {
        const FIX::Dictionary &iDictionary = settings.get( *iSessions ) ;

        if ( iDictionary.getString( FIX::CONNECTION_TYPE ) == FIX_INITIATOR )
        {
          _sessionId = *iSessions ;
        }
      }
    }
    catch ( ConfigError &e )
    {
      ERROR_1( CONFIG_ERROR_READING_EXCHANGE_DESTINATIONS, e.what() ) ;
      return false ;
    }

    return true ;
  }

  void PlusAdapter::toApp(FIX::Message &message, const FIX::SessionID&)
    throw( FIX::DoNotSend )
  {
#ifndef NDEBUG
    UT::DismantleFix::dismantle( "OUTBOUND TO EXCHANGE PLUS", 
                                 message.toString() ) ;
#endif
  }

  void PlusAdapter::fromApp( const FIX::Message &message, 
                             const FIX::SessionID& sessionID)
    throw( FIX::FieldNotFound, 
           FIX::IncorrectDataFormat, 
           FIX::IncorrectTagValue, 
           FIX::UnsupportedMessageType )
  {
#ifndef NDEBUG
    UT::DismantleFix::dismantle( "INBOUND FROM EXCHANGE PLUS", 
                                 message.toString() ) ;
#endif
    crack( message, sessionID );
  }

  bool PlusAdapter::send( const FIX42::NewOrderSingle &order ) 
  {
    if( _sessionId.toString() == "" )
      return false ;

    FIX::OrdType lOrdType ;
    order.get( lOrdType );

    switch( lOrdType )
    {
      case FIX::OrdType_STOP :
      case FIX::OrdType_STOP_LIMIT :
        std::cout << "ERROR STOP IS NOT SUPPORTED" << std::endl ;
        return false ;
    }

    FIX44::NewOrderSingle newOrder = FixConverter::toFix44( order ) ;

    return FIX::Session::sendToTarget( newOrder, _sessionId ) ;
  }

  bool PlusAdapter::send( const FIX42::OrderCancelRequest &order )
  {
    if( _sessionId.toString() == "" )
      return false ;

    FIX44::OrderCancelRequest cancelRequest 
      = FixConverter::toFix44( order ) ;

    return FIX::Session::sendToTarget( cancelRequest, _sessionId ) ;
  }

  bool PlusAdapter::send( const FIX42::OrderCancelReplaceRequest &order )
  {
    if( _sessionId.toString() == "" )
      return false ;

    FIX::OrdType lOrdType ;
    order.get( lOrdType );

    switch( lOrdType )
    {
      case FIX::OrdType_STOP :
      case FIX::OrdType_STOP_LIMIT :
        std::cout << "ERROR STOP IS NOT SUPPORTED" << std::endl ;
        return false ;
    }

    FIX44::OrderCancelReplaceRequest replaceOrder 
      = FixConverter::toFix44( order ) ;

    return FIX::Session::sendToTarget( replaceOrder, _sessionId ) ;
  }

  void PlusAdapter::onMessage ( const FIX44::ExecutionReport &message, 
                                const FIX::SessionID& )
  {
    FIX42::ExecutionReport exReport = FixConverter::toFix42( message ) ;
    exReport.set( FIX::SecurityExchange( MARKET_ID_ESM_NSE ) ) ;

    OmsHandler::getInstance().sendToOms( exReport ) ;
  }

  void PlusAdapter::onMessage ( const FIX44::OrderCancelReject &message, 
                                const FIX::SessionID& )
  {
    FIX42::OrderCancelReject cancelReject = FixConverter::toFix42( message ) ;
    cancelReject.setField( FIX::SecurityExchange( MARKET_ID_ESM_NSE ) ) ;

    OmsHandler::getInstance().sendToOms( cancelReject ) ;
  }

  void PlusAdapter::onMessage( 
      const FIX44::BusinessMessageReject &message, 
      const FIX::SessionID& )
  {
    FIX42::BusinessMessageReject reject = FixConverter::toFix42( message ) ;

    OmsHandler::getInstance().sendToOms( reject ) ;
  }

  void PlusAdapter::onMessage( const FIX44::News &, const FIX::SessionID& )
  {
    ERROR_1( MESSAGE_NOT_HANDLED, "News" ) ;
  }
}}
