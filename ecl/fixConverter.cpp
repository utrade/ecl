#include "fixConverter.h"
#include "eclConstants.h"

#include <quickfix/fix42/NewOrderSingle.h>
#include <quickfix/fix42/OrderCancelRequest.h>
#include <quickfix/fix42/OrderCancelReplaceRequest.h>
#include <quickfix/fix42/ExecutionReport.h>
#include <quickfix/fix42/OrderCancelReject.h>
#include <quickfix/fix42/BusinessMessageReject.h>

#include <quickfix/fix44/NewOrderSingle.h>
#include <quickfix/fix44/OrderCancelRequest.h>
#include <quickfix/fix44/OrderCancelReplaceRequest.h>
#include <quickfix/fix44/ExecutionReport.h>
#include <quickfix/fix44/OrderCancelReject.h>
#include <quickfix/fix44/BusinessMessageReject.h>

namespace UT
{
  FIX44::NewOrderSingle FixConverter::toFix44( 
      const FIX42::NewOrderSingle &message ) 
  {
    FIX::ClOrdID lClOrdID ;
    message.get( lClOrdID );

    FIX::Side lSide ;
    message.get( lSide );

    FIX::OrdType lOrdType ;
    message.get( lOrdType );

    FIX::TransactTime lTransactTime ;
    message.get( lTransactTime );

    FIX44::NewOrderSingle newOrder( lClOrdID,
                                    lSide,
                                    lTransactTime,
                                    lOrdType ) ;

    switch( lOrdType )
    {
      case FIX::OrdType_LIMIT :
        newOrder.setField( FIX::FIELD::Price, 
                           message.getField( FIX::FIELD::Price ) ) ;
        break ;

      case FIX::OrdType_STOP_LIMIT :
        newOrder.setField( FIX::FIELD::Price, 
                           message.getField( FIX::FIELD::Price ) ) ;
        newOrder.setField( FIX::FIELD::StopPx, 
                           message.getField( FIX::FIELD::StopPx ) ) ;
        break ;

      case FIX::OrdType_STOP :
        newOrder.setField( FIX::FIELD::StopPx, 
                           message.getField( FIX::FIELD::StopPx ) ) ;
        break; 
    }

    newOrder.setField( FIX::FIELD::TimeInForce, 
                       message.getField( FIX::FIELD::TimeInForce ) ) ;
    // 0 = Day (default for Limit/Pegged Orders if not specified)
    // 3 = IOC (default for Market  Orders if not specified)
    // 4 = FOK
    // 126 ExpireTime N UTCTimestamp Only valid  when TImeInForce 
    //        is set to Day Order 
    // 110 MinQty N Qty Minimum quantity of an order to be executed Valid 
    //        for IOC orders only

    newOrder.setField( FIX::FIELD::Account, 
                       message.getField( FIX::FIELD::Account ) ) ;
    newOrder.setField( FIX::FIELD::Symbol, 
                       message.getField( FIX::FIELD::Symbol ) ) ;
    newOrder.setField( FIX::FIELD::OrderQty, 
                       message.getField( FIX::FIELD::OrderQty ) ) ;

    //18 ExecInst N String Instructions for order handling M = Mid-price Peg 
    //   P = Market Peg R =  Primary Peg
    //528 OrderCapacity N Char The capacity in which the reporting member is 
    //    trading A = Agency P = Principal (Default)
    //211 PegOffsetValue N Float Amount (signed) added to the peg for a pegged 
    //    order, Specified in the currency of the instrument

    return newOrder ;
  }

  FIX44::OrderCancelRequest FixConverter::toFix44( 
      const FIX42::OrderCancelRequest &message ) 
  {
    FIX::OrigClOrdID lOrigClOrdID ;
    message.get( lOrigClOrdID ) ;

    FIX::ClOrdID lClOrdID ;
    message.get( lClOrdID ) ;

    FIX::Side lSide ;
    message.get( lSide ) ;

    FIX::TransactTime lTransactTime ;
    message.get( lTransactTime ) ;

    FIX44::OrderCancelRequest orderCancel( lOrigClOrdID,
                                           lClOrdID,
                                           lSide,
                                           lTransactTime ) ;

    orderCancel.setField( FIX::FIELD::OrderID, 
                          message.getField( FIX::FIELD::OrderID ) ) ;
    orderCancel.setField( FIX::FIELD::Symbol, 
                          message.getField( FIX::FIELD::Symbol ) ) ;
    orderCancel.setField( FIX::FIELD::OrderQty, 
                          message.getField( FIX::FIELD::OrderQty ) ) ;

    return orderCancel ;
  }

