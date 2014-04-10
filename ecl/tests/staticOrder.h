/*******************************************************************************
* Date      | Name   | Description                                             *
* 03 Oct 13 | Jovito | Req #1848 : Test Cases For ECL                          *
*******************************************************************************/

#ifndef UT_TEST_ECL_STATIC_ORDER_H
#define UT_TEST_ECL_STATIC_ORDER_H

namespace UT { namespace ECL { namespace TESTS
{
  class StaticOrder 
  {
    public :
      static FIX42::NewOrderSingle getNseCmOrder() 
      {
        FIX::OrdType ordType( FIX::OrdType_LIMIT );

        FIX42::NewOrderSingle newOrderSingle(
            FIX::ClOrdID( "1" ), 
            FIX::HandlInst( '1' ), 
            FIX::Symbol("BHEL"), 
            FIX::Side_BUY,
            FIX::TransactTime(), 
            ordType 
            ) ;

        newOrderSingle.set( FIX::OrderQty( 50 ) );
        newOrderSingle.set( FIX::TimeInForce( FIX::TimeInForce_DAY ) ) ;
        if(    ordType == FIX::OrdType_LIMIT 
            || ordType == FIX::OrdType_STOP_LIMIT )
        {
          newOrderSingle.set( FIX::Price( 150 ) ) ;
        }
        if(    ordType == FIX::OrdType_STOP 
            || ordType == FIX::OrdType_STOP_LIMIT )
        {
          newOrderSingle.set( FIX::StopPx( 149 ) ) ;
        }

        // // Extras start here
        newOrderSingle.set( FIX::SecurityID( "50562" ) ) ;
        newOrderSingle.set( FIX::SymbolSfx( "EQ" ) ) ;
        newOrderSingle.set( FIX::SecurityExchange( "NSE" ) ) ;
        newOrderSingle.set( 
            FIX::SecurityType( FIX::SecurityType_COMMON_STOCK ) ) ;
        newOrderSingle.set( FIX::ComplianceID( "111111111111100" ) ) ;

        newOrderSingle.set( 
            FIX::CustomerOrFirm( FIX::CustomerOrFirm_CUSTOMER ) ) ;

        return newOrderSingle;
      }

      static FIX42::NewOrderSingle getNseFoOrder() 
      {
        FIX::OrdType ordType( FIX::OrdType_LIMIT );

        FIX42::NewOrderSingle newOrderSingle(
            FIX::ClOrdID( "1" ), 
            FIX::HandlInst( '1' ), 
            FIX::Symbol("NIFTY"), 
            FIX::Side_BUY,
            FIX::TransactTime(), 
            ordType 
            ) ;

        newOrderSingle.set( FIX::OrderQty( 50 ) );
        newOrderSingle.set( FIX::TimeInForce( FIX::TimeInForce_DAY ) ) ;
        if(    ordType == FIX::OrdType_LIMIT 
            || ordType == FIX::OrdType_STOP_LIMIT )
        {
          newOrderSingle.set( FIX::Price( 5299 ) ) ;
        }

        if(    ordType == FIX::OrdType_STOP 
            || ordType == FIX::OrdType_STOP_LIMIT )
        {
          newOrderSingle.set( FIX::StopPx( 5298 ) ) ;
        }

        // // Extras start here
        newOrderSingle.set( FIX::SecurityID( "50562" ) ) ;
        newOrderSingle.set( FIX::SecurityExchange( "NSE" ) ) ;
        newOrderSingle.set( FIX::SecurityType( FIX::SecurityType_FUTURE ) ) ;
        newOrderSingle.set( FIX::ComplianceID( "111111111111100" ) ) ;
        newOrderSingle.set( FIX::MaturityMonthYear ( "201308" ) ) ;
        newOrderSingle.set( FIX::MaturityDay  ( "29" ) ) ;
        newOrderSingle.setField( 5005, "IDX" ) ;

        newOrderSingle.set( 
            FIX::CustomerOrFirm( FIX::CustomerOrFirm_CUSTOMER ) ) ;

        // NSE O
        // newOrderSingle.set( FIX::StrikePrice ( 201308 ) ) ;
        // newOrderSingle.set( FIX::PutOrCall ( FIX::PutOrCall_PUT ) ) ;
        // newOrderSingle.set( FIX::OptAttribute ( 'E' ) ) ;

        return newOrderSingle;
      }    

