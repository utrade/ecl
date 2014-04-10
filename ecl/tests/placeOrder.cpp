/*******************************************************************************
* Date      | Name   | Description                                             *
* 03 Oct 13 | Jovito | Req #1848 : Test Cases For ECL                          *
*******************************************************************************/

#include "../../common/converter.h"
#include "../../common/errorMessages.h"
#include "placeOrder.h"
#include "staticOrder.h"

namespace UT { namespace ECL { namespace TESTS
{
  NewOrders PlaceOrder::pendingNewOrders ;
  ReplaceOrders PlaceOrder::pendingReplaceOrders ;
  CancelOrders PlaceOrder::pendingCancelOrders ;

  ExReportsOfExchanges PlaceOrder::confirmedOrders ;

  void PlaceOrder::DummyOms::fromApp( const FIX::Message& m, 
                                      const FIX::SessionID& )
    throw( FIX::FieldNotFound, 
           FIX::IncorrectDataFormat, 
           FIX::IncorrectTagValue, 
           FIX::UnsupportedMessageType )
    {
#ifndef NDEBUG
      DismantleFix::dismantle( "INBOUND FROM EXCHANGE", m.toString() ) ;
#endif 

      FIX::MsgType lMsgType   ; 
      m.getHeader().getField( lMsgType ) ;

      if( lMsgType == FIX::MsgType_ExecutionReport )
      {
        std::string exchange = m.getField( FIX::FIELD::SecurityExchange ) ;

        DEBUG_1( "Adding execution Report" ) ;

        FIX::OrdStatus lOrdStatus ; m.getField( lOrdStatus ) ;
        FIX::ClOrdID   lClOrdID   ; m.getField( lClOrdID ) ;
        FIX::OrderID   lOrderID   ; m.getField( lOrderID ) ;

        if( lOrdStatus == FIX::OrdStatus_NEW )
        {
          NewOrders::iterator iOrders 
            = PlaceOrder::pendingNewOrders.find( lClOrdID ) ;

          if( iOrders != PlaceOrder::pendingNewOrders.end() )
          {
            {
              FIX42::NewOrderSingle &origOrder = iOrders->second ;

              ExReports &exReports = PlaceOrder::confirmedOrders[exchange] ;
              exReports[ lOrderID ] = m ;
              FIX42::ExecutionReport &exReport = exReports[ lOrderID ] ;

              exReport.setField( FIX::FIELD::OrdType, 
                                 origOrder.getField( FIX::FIELD::OrdType ));
              exReport.setField( FIX::FIELD::Price, 
                                 origOrder.getField( FIX::FIELD::Price )) ;
              exReport.setField( FIX::FIELD::OrderQty, 
                                 origOrder.getField( FIX::FIELD::OrderQty));
              exReport.setField( FIX::FIELD::Symbol, 
                                 origOrder.getField( FIX::FIELD::Symbol ));
              exReport.setField( FIX::FIELD::Side, 
                                 origOrder.getField( FIX::FIELD::Side ));
              exReport.setField( FIX::FIELD::SymbolSfx, 
                  origOrder.getField( FIX::FIELD::SymbolSfx ));
              exReport.setField( FIX::FIELD::SecurityType, 
                  origOrder.getField( FIX::FIELD::SecurityType ));
              exReport.setField( FIX::FIELD::SecurityExchange, 
                  origOrder.getField( FIX::FIELD::SecurityExchange ));
              exReport.setField( FIX::FIELD::ComplianceID, 
                  origOrder.getField( FIX::FIELD::ComplianceID ));
              exReport.setField( FIX::FIELD::TimeInForce, 
                  origOrder.getField( FIX::FIELD::TimeInForce ));
              exReport.setField( FIX::FIELD::OrderQty, 
                  origOrder.getField( FIX::FIELD::OrderQty ));
              exReport.setField( FIX::FIELD::CustomerOrFirm, 
                  origOrder.getField( FIX::FIELD::CustomerOrFirm ));
              // exReport.set( FIX::Account( 
              //     origOrder.getField( FIX::FIELD::Account ) ) ) ;
              // exReport.setField( 5003, origOrder.getField( 5003 ) ) ;
            }

            PlaceOrder::pendingNewOrders.erase( iOrders ) ;
          }
        }
        else if( lOrdStatus == FIX::OrdStatus_REJECTED )
        {
          NewOrders::iterator iOrders 
            = PlaceOrder::pendingNewOrders.find( lClOrdID ) ;

          if( iOrders != PlaceOrder::pendingNewOrders.end() )
          {
            PlaceOrder::pendingNewOrders.erase( iOrders ) ;
          }
        }
        else if( lOrdStatus == FIX::OrdStatus_CANCELED )
        {
          CancelOrders::iterator iOrder
            = PlaceOrder::pendingCancelOrders.find( lClOrdID ) ;

          if( iOrder != PlaceOrder::pendingCancelOrders.end() )
            PlaceOrder::pendingCancelOrders.erase( iOrder ) ;

          ExReports::iterator iReport 
            = confirmedOrders[exchange].find( lOrderID ) ;

          if( iReport != confirmedOrders[exchange].end() )
            confirmedOrders[exchange].erase( iReport ) ;

        }
        else if( lOrdStatus == FIX::OrdStatus_REPLACED )
        {
          ReplaceOrders::iterator iOrder
            = PlaceOrder::pendingReplaceOrders.find( lClOrdID ) ;

          if( iOrder != PlaceOrder::pendingReplaceOrders.end() )
          {
            FIX42::OrderCancelReplaceRequest &origOrder = iOrder->second ;

            ExReports::iterator iReport 
              = confirmedOrders[exchange].find( lOrderID ) ;

            if( iReport != confirmedOrders[exchange].end() )
            {
              FIX42::ExecutionReport &exReport = iReport->second ;

              exReport.setField( FIX::FIELD::ClOrdID, 
                                 origOrder.getField( FIX::FIELD::ClOrdID ) ) ;
              exReport.setField( FIX::FIELD::OrigClOrdID, 
                                 origOrder.getField( FIX::FIELD::OrigClOrdID ));
              exReport.setField( FIX::FIELD::OrderQty, 
                                 origOrder.getField( FIX::FIELD::OrderQty ) ) ;
              
              if( origOrder.isSetField( FIX::FIELD::Price ) )
              {
                exReport.setField( FIX::FIELD::Price, 
                                   origOrder.getField( FIX::FIELD::Price ) ) ;
              }
              // confirmedOrders[exchange].erase( iReport ) ;
            }

            PlaceOrder::pendingReplaceOrders.erase( iOrder ) ;
          }
        }
        else if( lOrdStatus == FIX::OrdStatus_PARTIALLY_FILLED 
            || lOrdStatus == FIX::OrdStatus_FILLED )
        {
          ExReports::iterator iReport 
            = PlaceOrder::confirmedOrders[exchange].find( lOrderID ) ;

          if( iReport != PlaceOrder::confirmedOrders[exchange].end() )
          {
            FIX42::ExecutionReport &exReport = iReport->second ;

            FIX::LastShares lLastShares ;
            m.getField( lLastShares ) ;

            FIX::OrderQty lOrderQty ;
            exReport.get( lOrderQty ) ;

            lOrderQty = lOrderQty - lLastShares ;

            if( lOrderQty == 0 )
            {
              PlaceOrder::confirmedOrders[exchange].erase( iReport ) ;
            }
          }
        }
      }
      else if( lMsgType == FIX::MsgType_OrderCancelReject )
      {
        std::string exchange = m.getField( FIX::FIELD::SecurityExchange ) ;

        FIX::ClOrdID lClOrdID   ; 
        m.getField( lClOrdID ) ;

        FIX::CxlRejResponseTo lCxlRejResponseTo ;
        m.getField( lCxlRejResponseTo ) ;

        if( lCxlRejResponseTo == FIX::CxlRejResponseTo_ORDER_CANCEL_REQUEST )
        {
          CancelOrders::iterator iCancelOrder
            = PlaceOrder::pendingCancelOrders.find( lClOrdID ) ;

          if( iCancelOrder != PlaceOrder::pendingCancelOrders.end() )
            PlaceOrder::pendingCancelOrders.erase( iCancelOrder ) ;
        }
        else
        {
          ReplaceOrders::iterator iReplaceOrder
            = PlaceOrder::pendingReplaceOrders.find( lClOrdID ) ;

          if( iReplaceOrder != PlaceOrder::pendingReplaceOrders.end() )
            PlaceOrder::pendingReplaceOrders.erase( iReplaceOrder ) ;
        }
      }
    }

