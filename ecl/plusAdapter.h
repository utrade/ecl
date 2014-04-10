#ifndef ECL_PLUS_ADAPTER_H
#define ECL_PLUS_ADAPTER_H

#include "quickfix/MessageCracker.h"

#include "quickfix/fix42/NewOrderSingle.h"
#include "quickfix/fix42/OrderCancelRequest.h"
#include "quickfix/fix42/OrderCancelReplaceRequest.h"
#include "quickfix/fix42/ExecutionReport.h"

#include "quickfix/fix44/ExecutionReport.h"
#include "quickfix/fix44/OrderCancelReject.h"
#include "quickfix/fix44/OrderCancelReplaceRequest.h"
#include "quickfix/fix44/BusinessMessageReject.h"
#include "quickfix/fix44/News.h"

namespace UT { namespace ECL
{
  class PlusAdapter
      : public FIX::Application, 
        public FIX::MessageCracker
  {

    public :
      /**
       * @brief Get an instance of OmsHandler.
       *   This class is a singleton. The reason its a singleton is because,
       * OmsHandler has to send to the adaptors i.e. access an object of 
       * the adapter while the Adaptor has to send to OMS i.e. access 
       * the object of OmsHandler. To solve this cyclic reference,
       * we will make both the Adaptors & OmsHandler into singleton.
       * @return Reference of an object of OmsHandler
       */
      static PlusAdapter &getInstance() ;

      /**
       * @brief init the configuration using the fix setting file.
       * We will pick up the source & destination from this file.
       * @param Fix Session Settings file.
       */
      bool reset( const FIX::SessionSettings &settings ) ;

    public :
      /**
       * @brief Read the settings and save the destinations.
       * @param Settings that are to be read.
       * @return true if we were able to find the settings.
       *         false if missing or exceptions.
       */
      bool fetchDestinations( const FIX::SessionSettings &settings ) ;

      /**
       * @brief onCreate overload of QuickFix.
       * @param SessionID of session we are creating.
       */
      void onCreate( const FIX::SessionID& ) {}

      /**
       * @brief onLogon overload of QuickFix recieved when we have successfully
       *   logged on.
       * @param SessionID that was logged on.
       */
      void onLogon( const FIX::SessionID& sessionID ) {}

      /**
       * @brief onLogout overload of QuifixFix received when we have 
       *  successfully logged out.
       * @param SessionID that was logged out.
       */
      void onLogout( const FIX::SessionID& sessionID ) {}

      /**
       * @brief toAdmin overload of QuickFix if we wish to modify an admin
       *   message before we send it.
       * @param Message that is being sent.
       * @param SessionID to which we are going to send the message.
       * @return  
       */
      void toAdmin( FIX::Message&, const FIX::SessionID& ) {}

      /**
       * @brief toAdmin overload of QuickFix if we wish to modify normal
       *   messages before we send it.
       * @param Message that is being sent.
       * @param SessionID to which we are going to send the message.
       * @return  
       */
      void toApp( FIX::Message&, const FIX::SessionID& )
        throw( FIX::DoNotSend ) ;

      /**
       * @brief fromAdmin overload is called when we receive an admin message.
       * @param Message that was received.
       * @param SessionID on which the message was received.
       * @return  
       */
      void fromAdmin( const FIX::Message&, const FIX::SessionID& )
        throw( FIX::FieldNotFound, 
               FIX::IncorrectDataFormat, 
               FIX::IncorrectTagValue, 
               FIX::RejectLogon ) 
        {}

      /**
       * @brief fromApp overload is called when we receive a normal message.
       * @param Message that was received.
       * @param SessionID on which the message was received.
       * @return  
       */
      void fromApp( const FIX::Message& message, 
                    const FIX::SessionID& sessionID )
        throw( FIX::FieldNotFound, 
            FIX::IncorrectDataFormat, 
            FIX::IncorrectTagValue, 
            FIX::UnsupportedMessageType ); 

      /**
       * @brief convert a FIX42 NewOrderSingle to a FIX44 NewOrderSingle 
       *    and send it to the exchange.
       * @param Order you wish to convert and send.
       * @return true if message was sent.
       *         false otherwise.
       */
      bool send( const FIX42::NewOrderSingle &message ) ;

      /**
       * @brief convert a FIX42 OrderCancelRequest to a FIX44 NewOrderSingle 
       *    and send it to the exchange.
       * @param Order you wish to convert and send.
       * @return true if message was sent.
       *         false otherwise.
       */
      bool send( const FIX42::OrderCancelRequest &message ) ;

      /**
       * @brief convert a FIX42 OrderCancelReplaceRequest to a FIX44 
       *   NewOrderSingle and send it to the exchange.
       * @param Order you wish to convert and send.
       * @return true if message was sent.
       *         false otherwise.
       */
      bool send( const FIX42::OrderCancelReplaceRequest &message ) ;

      /**
       * @brief onMessage overload called by quickfix when we receive an
       *   execution report.
       * @param ExecutionReport that was received.
       * @param SessionID on which we received the execution report.
       */
      void onMessage( const FIX44::ExecutionReport&, const FIX::SessionID& );

      /**
       * @brief onMessage overload called by quickfix when we receive an
       *   order cancel reject.
       * @param Order cancel reject that was received.
       * @param SessionID on which we received the execution report.
       */
      void onMessage( const FIX44::OrderCancelReject&, const FIX::SessionID& );

      /**
       * @brief onMessage overload called by quickfix when we receive a news.
       * @param News that was received.
       * @param SessionID on which we received the execution report.
       */
      void onMessage( const FIX44::News &, const FIX::SessionID& );

      /**
       * @brief onMessage overload called by quickfix when we receive a 
       *   business message reject.
       * @param BusinessMessageReject that was received.
       * @param SessionID on which we received the execution report.
       */
      void onMessage( const FIX44::BusinessMessageReject &,  
                      const FIX::SessionID& );

    private :
      /**
       * @brief The Session ID of this connection.
       * For now we have assumed that we will have only 1 session ID.
       * This has to modified to hold multiple session ids in the future.
       */
      FIX::SessionID _sessionId ;

    private :
      // Members to make it a singleton

      /**
       * @brief Default constructor.
       * The constructor is private so that no one can create an object
       * of this singleton.
       */
      PlusAdapter() ;

      /**
       * @brief Copy constructor.
       * The copy contructor is private so that we cannot copy this singleton.
       */
      PlusAdapter( const PlusAdapter& ) ;

      /**
       * @brief Assignment operator
       * The assignment operator is private so that we cannot copy this 
       *   singleton.
       */
      PlusAdapter & operator = ( const PlusAdapter & ) ;

      /**
       * The single instance of the singleton that will be running.
       */
      static PlusAdapter *_instance ;
      static boost::mutex _mutexOnInstance ;
  };
}}

#endif // ECL_PLUS_ADAPTER_H