      static FIX42::NewOrderSingle getNseCdsOrder() 
      {
        FIX::OrdType ordType( FIX::OrdType_LIMIT );

        FIX42::NewOrderSingle newOrderSingle(
            FIX::ClOrdID( "1" ), 
            FIX::HandlInst( '1' ), 
            FIX::Symbol("EURINR"), 
            FIX::Side_BUY,
            FIX::TransactTime(), 
            ordType 
            ) ;

        newOrderSingle.set( FIX::OrderQty( 50 ) );
        newOrderSingle.set( FIX::TimeInForce( FIX::TimeInForce_DAY ) ) ;
        if(    ordType == FIX::OrdType_LIMIT 
            || ordType == FIX::OrdType_STOP_LIMIT )
        {
          newOrderSingle.set( FIX::Price( 78.6 ) ) ;
        }
        if( ordType == FIX::OrdType_STOP || ordType == FIX::OrdType_STOP_LIMIT )
        {
          newOrderSingle.set( FIX::StopPx( 78.5 ) ) ;
        }

        // // Extras start here
        newOrderSingle.set( FIX::SecurityID( "1377" ) ) ;
        newOrderSingle.set( FIX::SecurityExchange( "NSECDS" ) ) ;
        newOrderSingle.set( FIX::SecurityType( FIX::SecurityType_FUTURE ) ) ;
        newOrderSingle.set( FIX::ComplianceID( "111111111111100" ) ) ;
        newOrderSingle.set( FIX::MaturityMonthYear( "201309" ) ) ;
        newOrderSingle.set( FIX::MaturityDay( "26" ) ) ;
        newOrderSingle.setField( 5005, "IDX" ) ;
        // newOrderSingle.set( FIX::MaxFloor( 0 ) ) ;

        newOrderSingle.set( 
            FIX::CustomerOrFirm( FIX::CustomerOrFirm_CUSTOMER ) ) ;

        // NSE O
        // newOrderSingle.set( FIX::StrikePrice ( 201308 ) ) ;
        // newOrderSingle.set( FIX::PutOrCall ( FIX::PutOrCall_PUT ) ) ;
        // newOrderSingle.set( FIX::OptAttribute ( 'E' ) ) ;

        return newOrderSingle;
      }

      static FIX42::NewOrderSingle getBseEdOrder() 
      {
        FIX::OrdType ordType( FIX::OrdType_LIMIT );

        FIX42::NewOrderSingle newOrderSingle(
            FIX::ClOrdID( "1" ), 
            FIX::HandlInst( '1' ), 
            FIX::Symbol("BHEL"), 
            FIX::Side_BUY,
            FIX::TransactTime(), 
            ordType 
            ) ;

        newOrderSingle.set( FIX::OrderQty( 50 ) );
        newOrderSingle.set( FIX::TimeInForce( FIX::TimeInForce_DAY ) ) ;
        if( ordType == FIX::OrdType_LIMIT || ordType == FIX::OrdType_STOP_LIMIT)
        {
          newOrderSingle.set( FIX::Price( 150 ) ) ;
        }
        if( ordType == FIX::OrdType_STOP || ordType == FIX::OrdType_STOP_LIMIT )
        {
          newOrderSingle.set( FIX::StopPx( 149 ) ) ;
        }

        // Extras start here
        newOrderSingle.set( FIX::SecurityID( "500103" ) ) ;
        newOrderSingle.set( FIX::SymbolSfx( "A" ) ) ;
        newOrderSingle.set( FIX::SecurityExchange( "BSE" ) ) ;
        newOrderSingle.set( 
            FIX::SecurityType( FIX::SecurityType_COMMON_STOCK ) ) ;
        newOrderSingle.set( FIX::ComplianceID( "1111111111111000" ) ) ;

        newOrderSingle.set( FIX::Account ( "TESTACCNT" ) ) ;
        newOrderSingle.set( 
            FIX::CustomerOrFirm( FIX::CustomerOrFirm_CUSTOMER ) ) ;

        return newOrderSingle;
      }

