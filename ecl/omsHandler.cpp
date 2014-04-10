#include "omsHandler.h"
#include "adapters_fwd.h"
#include "eclConstants.h"

#include "../common/constants.h"
#include "../common/converter.h"
#include "../common/errorMessages.h"
#include "../common/dismantleFix.h"
#include "../common/exceptions.h"

#include <quickfix/fix42/NewOrderSingle.h>
#include <quickfix/fix42/ExecutionReport.h>
#include <quickfix/fix42/OrderCancelRequest.h>
#include <quickfix/fix42/OrderCancelReplaceRequest.h>
#include <quickfix/fix42/OrderCancelReject.h>
#include <quickfix/fix42/NewOrderSingle.h>
#include <quickfix/fix42/Reject.h>

namespace UT { namespace ECL
{
  OmsHandler *OmsHandler::_instance = NULL ;
  boost::mutex OmsHandler::_mutexOnInstance ;

  OmsHandler::OmsHandler() 
  {
  }

  OmsHandler::OmsHandler( const OmsHandler& ) 
  {
  }

  OmsHandler &OmsHandler::operator = ( const OmsHandler & ) {
    return getInstance() ;
  }

  OmsHandler &OmsHandler::getInstance() 
  {
    if( _instance != NULL )
      return *_instance ;

    _mutexOnInstance.lock() ;

    if( _instance != NULL )
      return *_instance ;

    _instance = new OmsHandler() ;
    return *_instance ;

    _mutexOnInstance.unlock() ;
  }

  void OmsHandler::onLogon( const FIX::SessionID& sessionID ) 
  {
  }

  void OmsHandler::onLogout( const FIX::SessionID& sessionID ) 
  {
  }

  void OmsHandler::toApp( FIX::Message&, const FIX::SessionID& )
    throw( FIX::DoNotSend ) 
    {
    }

  void OmsHandler::fromApp( const FIX::Message& message, 
                            const FIX::SessionID& sessionID )
    throw( FIX::FieldNotFound, 
           FIX::IncorrectDataFormat, 
           FIX::IncorrectTagValue, 
           FIX::UnsupportedMessageType )
    {
#ifndef NDEBUG
      if( sessionID.toString().find( "oms" ) != std::string::npos ) {
        UT::DismantleFix::dismantle( "INBOUND FROM OMS", message.toString() ) ;
      }
      else {
        UT::DismantleFix::dismantle( "INBOUND FROM EXCHANGE", 
                                     message.toString() ) ;
      }
#endif

      /*
      _threadPool.post( boost::bind( &ECL::crackMessage, 
            this, 
            message, 
            sessionID ) ) ;
            */
      crack( message, sessionID ) ;
    }

  bool OmsHandler::reset( const FIX::SessionSettings &settings ) 
  {
    return fetchOmsDestination( settings ) ;
  }

  template< class Message >
    void OmsHandler::send( const Message &message ) 
    {
      try
      {
        std::string securityExchange( message.getField ( 
                                       FIX::FIELD::SecurityExchange ) ) ;

#if defined(WITH_PLUS_FIX44)
        if( securityExchange == MARKET_ID_PLUS ) 
        {
          DEBUG_1( "Message is for PLUS " ) ;

          if( ! PlusAdapter::getInstance().send( message ) )
          {
            rejectOrder( 
                message, 
                ERRORCODE_EXCHANGE_NOT_CONNECTED, 
                STR_ERRORCODE_EXCHANGE_NOT_CONNECTED 
                ) ;
          }
          return ;
        } 
#endif // WITH_PLUS_FIX44

#if defined(WITH_ESMNSE_FIX42)
        if ( securityExchange == MARKET_ID_ESM_NSE 
            || securityExchange == MARKET_ID_ESM ) 
        {
          DEBUG_1( "Message is for NSE FIX " ) ;

          if( ! EsmNseAdapter::getInstance().send( message ) )
          {
            rejectOrder( 
                message, 
                ERRORCODE_EXCHANGE_NOT_CONNECTED,
                STR_ERRORCODE_EXCHANGE_NOT_CONNECTED
                ) ;
          }

          return ;
        }
#endif // defined(WITH_ESMNSE_FIX42)

#if defined(WITH_ESMBSE_FIX50)
        if ( securityExchange == MARKET_ID_ESM_BSE )
        {
          DEBUG_1( "Message is for BSE FIX " ) ;

          if( ! BseFixAdapter::getInstance().send( message ) )
          {
            rejectOrder( 
                message, 
                ERRORCODE_EXCHANGE_NOT_CONNECTED, i
                STR_ERRORCODE_EXCHANGE_NOT_CONNECTED i
                ) ;
          }
          return ;
        }
#endif // defined(WITH_ESMBSE_FIX50)

        rejectOrder( 
            message, 
            0, 
            std::string("Exchange does not exist : ") + securityExchange ) ;
      }
      catch ( FIX::FieldNotFound &e)
      {
        rejectOrder( 
            message, 
            0, 
            e.what() + std::string( ". Field : ") 
                     + StringConverter::toString( e.field ) ) ;
      }
      catch ( std::exception &e ) 
      {
        rejectOrder( message, 0, e.what() );
      }
    }

