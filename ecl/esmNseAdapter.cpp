#if defined(WITH_ESMNSE_FIX42)

#include "esmNseAdapter.h"

#include <quickfix/fix42/NewOrderSingle.h>
#include <quickfix/fix42/OrderCancelRequest.h>
#include <quickfix/fix42/OrderCancelReplaceRequest.h>
#include <quickfix/fix42/ExecutionReport.h>
#include <quickfix/fix42/OrderCancelReject.h>
#include <quickfix/fix42/BusinessMessageReject.h>

#include "omsHandler.h"
#include "eclConstants.h"

#include "../common/dismantleFix.h"
#include "../common/errorMessages.h"
#include "../common/exceptions.h"

namespace UT { namespace ECL
{
  EsmNseAdapter *EsmNseAdapter::_instance = NULL ;

  boost::mutex EsmNseAdapter::_mutexOnInstance ;

  EsmNseAdapter::EsmNseAdapter() 
  {
  }

  EsmNseAdapter::EsmNseAdapter( const EsmNseAdapter& ) 
  {
  }

  EsmNseAdapter &EsmNseAdapter::operator = ( const EsmNseAdapter & ) 
  {
    return getInstance() ;
  }

  EsmNseAdapter &EsmNseAdapter::getInstance() 
  {
    if( _instance != NULL )
      return *_instance ;

    _mutexOnInstance.lock() ;

    if( _instance != NULL )
      return *_instance ;

    _instance = new EsmNseAdapter() ;
    return *_instance ;

    _mutexOnInstance.unlock() ;
  }

  bool EsmNseAdapter::reset( const FIX::SessionSettings &settings ) 
  {
    return fetchDestinations( settings ) ;
  }

  bool EsmNseAdapter::fetchDestinations( const FIX::SessionSettings &settings ) 
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

  void EsmNseAdapter::toApp(FIX::Message &message, const FIX::SessionID&)
    throw( FIX::DoNotSend )
  {
#ifndef NDEBUG
    UT::DismantleFix::dismantle( "OUTBOUND TO EXCHANGE ESMNSE", 
                                 message.toString() ) ;
#endif
  }

  void EsmNseAdapter::fromApp(const FIX::Message &message, 
                              const FIX::SessionID& sessionID)
    throw( FIX::FieldNotFound, 
           FIX::IncorrectDataFormat, 
           FIX::IncorrectTagValue, 
           FIX::UnsupportedMessageType )
  {
#ifndef NDEBUG
    UT::DismantleFix::dismantle( "INBOUND FROM EXCHANGE ESMNSE", 
                                 message.toString() ) ;
#endif
    crack( message, sessionID );
  }

  bool EsmNseAdapter::send( const FIX42::NewOrderSingle &message ) 
  {
    if( _sessionId.toString() == "" )
      return false ;

    DEBUG_1("Converting to NSE format" ) ;

    FIX42::NewOrderSingle newOrder( message ) ;

    // change price from rupees to paise
    FIX::Price price ;
    if ( message.isSet ( price ) ) 
    {
      message.get ( price ) ;
      price = price * PRICE_MULTIPLIER_ESMNSE  ;
      newOrder.set ( price ) ;
    }

    FIX::StopPx stopPx ;
    if ( message.isSet ( stopPx ) ) 
    {
      message.get ( stopPx ) ;
      stopPx = stopPx * PRICE_MULTIPLIER_ESMNSE  ;
      newOrder.set ( stopPx ) ;
    }

    /*
    newOrderSingle.setField( 
      FIX::CustomerOrFirm ( FIX::CustomerOrFirm_CUSTOMER ) ) ;
    newOrderSingle.setField ( FIX::ClearingAccount ( "DummyCA" ) ) ;

    // remove custom tags used between ccl and ecl
    newOrderSingle.removeField ( FIX::FIELD::SecurityExchange ) ;

    // remove custom tags used between ccl and oms
    newOrderSingle.removeField ( CUSTOMTAGS::AlgorithmType ) ;
    newOrderSingle.removeField ( CUSTOMTAGS::ParentOrderId ) ;
    newOrderSingle.removeField ( CUSTOMTAGS::UserId ) ;
    newOrderSingle.removeField ( CUSTOMTAGS::DeltaQty ) ;
    newOrderSingle.removeField ( CUSTOMTAGS::DerivativeSymbolType ) ;
       */

    return FIX::Session::sendToTarget( newOrder, _sessionId ) ;
  }