      static FIX42::NewOrderSingle getEsmNseOrder() 
      {
        FIX::OrdType ordType( FIX::OrdType_LIMIT );

        FIX42::NewOrderSingle newOrderSingle(
            FIX::ClOrdID( "1" ), 
            FIX::HandlInst( '1' ), 
            FIX::Symbol("BHEL"), 
            FIX::Side_BUY,
            FIX::TransactTime(), 
            ordType 
            ) ;

        newOrderSingle.set( FIX::OrderQty( 50 ) );
        newOrderSingle.set( FIX::TimeInForce( FIX::TimeInForce_DAY ) ) ;
        if( ordType == FIX::OrdType_LIMIT || ordType == FIX::OrdType_STOP_LIMIT)
        {
          newOrderSingle.set( FIX::Price( 150 ) ) ;
        }
        if( ordType == FIX::OrdType_STOP || ordType == FIX::OrdType_STOP_LIMIT )
        {
          newOrderSingle.set( FIX::StopPx( 149 ) ) ;
        }

        // // Extras start here
        newOrderSingle.set( FIX::SecurityID( "50562" ) ) ;
        newOrderSingle.set( FIX::SymbolSfx( "EQ" ) ) ;
        newOrderSingle.set( FIX::SecurityExchange( "ESMNSE" ) ) ;
        newOrderSingle.set( 
            FIX::SecurityType( FIX::SecurityType_COMMON_STOCK ) ) ;
        newOrderSingle.set( FIX::ComplianceID( "111111111111100" ) ) ;

        newOrderSingle.set( 
            FIX::CustomerOrFirm( FIX::CustomerOrFirm_CUSTOMER ) ) ;

        return newOrderSingle;
      }