  void PlaceOrder::DummyOms::toApp( FIX::Message& m, 
                                    const FIX::SessionID& sessionID )
    throw( FIX::DoNotSend )
    {
#ifndef NDEBUG
      DismantleFix::dismantle( "OUTBOUND TO EXCHANGE", m.toString() ) ;
#endif
    }

  PlaceOrder::PlaceOrder( const std::string &omsConfigFile ) 
    : 
    _sessionID( "FIX.4.2", "oms-ecl-utrade", "ecl-utrade" ),
    _settings( omsConfigFile ) ,
    _factory( _settings ),
    _initiator( _dummyOmsApp, _factory, _settings ),
    _clOrdId( 0 )
  {
    _initiator.start();
    FIX::process_sleep( 1 );

    processUserInput();
  }

  PlaceOrder::~PlaceOrder( ) 
  {
    _initiator.stop() ;
    FIX::process_sleep( 1 );
  }

  void PlaceOrder::processUserInput() 
  {
    std::string command( "" ) ;
    while ( command != "0" )
    {
      std::cout
        << "\nOptions are : \n"
        << " 1. Test Nse CM \n"
        << " 2. Test Nse FO \n"
        << " 3. Test Nse CD \n"
        << " 4. Test Bse ED \n"
        << " 5. Test EsmNse \n"
        << " 0. Return To Previous Menu "
        << std::endl;

      getline( std::cin, command ) ;

      if( command == "1" )
      {
        testOrder( "NSECM", StaticOrder::getNseCmOrder() ) ;
      } 
      else if( command == "2" )
      {
        testOrder( "NSEFO", StaticOrder::getNseFoOrder() ) ;
      } 
      else if( command == "3" )
      {
        testOrder( "NSECDS", StaticOrder::getNseCdsOrder() ) ;
      } 
      else if( command == "5" )
      {
        testOrder( "ESMNSE", StaticOrder::getEsmNseOrder() ) ;
      } 
      else if( command == "0" ) {}
      else
      {
        std::cout << "Invalid Option Selected. Choose Again \n " ;
      }
    }
  }

