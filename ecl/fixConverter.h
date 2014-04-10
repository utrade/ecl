#ifndef UT_ECL_FIX_CONVERTER_H
#define UT_ECL_FIX_CONVERTER_H

#include <quickfix/MessageCracker.h>

namespace UT
{
  class FixConverter
  {
    public :
      /**
       * @brief Convert From a FIX42 NewOrderSingle to FIX44 NewOrderSingle.
       * @param FIX42 NewOrderSingle to be converted
       * @return FIX44 NewOrderSingle
       */
      static FIX44::NewOrderSingle toFix44( 
          const FIX42::NewOrderSingle &message ) ;

      /**
       * @brief Convert From a FIX42 OrderCancelRequest to FIX44 
       *    OrderCancelRequest.
       * @param FIX42 OrderCancelRequest to be converted
       * @return FIX44 OrderCancelRequest
       */
      static FIX44::OrderCancelRequest toFix44( 
          const FIX42::OrderCancelRequest &message ) ;

      /**
       * @brief Convert From a FIX42 OrderCancelReplaceRequest to FIX44 
       *    OrderCancelReplaceRequest.
       * @param FIX42 OrderCancelReplaceRequest to be converted
       * @return FIX44 OrderCancelReplaceRequest
       */
      static FIX44::OrderCancelReplaceRequest toFix44( 
          const FIX42::OrderCancelReplaceRequest &message ) ;

      /**
       * @brief Convert From a FIX44 ExecutionReport to FIX42 ExecutionReport.
       * @param FIX44 ExecutionReport to be converted
       * @return FIX42 ExecutionReport
       */
      static FIX42::ExecutionReport toFix42( 
          const FIX44::ExecutionReport &message ) ;

      /**
       * @brief Convert From a FIX44 OrderCancelReject to FIX42 
       *    OrderCancelReject.
       * @param FIX44 OrderCancelReject to be converted
       * @return FIX42 OrderCancelReject
       */
      static FIX42::OrderCancelReject toFix42( 
          const FIX44::OrderCancelReject &message ) ;

      /**
       * @brief Convert From a FIX44 BusinessMessageReject to FIX42 
       *    BusinessMessageReject.
       * @param FIX44 BusinessMessageReject to be converted
       * @return FIX42 BusinessMessageReject
       */
      static FIX42::BusinessMessageReject toFix42( 
          const FIX44::BusinessMessageReject &message ) ;
  };
 
}
#endif // UT_ECL_FIX_CONVERTER_H