      /*
FIX42::OrderCancelRequest Application::queryOrderCancelRequest42()
{
  FIX42::OrderCancelRequest orderCancelRequest( queryOrigClOrdID(),
      queryClOrdID(), querySymbol(), querySide(), FIX::TransactTime() );

  orderCancelRequest.set( queryOrderQty() );

  // Note that errors are not sent back. Need to handle

  // Extras start here
  orderCancelRequest.set( FIX::SecurityExchange( "ESM" ) ) ;
  orderCancelRequest.set( FIX::SecurityID( "50562" ) ) ;
  orderCancelRequest.set( FIX::OrderID( "0201308080533045134" ) ) ;
  orderCancelRequest.setField( FIX::OrdType( FIX::OrdType_LIMIT ) ) ;
  orderCancelRequest.set( FIX::SecurityType( FIX::SecurityType_COMMON_STOCK ) );

  // BSE
  orderCancelRequest.set( FIX::Account( "TESTACCOUNT" ) ) ;
  orderCancelRequest.set( FIX::ComplianceID( "111111111111100" ) ) ;

  // NSE CM
  orderCancelRequest.set( FIX::SymbolSfx( "EQ" ) ) ;
  orderCancelRequest.setField( 5022, "19700101-00:00:00" ) ;

  // NSE F
  orderCancelRequest.set( FIX::MaturityMonthYear ( "201308" ) ) ;
  orderCancelRequest.set( FIX::MaturityDay  ( "29" ) ) ;
  orderCancelRequest.setField( 5005, "IDX" ) ;
  orderCancelRequest.set( FIX::MaturityMonthYear( "201308" ) ) ;
  orderCancelRequest.set( FIX::Account( "JOVI" ) ) ;
  orderCancelRequest.set( FIX::MaturityDay( "29" ) ) ;
  
  // NSE O
  orderCancelRequest.set( FIX::StrikePrice ( 201308 ) ) ;
  orderCancelRequest.set( FIX::PutOrCall ( FIX::PutOrCall_PUT ) ) ;
  orderCancelRequest.set( FIX::OptAttribute ( 'E' ) ) ;


  //orderCancelRequest.set( FIX::AlgorithmType( "NONE" ) ) ;
  //orderCancelRequest.set( FIX::ParentOrderId( "NONE" ) ) ;
  //orderCancelRequest.set( FIX::UserId( "JOVI" ) ) ;
  //orderCancelRequest.set( FIX::DerivativeSymbolType( "IDX" ) ) ;
  //orderCancelRequest.set( FIX::ExchCreateTime( "20130807-11:49:46" ) ) ;
  //orderCancelRequest.set( FIX::ExchModifyTime( "20130807-11:50:52" ) ) ;
  //orderCancelRequest.set( FIX::ProductType( "INTRADAY" ) ) ;
  //orderCancelRequest.set( FIX::SquareOff( "N" ) ) ;
  //orderCancelRequest.set( FIX::SeqNum( "5" ) ) ;
  queryHeader( orderCancelRequest.getHeader() );
  return orderCancelRequest;
}

FIX42::OrderCancelReplaceRequest Application::queryCancelReplaceRequest42()
{
  FIX42::OrderCancelReplaceRequest cancelReplaceRequest(
    queryOrigClOrdID(), queryClOrdID(), FIX::HandlInst( '1' ),
    querySymbol(), querySide(), FIX::TransactTime(), queryOrdType() );

  //if ( queryConfirm( "New price" ) )
    //cancelReplaceRequest.set( queryPrice() );
  //if ( queryConfirm( "New quantity" ) )
    //cancelReplaceRequest.set( queryOrderQty() );

  // Extra fields required
  cancelReplaceRequest.set( FIX::SecurityExchange( "ESM" ) ) ;
  cancelReplaceRequest.set( FIX::SecurityID( "50562" ) ) ;
  cancelReplaceRequest.set( FIX::OrderID( "0201308080533045134" ) ) ;
  cancelReplaceRequest.set( FIX::Price( 5001.00 ) ) ;
  cancelReplaceRequest.set( FIX::OrderQty( 100 ) ) ;
  cancelReplaceRequest.setField( FIX::CumQty( 0 ) ) ;
  cancelReplaceRequest.set( 
      FIX::SecurityType( FIX::SecurityType_COMMON_STOCK ) ) ;

  // BSE
  cancelReplaceRequest.set( FIX::Account( "TESTACCOUNT" ) ) ;
  cancelReplaceRequest.set( FIX::ComplianceID( "111111111111100" ) ) ;
  cancelReplaceRequest.setField( 5024, "L" ) ;
  cancelReplaceRequest.setField( 5004, "+5" ) ;
  
  //// NSE CM
  cancelReplaceRequest.set( FIX::SymbolSfx( "XX" ) ) ;
  cancelReplaceRequest.setField( 5021, "19700101-00:00:00" ) ;
  cancelReplaceRequest.setField( 5022, "19700101-00:00:00" ) ;

  // NSE F
  cancelReplaceRequest.set( FIX::MaturityMonthYear ( "201308" ) ) ;
  cancelReplaceRequest.set( FIX::MaturityDay  ( "29" ) ) ;
  cancelReplaceRequest.setField( 5005, "IDX" ) ;
  
  // NSE O
  cancelReplaceRequest.set( FIX::StrikePrice ( 201308 ) ) ;
  cancelReplaceRequest.set( FIX::PutOrCall ( FIX::PutOrCall_PUT ) ) ;
  cancelReplaceRequest.set( FIX::OptAttribute ( 'E' ) ) ;

  // Others
  //cancelReplaceRequest.set( FIX::Account( "JOVI" ) ) ;
  //cancelReplaceRequest.set( FIX::TimeInForce( FIX::TimeInForce_DAY ) ) ;
  //cancelReplaceRequest.set( FIX::SettlmntTyp( FIX::SettlmntTyp_CASH ) ) ;
  //cancelReplaceRequest.set( FIX::MaxFloor( 0 ) ) ;
  //cancelReplaceRequest.set( FIX::MaturityMonthYear( "201308" ) ) ;
  //cancelReplaceRequest.set( 
  FIX::CustomerOrFirm( FIX::CustomerOrFirm_CUSTOMER ) ) ;
  //cancelReplaceRequest.set( FIX::MaturityDay( "29" ) ) ;
  //cancelReplaceRequest.set( FIX::NoTradingSessions( "1" ) ) ;
  //cancelReplaceRequest.set( FIX::TradingSessionID( "RL" ) ) ;


  //cancelReplaceRequest.set( FIX::AlgorithmType( "NONE" ) ) ;
  //cancelReplaceRequest.set( FIX::ParentOrderId( "NONE" ) ) ;
  //cancelReplaceRequest.set( FIX::UserId( "JOVI" ) ) ;
  //cancelReplaceRequest.set( FIX::DeltaQty( "0" ) ) ;
  //cancelReplaceRequest.set( FIX::DerivativeSymbolType( "IDX" ) ) ;    
  //cancelReplaceRequest.set( FIX::ExchCreateTime( "20130807-11:49:46" ) ) ;
  //cancelReplaceRequest.set( FIX::ExchModifyTime( "20130807-11:49:46" ) ) ;
  //cancelReplaceRequest.set( FIX::ProductType( "INTRADAY" ) ) ;
  //cancelReplaceRequest.set( FIX::SquareOff( "N" ) ) ;    
  //cancelReplaceRequest.set( FIX::SeqNum( "3" ) ) ;     

  queryHeader( cancelReplaceRequest.getHeader() );
  return cancelReplaceRequest;
}

         */
  };

}}}
#endif // UT_TEST_ECL_STATIC_ORDER_H