  bool EsmNseAdapter::send( const FIX42::OrderCancelRequest &order )
  {
    if( _sessionId.toString() == "" )
      return false ;

    DEBUG_1( "Creating a new cancel request from the old one" ) ;
    FIX42::OrderCancelRequest cancelRequest( order ) ;

    // orderCancel.removeField ( FIX::FIELD::SecurityExchange ) ;
    // orderCancel.removeField ( CUSTOMTAGS::DerivativeSymbolType ) ;

    return FIX::Session::sendToTarget( cancelRequest, _sessionId ) ;
  }

  bool EsmNseAdapter::send( const FIX42::OrderCancelReplaceRequest &order )
  {
    if( _sessionId.toString() == "" )
      return false ;

    FIX42::OrderCancelReplaceRequest replaceOrder( order ) ;

    // orderReplace.setField( 
    //  FIX::CustomerOrFirm ( FIX::CustomerOrFirm_CUSTOMER ) ) ;
    // orderReplace.setField ( FIX::ClearingAccount ( "DummyCA" ) ) ;
    // orderReplace.removeField ( FIX::FIELD::SecurityExchange ) ;
    // orderReplace.removeField ( CUSTOMTAGS::DeltaQty ) ;
    // orderReplace.removeField ( CUSTOMTAGS::DerivativeSymbolType ) ;

    FIX::Price price ;
    if ( order.isSet ( price ) )
    {
      order.get ( price ) ;
      price = price * PRICE_MULTIPLIER_ESMNSE  ;
      replaceOrder.set ( price ) ;
    }

    FIX::StopPx stopPx ;
    if ( order.isSet ( stopPx ) )
    {
      order.get ( stopPx ) ;
      stopPx = stopPx * PRICE_MULTIPLIER_ESMNSE  ;
      replaceOrder.set ( stopPx ) ;
    }

    FIX::OrderQty lOrderQty ;
    FIX::CumQty lCumQty ;
    order.get( lOrderQty ) ;
    order.getField( lCumQty ) ;
    lOrderQty = lOrderQty - lCumQty ;

    replaceOrder.set( lOrderQty ) ;

    return FIX::Session::sendToTarget( replaceOrder, _sessionId ) ;
  }

  void EsmNseAdapter::onMessage( 
      const FIX42::ExecutionReport &message, 
      const FIX::SessionID& )
  {
    FIX42::ExecutionReport exReport( message ) ;
    exReport.set( FIX::SecurityExchange( MARKET_ID_ESM_NSE ) ) ;

    FIX::ExecType execType ;
    message.get ( execType ) ;
    if ( execType == ExecType_NSE_STOP_LOSS_TRIGGERED )
    {
      exReport.set( execType = FIX::ExecType_TRIGGERED_OR_ACTIVATED_BY_SYSTEM );
    }

    FIX::Price price ;
    if ( message.isSet ( price ) )
    {
      message.get ( price ) ;
      price = price / PRICE_MULTIPLIER_ESMNSE  ;
      exReport.set ( price ) ;
    }

    FIX::AvgPx avgPx ;
    if ( message.isSet ( avgPx ) )
    {
      message.get ( avgPx ) ;
      avgPx = avgPx / PRICE_MULTIPLIER_ESMNSE  ;
      exReport.set ( avgPx ) ;
    }

    FIX::LastPx lastPx ;
    if ( message.isSet ( lastPx ) )
    {
      message.get ( lastPx ) ;
      lastPx = lastPx / PRICE_MULTIPLIER_ESMNSE  ;
      exReport.set ( lastPx ) ;
    }

    FIX::StopPx stopPx ;
    if ( message.isSet ( stopPx ) )
    {
      message.get ( stopPx ) ;
      stopPx = stopPx / PRICE_MULTIPLIER_ESMNSE  ;
      exReport.set ( stopPx ) ;
    }

    OmsHandler::getInstance().sendToOms( exReport ) ;
  }

  void EsmNseAdapter::onMessage ( const FIX42::OrderCancelReject &message, 
                                  const FIX::SessionID& )
  {
    FIX42::OrderCancelReject cancelReject( message ) ;
    cancelReject.setField( FIX::SecurityExchange( MARKET_ID_ESM_NSE ) ) ;

    OmsHandler::getInstance().sendToOms( cancelReject ) ;
  }

  void EsmNseAdapter::onMessage( 
      const FIX42::BusinessMessageReject &message, 
      const FIX::SessionID& )
  {
    FIX42::BusinessMessageReject reject( message ) ;

    OmsHandler::getInstance().sendToOms( reject ) ;
  }

  void EsmNseAdapter::onMessage( const FIX42::News &, const FIX::SessionID& )
  {
    ERROR_1( MESSAGE_NOT_HANDLED, "News" ) ;
  }
}}

#endif // defined(WITH_ESMNSE_FIX42)