  void PlaceOrder::testOrder( const std::string &exchange, 
                              FIX42::NewOrderSingle order ) 
  {
    std::string command( "" ) ;
    while ( command != "0" )
    {
      std::cout
        << "\nOptions are : \n"
        << " 1. Place New Order on " << exchange << "\n"
        << " 2. Place Replace Order on " << exchange << "\n"
        << " 3. Place Cancel Order on " << exchange << "\n"
        << " 0. Return To Previous Menu "
        << std::endl;

      getline( std::cin, command ) ;

      if( command == "1" )
      {
        order.set( FIX::ClOrdID( UT::IntConverter::convert( ++_clOrdId ) ) ) ;
        FIX::Session::sendToTarget( order, _sessionID );

        pendingNewOrders[ order.getField( FIX::FIELD::ClOrdID ) ] = order ;
      } 
      else if( command == "2" )
      {
        FIX42::ExecutionReport *exReport = selectFromDisplayedOrders( exchange);
        if( exReport != NULL )
        {
          replaceOrder( *exReport ) ;
        }
      } 
      else if( command == "3" )
      {
        FIX42::ExecutionReport *exReport = selectFromDisplayedOrders( exchange);
        if( exReport != NULL )
        {
          cancelOrder( *exReport ) ;
        }
      } 
    }
  }

