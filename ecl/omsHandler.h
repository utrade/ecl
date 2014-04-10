#ifndef UT_ECL_OMS_HANDLER_H
#define UT_ECL_OMS_HANDLER_H

#include "../common/threadPool.h"

#include <quickfix/Application.h>
#include <quickfix/MessageCracker.h>

namespace UT { namespace ECL
{
  class OmsHandler
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
      static OmsHandler &getInstance() ;

      /**
       * @brief Send a FIX42 Message to Oms.
       *   When we receive a confirmation from the exchange,
       * the adaptor will convert it into the required format
       * and we will send it to OMS.
       * @param The message that needs to be sent to OMS.
       */
      void sendToOms( FIX42::Message &message ) ;

      /**
       * @brief Re-init the configuration using the fix setting file.
       * We will pick up the oms & ecl destination from this file.
       * @param Fix Session Settings file.
       */
      bool reset( const FIX::SessionSettings &settings ) ;

    private :
      /**
       * Find the exchange for whom the message is and call the 
       * send function of that exchange.
       * @param Message that has to be sent.
       */
      template< class Message >
        void send( const Message &message ) ;

    private :
      // OVERLOADS

      /**
       * @brief onCreate is called when a new session is created.
       * @param Session id.
       */
      void onCreate( const FIX::SessionID& ) {}

      /**
       * @brief OnLogon message received from QuickFix after we
       *   have successfully logged in.
       * @param The session we are logged on with.
       */
      void onLogon( const FIX::SessionID& sessionID ) ;

      /**
       * @brief OnLogout message received from QuickFix after we
       *   have successfully logged out.
       * @param The session id which logged out.
       */
      void onLogout( const FIX::SessionID& sessionID ) ;

      /**
       * @brief toAdmin function called by QuickFix.
       *   Allows us to modify an admin message e.g. Logon, Logout
       * before it is actually sent to the destination.
       * @param The actual message that is begin sent.
       * @param The session id to which we are going to send the message.
       */
      void toAdmin( FIX::Message&, const FIX::SessionID& ) {}

      /**
       * @brief We have received an admin message.
       * @param Message we have received.
       * @param Session Id on which we have received the message.
       */
      void fromAdmin( const FIX::Message&, const FIX::SessionID& )
        throw( FIX::FieldNotFound, 
               FIX::IncorrectDataFormat, 
               FIX::IncorrectTagValue, 
               FIX::RejectLogon ) 
        {}

      /**
       * @brief toApp function called by QuickFix.
       *   Allows us to modify an normal message 
       *    e.g. NewOrderSingle, OrderCancelRequest
       * before it is actually sent to the destination.
       * @param The actual message that is begin sent.
       * @param The session id to which we are going to send the message.
       */
      void toApp( FIX::Message&, const FIX::SessionID& )
        throw( FIX::DoNotSend ) ;

      /**
       * @brief We have received a message.
       * @param Message we have received.
       * @param Session Id on which we have received the message.
       */
      void fromApp( const FIX::Message& message, 
                    const FIX::SessionID& sessionID )
        throw( FIX::FieldNotFound, 
               FIX::IncorrectDataFormat, 
               FIX::IncorrectTagValue, 
               FIX::UnsupportedMessageType ); 

      // MessageCracker overloads
      /**
       * @brief We have received a NewOrderSingle message.
       * @param The actual message
       * @param The SessionId from which we received the message.
       */
      void onMessage ( const FIX42::NewOrderSingle&, const FIX::SessionID& );

      /**
       * @brief We have received a NewOrderList message.
       * @param The actual message
       * @param The SessionId from which we received the message.
       */
      void onMessage ( const FIX42::NewOrderList&, const FIX::SessionID& );

      /**
       * @brief We have received a OrderCancelRequest message.
       * @param The actual message
       * @param The SessionId from which we received the message.
       */
      void onMessage ( const FIX42::OrderCancelRequest&,  
                       const FIX::SessionID& );