  void OmsHandler::onMessage( 
      const FIX42::NewOrderSingle &message, 
      const FIX::SessionID& )
  {
    ECL_ORDER_LOG_FROM_OMS( "Pending New" ) ;

    std::string errorText ;
    int errorNo = 0 ; // isValidOrder( message, errorText ) ;
    if( errorNo != 0 )
    {
      rejectOrder( message, errorNo, errorText ) ;
    }
    else
    {
      send<FIX42::NewOrderSingle>( message ) ;
    }
  }

  void OmsHandler::onMessage ( const FIX42::NewOrderList&, 
                               const FIX::SessionID& )
  {
#if defined(WITH_NSE_NNF) || defined(WITH_NSE_FO_NNF)
    if( ! NnfFoAdapter::getInstance().send( newOrderList ) )
    {
      rejectOrder( 
          message, 
          ERRORCODE_EXCHANGE_NOT_CONNECTED, 
          STR_ERRORCODE_EXCHANGE_NOT_CONNECTED 
          ) ;
    }
#endif
  }

  void OmsHandler::onMessage( 
      const FIX42::OrderCancelRequest &message,
      const FIX::SessionID& )
  {
    ECL_ORDER_LOG_FROM_OMS( "Pending Cancel" ) ;
    send<FIX42::OrderCancelRequest>( message ) ;
  }

  void OmsHandler::onMessage( 
      const FIX42::OrderCancelReplaceRequest &message, 
      const FIX::SessionID& )
  {
    ECL_ORDER_LOG_FROM_OMS( "Pending Replace" ) ;

    std::string errorText ;
    int errorNo = 0 ; // isValidOrder( message, errorText ) ;
    if( errorNo != 0 )
    {
      rejectOrder( message, errorNo, errorText ) ;
    }
    else
    {
      send<FIX42::OrderCancelReplaceRequest>( message ) ;
    }
  }

  void OmsHandler::onMessage ( const FIX42::OrderCancelReject&, 
                               const FIX::SessionID& )
  {
  }

  void OmsHandler::sendToOms( FIX42::Message &message ) 
  {
    try
    {
      FIX::Session::sendToTarget( 
          message ,
          _eclCompId,
          _omsCompId 
          ) ;
    }
    catch ( std::exception &e )
    {
      ERROR_1( CANNOT_SEND_FIX_MSG, e.what() ) ;
    }
  }

  void OmsHandler::sendReject ( const std::string &clOrdId,
      const FIX::MsgSeqNum &msgSeqNum,
      const std::string &msgType,
      const int tagNum ,
      const int rejectReason,
      const std::string &rejectReasonTxt
      )
  {
    FIX42::Reject reject ;

    reject.set( FIX::RefSeqNum  ( msgSeqNum ) ) ;
    reject.set( FIX::RefMsgType ( msgType   ) ) ;
    reject.set( FIX::RefTagID   ( tagNum   ) ) ;
    reject.set( FIX::Text       ( rejectReasonTxt   ) ) ;
    reject.set( FIX::SessionRejectReason ( rejectReason ) );

    sendToOms( reject ) ;
  }