  FIX42::ExecutionReport *PlaceOrder::selectFromDisplayedOrders( 
      const std::string &exchange ) 
  {
    ExReports &exReports = PlaceOrder::confirmedOrders[exchange] ;

    if( exReports.size() == 0 )
    {
      std::cout << "\n No Orders here " << std::endl ;
      return NULL ;
    }

    std::string positionNumber ;

    FIX::OrdType lOrdType ;

    ExReports::iterator iExReports ;
    while( positionNumber != "0" )
    {
      std::string orderNumbers[ exReports.size() + 1] ;
      int counter = 1 ;

      std::cout << "\n  OrderId \t\t Type \t Price \t Qty " ;

      for( iExReports = exReports.begin() ; 
           iExReports != exReports.end() ; 
           iExReports++ )
      {
        orderNumbers[counter] =
            iExReports->second.getField( FIX::FIELD::OrderID ) ;

        std::cout << "  \n"
          << counter ++ << ". "
          << iExReports->second.getField( FIX::FIELD::OrderID )
          << " \t " << getOrdType( iExReports->second.get( lOrdType ) )
          << " \t " << iExReports->second.getField( FIX::FIELD::Price )
          << " \t " << iExReports->second.getField( FIX::FIELD::OrderQty ) ;
      }
      std::cout << "\n  +++++++++++ 0. Return +++++++++++ " << std::endl ;

      getline( std::cin, positionNumber ) ;
      if( positionNumber != "0" )
      {
        iExReports = exReports.find( orderNumbers[
            UT::IntConverter::toInt( positionNumber ) ] ) ;

        if( iExReports == exReports.end() )
        {
          std::cout << " ====== Unknown Order Number. Try Again " << std::endl ;
        }
        else
        {
          FIX42::ExecutionReport &lExRept = iExReports->second ;
          return &lExRept ;
        }
      }
    }

    return NULL ;
  }

  void PlaceOrder::replaceOrder( FIX42::ExecutionReport &report ) 
  {
    FIX::Side lSide ;
    FIX::OrdType lOrdType ;
    FIX::ClOrdID lClOrdID( UT::IntConverter::convert( ++_clOrdId ) ) ;

    FIX42::OrderCancelReplaceRequest orderReplaceRequest(
        FIX::OrigClOrdID( report.getField( FIX::FIELD::ClOrdID ) ),
        lClOrdID,
        FIX::HandlInst( '1' ),
        FIX::Symbol( report.getField( FIX::FIELD::Symbol ) ),
        report.get( lSide ),
        FIX::TransactTime(),
        report.get( lOrdType ) 
        ) ;

    orderReplaceRequest.set( FIX::OrderID( 
                             report.getField( FIX::FIELD::OrderID ) ) ) ;
    orderReplaceRequest.set( FIX::SecurityID( 
                             report.getField( FIX::FIELD::SecurityID ) ) ) ;
    orderReplaceRequest.set( FIX::SymbolSfx( 
                             report.getField( FIX::FIELD::SymbolSfx ) ) ) ;
    orderReplaceRequest.set( FIX::SecurityType( 
                             report.getField( FIX::FIELD::SecurityType ) ) ) ;
    orderReplaceRequest.set( FIX::SecurityExchange( 
                             report.getField( FIX::FIELD::SecurityExchange ) ));
    orderReplaceRequest.set( FIX::ComplianceID( 
                             report.getField( FIX::FIELD::ComplianceID ) ) ) ;
    orderReplaceRequest.setField( FIX::FIELD::CumQty, 
                                  report.getField( FIX::FIELD::CumQty ) ) ;
    orderReplaceRequest.setField( FIX::FIELD::OrderQty, 
                                  report.getField( FIX::FIELD::OrderQty ) ) ;
    orderReplaceRequest.setField( FIX::FIELD::Price, 
                                  report.getField( FIX::FIELD::Price ) ) ;
    orderReplaceRequest.setField( FIX::FIELD::TimeInForce, 
                                  report.getField( FIX::FIELD::TimeInForce ) ) ;
    orderReplaceRequest.setField( FIX::FIELD::CustomerOrFirm, 
                               report.getField( FIX::FIELD::CustomerOrFirm ) ) ;
    // orderReplaceRequest.set( FIX::Account( 
    //                          report.getField( FIX::FIELD::Account ) ) ) ;
    // orderReplaceRequest.setField( FIX::FIELD::SettlmntTyp, 
    //                             report.getField( FIX::FIELD::SettlmntTyp ) );
    // orderReplaceRequest.setField( FIX::FIELD::MaxFloor, 
    //                            report.getField( FIX::FIELD::MaxFloor ) ) ;
    // orderReplaceRequest.setField( 5003, report.getField( 5003 ) ) ;
    // orderReplaceRequest.setField( 5004, report.getField( 5004 ) ) ;
    // orderReplaceRequest.setField( 5021, report.getField( 5021 ) ) ;
    // orderReplaceRequest.setField( 5022, report.getField( 5022 ) ) ;
    // orderReplaceRequest.setField( 5023, report.getField( 5023 ) ) ;
    // orderReplaceRequest.setField( 5024, report.getField( 5024 ) ) ;

    FIX::Session::sendToTarget( orderReplaceRequest, _sessionID );

    pendingReplaceOrders[ lClOrdID ] = orderReplaceRequest ;
  }

