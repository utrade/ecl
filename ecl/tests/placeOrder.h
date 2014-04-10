/*******************************************************************************
* Date      | Name   | Description                                             *
* 03 Oct 13 | Jovito | Req #1848 : Test Cases For ECL                          *
*******************************************************************************/

#ifndef UT_ECL_TEST_PLACE_ORDER
#define UT_ECL_TEST_PLACE_ORDER

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
#include <quickfix/fix42/OrderCancelRequest.h>
#include <quickfix/fix42/OrderCancelReplaceRequest.h>
#include <quickfix/fix42/ExecutionReport.h>
#include <quickfix/fix42/QuoteRequest.h>

#include <boost/unordered_map.hpp>

#include "../../common/dismantleFix.h"

#include "report.h"

namespace UT { namespace ECL { namespace TESTS
{
  typedef 
    boost::unordered_map<std::string, FIX42::NewOrderSingle > NewOrders ;

  typedef 
    boost::unordered_map<std::string, FIX42::OrderCancelReplaceRequest > 
      ReplaceOrders ;

  typedef 
    boost::unordered_map<std::string, FIX42::OrderCancelRequest > CancelOrders ;

  typedef 
    boost::unordered_map<std::string, FIX42::ExecutionReport > ExReports ;

  typedef boost::unordered_map< std::string, ExReports > 
    ExReportsOfExchanges ;

  class PlaceOrder
  {
    /**
     * @brief Dummy Oms only places orders on the exchange.
     */
    class DummyOms : public FIX::NullApplication
    {
      public:
        /**
         * @brief Default constructor sets the count of orders to 0.
         */
      DummyOms() : m_count(0) {}

      /**
       * @brief Received a message from the application.
       * When we receive 
       * NewOrderConfirmation -> Fetch order from pending order list and 
       *                                 update it.
       * ReplaceConfirmation -> Fetch order from pending replace list and 
       *                                 update it.
       * CancelConfirmation -> Cancel Order from pending list.
       * @param Fix Message that was received.
       * @param Session Id on which we received the message.
       */
      void fromApp( const FIX::Message& m, const FIX::SessionID& ) 
        throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, 
               FIX::IncorrectTagValue, FIX::UnsupportedMessageType ) ;

      /**
       * @brief Any changes to be done before we send a message to the exchange?
       */
      void toApp( FIX::Message& m, const FIX::SessionID& sessionID ) 
        throw( FIX::DoNotSend ) ;

      private:
      /**
       * @brief Count of number of requests that were sent.
       */
      int m_count;
    };

    public :
    /**
     * @brief Default constructor.
     * @param The config file to be used by the fix initiator.
     */
      PlaceOrder( const std::string &omsConfigFile ) ;

      /**
       * @brief Destructor to clean up objects.
       */
      ~PlaceOrder() ;

      /**
       * @brief Handle use input.
       * Take input from the user and call the appropriate function.
       */
      void processUserInput() ;

    public :
      /**
       * @brief A collection of NewOrderSingles that were sent to the exchange.
       * This collection is used to manage the order book when we receive an
       *  execution report.
       */
      static NewOrders pendingNewOrders ;

      /**
       * @brief A collection of OrderCancelReplaceRequest that were 
       *  sent to the exchange.  This collection is used to manage the 
       *  order book when we receive an execution report.
       */
      static ReplaceOrders pendingReplaceOrders ;

      /**
       * @brief A collection of OrderCancelReplaceRequest that were 
       *  sent to the exchange.  This collection is used to manage the 
       *  order book when we receive an execution report.
       */
      static CancelOrders pendingCancelOrders ;

      /**
       * @brief A collection of execution reports that were sent to the 
       *    exchange.
       * This collection is used to manage the order book when we send a 
       *  cancel or replace.
       */
      static ExReportsOfExchanges confirmedOrders ;

    private :
      /**
       * @brief The dummy OMS application that will send and receive 
       *   orders towards the exchange.
       */
      DummyOms _dummyOmsApp ;

      /**
       * @brief The sessionId used to identify the connection between
       *  ecl & the above dummy oms.
       */
      FIX::SessionID _sessionID ;

      /**
       * @brief The settings file used to configure the dummy oms and
       *   connect to ecl.
       */
      FIX::SessionSettings _settings ;

      /**
       * @brief The File path where the logs will be stored.
       */
      FIX::FileStoreFactory _factory ;

      /**
       * @brief The initiator which does the actual connection and sending of 
       *   messages.
       */
      FIX::ThreadedSocketInitiator _initiator ;

      /**
       * @brief Display a report with timestamp etc.
       */
      UT::Report _report ;

      /**
       * @brief Allow the user to place a New, Replace Or Cancel Order.
       * Accepts input from the user and calls the appropriate function.
       * @param The exchange on which we are going to place the order.
       * @param The actual order which we are going to place.
       */
      void testOrder( const std::string &exchange, FIX42::NewOrderSingle order);

      /**
       * Displays the list of orders from the collection of execution reports.
       * A user can select an order to either cancel or replace.
       * @param Exchange whose list we are about to display.
       * @param The MsgType identifying if its a Cancel or Replace.
       * @return  
       */
      FIX42::ExecutionReport *selectFromDisplayedOrders( 
          const std::string &exchange ) ;

      /**
       * @brief Send a replace order to the exchange generated from the
       *   execution report.
       * @param The Execution Report from which the order is generated.
       */
      void replaceOrder( FIX42::ExecutionReport &report ) ;

      /**
       * @brief Send a replace order to the exchange generated from the
       *   execution report.
       * @param The Execution Report from which the order is generated.
       */
      void cancelOrder( FIX42::ExecutionReport &report ) ;

      /**
       * @brief Get the Type of Order as text.
       */
      std::string getOrdType( FIX::OrdType &lOrdType ) ;

      /**
       * Current ClOrdID.
       */
      uint64_t _clOrdId ;
  };
}}}

#endif // UT_ECL_TEST_PLACE_ORDER