  FIX44::OrderCancelReplaceRequest FixConverter::toFix44( 
      const FIX42::OrderCancelReplaceRequest &message ) 
  {
    FIX::OrigClOrdID lOrigClOrdID ;
    message.get( lOrigClOrdID ) ;

    FIX::ClOrdID lClOrdID ;
    message.get( lClOrdID ) ;

    FIX::Side lSide ;
    message.get( lSide ) ;

    FIX::TransactTime lTransactTime ;
    message.get( lTransactTime ) ;

    FIX::OrdType lOrdType ;
    message.get( lOrdType ) ;

    FIX44::OrderCancelReplaceRequest orderReplace( lOrigClOrdID,
                                                   lClOrdID,
                                                   lSide,
                                                   lTransactTime,
                                                   lOrdType ) ;

    switch( lOrdType )
    {
      case FIX::OrdType_LIMIT :
        orderReplace.setField( FIX::FIELD::Price, 
                                message.getField( FIX::FIELD::Price ) ) ;
        break ;

      case FIX::OrdType_STOP :
        orderReplace.setField( FIX::FIELD::Price, 
                               message.getField( FIX::FIELD::Price ) ) ;
        orderReplace.setField( FIX::FIELD::StopPx, 
                               message.getField( FIX::FIELD::StopPx ) ) ;
        break ;

      case FIX::OrdType_STOP_LIMIT :
        orderReplace.setField( FIX::FIELD::StopPx, 
                               message.getField( FIX::FIELD::StopPx ) ) ;
        break ;
    }

    orderReplace.setField( FIX::FIELD::OrderID, 
                           message.getField( FIX::FIELD::OrderID ) ) ;
    orderReplace.setField( FIX::FIELD::Symbol, 
                           message.getField( FIX::FIELD::Symbol ) ) ;
    orderReplace.setField( FIX::FIELD::OrderQty, 
                           message.getField( FIX::FIELD::OrderQty ) ) ;
    orderReplace.setField( FIX::FIELD::TimeInForce, 
                           message.getField( FIX::FIELD::TimeInForce ) ) ;

    //    0 = Day
    //    3 = IOC
    //    4 = FOK

    return orderReplace ;
  }
  
  FIX42::ExecutionReport FixConverter::toFix42( 
      const FIX44::ExecutionReport &message ) 
  {
    FIX::OrderID orderId ;
    message.getField ( orderId ) ;

    FIX::ExecID  execId ;
    message.getField ( execId  ) ;

    FIX::OrdStatus ordStatus ;
    FIX::ExecType  execType ;
    message.getField ( ordStatus ) ;

    // Change the exectype from FIX4.4 to FIX4.2 
    message.getField ( execType ) ;
    switch( execType ) 
    {
      case FIX::ExecType_TRADE :
        execType = FIX::ExecType_FILL ;
        break ;
      case FIX::ExecType_REPLACED :
        ordStatus = FIX::OrdStatus_REPLACED ;
        break ;
    }


    FIX::Side side ;
    message.getField ( side ) ;

    FIX::LeavesQty leavesQty ;
    message.getField ( leavesQty ) ;

    FIX::CumQty  cumQty ;
    message.getField ( cumQty ) ;

    FIX42::ExecutionReport fixReport ( 
        orderId,
        execId,
        FIX::ExecTransType ( FIX::ExecTransType_NEW ),
        execType,
        ordStatus,
        message.getField ( FIX::FIELD::Symbol ),
        side,
        leavesQty,
        cumQty,
        FIX::AvgPx ( 0 ) 
        );

    FIX::ClOrdID clOrdId ;
    message.getField ( clOrdId ) ;
    fixReport.set ( clOrdId ) ;

    FIX::TransactTime transactTime ;
    message.getField ( transactTime ) ;
    fixReport.set ( transactTime ) ;

    if( message.isSetField ( FIX::FIELD::LastPx ) )
    {
      fixReport.setField( FIX::FIELD::LastPx, 
                          message.getField( FIX::FIELD::LastPx ) ) ;

      FIX::LastShares lLastShares ;
      message.getField( lLastShares ) ;
      fixReport.setField( lLastShares ) ;
    }

    FIX::Text lText ;
    if( message.isSetField( lText ) )
    {
      fixReport.set( message.get( lText ) ) ;
    }

    return fixReport ;
  }