  void PlaceOrder::cancelOrder( FIX42::ExecutionReport &report ) 
  {
    FIX::ClOrdID lClOrdID( UT::IntConverter::convert( ++_clOrdId ) ) ;

    FIX::Side lSide ;

    FIX42::OrderCancelRequest orderCancelRequest( 
        FIX::OrigClOrdID( report.getField( FIX::FIELD::ClOrdID ) ),
        lClOrdID,
        FIX::Symbol( report.getField( FIX::FIELD::Symbol ) ),
        report.get( lSide ),
        FIX::TransactTime() 
        ) ;

    orderCancelRequest.set( FIX::OrderID( 
                            report.getField( FIX::FIELD::OrderID ) ) ) ;
    orderCancelRequest.set( FIX::SecurityID( 
                              report.getField( FIX::FIELD::SecurityID ) ) ) ;
    orderCancelRequest.set( FIX::SymbolSfx( 
                                report.getField( FIX::FIELD::SymbolSfx ) ) ) ;
    orderCancelRequest.set( FIX::SecurityType( 
                            report.getField( FIX::FIELD::SecurityType ) ) ) ;
    orderCancelRequest.set( FIX::SecurityExchange( 
                            report.getField( FIX::FIELD::SecurityExchange ) ) );
    orderCancelRequest.set( FIX::ComplianceID( 
                             report.getField( FIX::FIELD::ComplianceID ) ) ) ;
    orderCancelRequest.setField( FIX::FIELD::OrderQty, 
                                 report.getField( FIX::FIELD::OrderQty ) ) ;
    orderCancelRequest.setField( FIX::FIELD::OrdType, 
                                 report.getField( FIX::FIELD::OrdType ) ) ;
    // orderCancelRequest.set( FIX::Account( 
    //                         report.getField( FIX::FIELD::Account ) ) ) ;
    // orderCancelRequest.setField( 5003, report.getField( 5003 ) ) ;
    // orderCancelRequest.setField( 5021, report.getField( 5021 ) ) ;
    // orderCancelRequest.setField( 5022, report.getField( 5022 ) ) ;

    FIX::Session::sendToTarget( orderCancelRequest, _sessionID );

    pendingCancelOrders[ lClOrdID ] = orderCancelRequest ;
  }

  std::string PlaceOrder::getOrdType( FIX::OrdType &lOrdType ) 
  {
    switch( lOrdType )
    {
      case FIX::OrdType_MARKET :
        return "MARKET" ;
      case FIX::OrdType_LIMIT :
        return "LIMIT" ;
      case FIX::OrdType_STOP :
        return "STOP" ;
      case FIX::OrdType_STOP_LIMIT :
        return "STOP_LIMIT" ;
    }
    return "Unknown Order Type " ;
  }


}}}