  void OmsHandler::rejectOrder( 
      const FIX42::NewOrderSingle &newOrderSingle,
      int errorNo,
      const std::string &errorText 
      ) 
  {
    FIX::Side lSide ;

    FIX42::ExecutionReport 
      fixReport ( 
          FIX::OrderID( "0" ),
          FIX::ExecID( "0" ),
          FIX::ExecTransType_NEW,            
          FIX::ExecType_NEW,
          FIX::OrdStatus_REJECTED,
          newOrderSingle.getField( FIX::FIELD::Symbol ),
          newOrderSingle.get( lSide ),
          FIX::LeavesQty( 0 ),
          FIX::CumQty( 0 ),
          FIX::AvgPx( 0 )
          );

    FIX::ClOrdID lClOrdID ;
    newOrderSingle.get( lClOrdID );
    fixReport.set( lClOrdID ) ;

    fixReport.set( FIX::Text( errorText ) ) ;
    fixReport.set( FIX::TransactTime() ) ;

    sendToOms ( fixReport ) ;
  }

  void OmsHandler::rejectOrder( 
      const FIX42::OrderCancelRequest &cancelOrder,
      int errorNo,
      const std::string &errorText 
      ) 
  {
    FIX42::OrderCancelReject cancelReject(
        FIX::OrderID( "0" ),
        cancelOrder.getField( FIX::FIELD::ClOrdID ),
        cancelOrder.getField( FIX::FIELD::OrigClOrdID ),
        ORD_STATUS_UPDATED,   //FIX::OrdStatus ( 'U' ),
        FIX::CxlRejResponseTo_ORDER_CANCEL_REQUEST 
        ) ;

    cancelReject.set( FIX::Text( errorText ) ) ;

    OmsHandler::getInstance().sendToOms( cancelReject ) ;
  }

  void OmsHandler::rejectOrder( 
      const FIX42::OrderCancelReplaceRequest &replaceOrder,
      int errorNo,
      const std::string &errorText ) 
  {
    FIX42::OrderCancelReject replacelReject(
        FIX::OrderID( "0" ),
        replaceOrder.getField( FIX::FIELD::ClOrdID ),
        replaceOrder.getField( FIX::FIELD::OrigClOrdID ),
        ORD_STATUS_UPDATED,   //FIX::OrdStatus ( 'U' ),
        FIX::CxlRejResponseTo_ORDER_CANCEL_REPLACE_REQUEST ) ;

    replacelReject.set( FIX::Text( errorText ) ) ;

    OmsHandler::getInstance().sendToOms( replacelReject ) ;
  }

  bool OmsHandler::fetchOmsDestination( const FIX::SessionSettings &settings ) 
  {
    try
    {  
      std::set< FIX::SessionID > sessions = settings.getSessions() ;
      std::set< FIX::SessionID >::iterator iSessions  = sessions.begin() ;

      for( ; iSessions != sessions.end() ; ++iSessions )
      {
        const FIX::Dictionary &iDictionary = settings.get( *iSessions ) ;

        if ( iDictionary.getString( FIX::CONNECTION_TYPE ) == FIX_ACCEPTOR )
        {
          _eclCompId = FIX::SenderCompID( 
                                iDictionary.getString ( FIX::SENDERCOMPID ) ) ;
          _omsCompId = FIX::TargetCompID( 
                                iDictionary.getString ( FIX::TARGETCOMPID ) ) ;

          return true ;
        }
      }
    }
    catch ( ConfigError &e )
    {
      ERROR_1( CONFIG_ERROR_READING_OMS_DESTINATION, e.what() ) ;
      return false ;
    }

    ERROR_1( CONFIG_ERROR_READING_OMS_DESTINATION, 
             "Cannot Find Accepto Session For OMS" ) ;
    return false ;
  }
}}