      /**
       * @brief We have received a OrderCancelReplaceRequest message.
       * @param The actual message
       * @param The SessionId from which we received the message.
       */
      void onMessage ( const FIX42::OrderCancelReplaceRequest&, 
                       const FIX::SessionID& );

      /**
       * @brief We have received a OrderCancelReject message.
       * @param The actual message
       * @param The SessionId from which we received the message.
       */
      void onMessage ( const FIX42::OrderCancelReject&, const FIX::SessionID& );

      /**
       * @brief Reject a message received from OMS.
       * @param ClOrdId of the message we are gonna reject.
       * @param MsgSeqNum of the message. 
       * @param Original MsgType.
       * @param TagNumber which was invalid
       * @param The reason for rejection as an integer.
       * @param The rejection text.
       */
      void sendReject( 
          const std::string &clOrdId,
          const FIX::MsgSeqNum &msgSeqNum,
          const std::string &msgType,
          const int tagNum ,
          const int rejectReason,
          const std::string &rejectReasonTxt
          );

      /**
       * @brief Reject a new order from Oms.
       * A new order was received from Oms but failed validations.
       *  Send an Exectuion Report with status Reject and its reason.
       * @param The Order that was received.
       * @param The error number. 
       * @param The text explaining the error. 
       */
      void rejectOrder( 
          const FIX42::NewOrderSingle &newOrderSingle,
          int errorNo,
          const std::string &errorText 
          ) ;

      /**
       * @brief Reject a cancel order from Oms.
       * A cancel order was received from Oms but failed validations.
       *  Send an Order Cancel Reject with its reason.
       * @param The Order that was received.
       * @param The error number. 
       * @param The text explaining the error. 
       */
      void rejectOrder( 
          const FIX42::OrderCancelRequest &cancelOrder,
          int errorNo,
          const std::string &errorText 
          ) ;

      /**
       * @brief Reject a replace order from Oms.
       * A replace order was received from Oms but failed validations.
       *  Send an Order Cancel Reject with its reason.
       * @param The Order that was received.
       * @param The error number. 
       * @param The text explaining the error. 
       */
      void rejectOrder( 
          const FIX42::OrderCancelReplaceRequest &replaceOrder,
          int errorNo,
          const std::string &errorText ) ;

    private :
      // Members to make it a singleton

      /**
       * @brief Default constructor.
       * The constructor is private so that no one can create an object
       * of this singleton.
       */
      OmsHandler() ;

      /**
       * @brief Copy constructor.
       * The copy contructor is private so that we cannot copy this singleton.
       */
      OmsHandler( const OmsHandler& ) ;

      /**
       * @brief Assignment operator
       * The assignment operator is private so that we cannot copy this 
       *   singleton.
       */
      OmsHandler & operator = ( const OmsHandler & ) ;

      /**
       * The single instance of the singleton that will be running.
       */
      static OmsHandler *_instance ;
      static boost::mutex _mutexOnInstance ;

    private :
      /**
       * @brief Fetch the eclTargetCompId & omsTargetCompId from the settings
       * @param The Settings to read.
       * @return true if we were able to find the values.
       *         false if there is no acceptor session or if there was an issue.
       */
      bool fetchOmsDestination( const FIX::SessionSettings &settings ) ;

      /**
       * @brief Call the crackMessage of MessageCracker.
       *   Boost Bind cannot call the crack() message of MessageCracker.
       *   Hence, we have added our own in its place.
       * @param The Message to be cracked.
       * @param The SessionID from which the message was received.
       * @return  
       */
      inline void crackMessage( 
          const FIX::Message& message, 
          const FIX::SessionID& sessionID )
      {
        crack( message, sessionID ); 
      }

    private :
      UT::ThreadPool _threadPool ;

      FIX::SenderCompID _eclCompId ;
      FIX::TargetCompID _omsCompId ;
  };
}}
#endif // UT_ECL_OMS_HANDLER_H