  FIX42::OrderCancelReject FixConverter::toFix42( 
      const FIX44::OrderCancelReject &message ) 
  {
    FIX::OrderID orderId ;
    message.getField ( orderId ) ;

    FIX::ClOrdID clOrdId ;
    message.getField ( clOrdId ) ;

    FIX::OrdStatus ordStatus;
    message.getField ( ordStatus ) ;

    FIX::CxlRejResponseTo lCxlRejResponseTo ;
    message.getField ( lCxlRejResponseTo ) ;

    FIX42::OrderCancelReject cancelReject (
        orderId,
        clOrdId, 
        message.getField( FIX::FIELD::OrigClOrdID ),
        ordStatus, 
        lCxlRejResponseTo 
        ) ;

    FIX::Text lText ;
    if( message.isSetField( lText ) )
    {
      cancelReject.setField( message.getField ( lText ) ) ;
    }

    if ( message.isSetField ( FIX::FIELD::Price ) )
    {
      cancelReject.setField( FIX::FIELD::Price, 
                             message.getField( FIX::FIELD::Price ) ) ;
    }

    return cancelReject ;
  }

  FIX42::BusinessMessageReject FixConverter::toFix42( 
      const FIX44::BusinessMessageReject &message ) 
  {
    FIX42::BusinessMessageReject reject ;

    FIX::RefMsgType  lRefMsgType ;
    FIX::BusinessRejectRefID lBusinessRejectRefID ;
    FIX::BusinessRejectReason lBusinessRejectReason ;
    FIX::Text lText ;

    reject.set( message.get( lRefMsgType ) ) ;
    reject.set( message.get( lBusinessRejectRefID ) ) ;
    reject.set( message.get( lBusinessRejectReason ) ) ;

    if( message.isSet( lText ) )
    {
      reject.set( message.get( lText ) ) ;
    }
    else
    {
      switch( lBusinessRejectReason )
      {
        case FIX::BusinessRejectReason_OTHER : // 0;
          reject.setField( FIX::FIELD::Text, 
                           FIX::BusinessRejectReason_OTHER_TEXT ) ;
          break ;
        case FIX::BusinessRejectReason_UNKNOWN_ID : // 1;
          reject.setField( FIX::FIELD::Text, 
                           FIX::BusinessRejectReason_UNKNOWN_ID_TEXT ) ;
          break ;
        case FIX::BusinessRejectReason_UNKNOWN_SECURITY : // 2;
          reject.setField( FIX::FIELD::Text, 
                           FIX::BusinessRejectReason_UNKNOWN_SECURITY_TEXT ) ;
          break ;
        case FIX::BusinessRejectReason_UNSUPPORTED_MESSAGE_TYPE : // 3;
          reject.setField( 
              FIX::FIELD::Text, 
              FIX::BusinessRejectReason_UNSUPPORTED_MESSAGE_TYPE_TEXT 
              ) ;
          break ;
        case FIX::BusinessRejectReason_APPLICATION_NOT_AVAILABLE : // 4;
          reject.setField( 
              FIX::FIELD::Text, 
              FIX::BusinessRejectReason_APPLICATION_NOT_AVAILABLE_TEXT 
              ) ;
          break ;
        case FIX::BusinessRejectReason_CONDITIONALLY_REQUIRED_FIELD_MISSING :
          reject.setField( 
              FIX::FIELD::Text, 
              FIX::BusinessRejectReason_CONDITIONALLY_REQUIRED_FIELD_MISSING_TEXT 
              ) ;
          break ;
        case FIX::BusinessRejectReason_NOT_AUTHORIZED : // 6;
          reject.setField( 
              FIX::FIELD::Text, 
              FIX::BusinessRejectReason_NOT_AUTHORIZED_TEXT 
              ) ;
          break ;
        case FIX::BusinessRejectReason_INVALID_PRICE_INCREMENT : // 18;
        case BusinessRejectReason_INVALID_PRICE_INCREMENT_PLUS : // 16;
          reject.setField( 
              FIX::FIELD::Text, 
              FIX::BusinessRejectReason_DELIVERTO_FIRM_NOT_AVAILABLE_AT_THIS_TIME_TEXT 
              ) ;
          break ;
        default:
          reject.setField( FIX::FIELD::Text, 
              FIX::BusinessRejectReason_OTHER_TEXT ) ;
          break ;
      }
    }

    return reject ;
  }

}
