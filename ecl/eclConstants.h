#ifndef UT_ECL_CONSTANTS_H
#define UT_ECL_CONSTANTS_H

#include "../common/constants.h"
#include "../common/errorlog.h"
#include <quickfix/FixFields.h>

#ifndef WIN32
#include <sys/time.h>
#endif

#include "../common/types.h"

namespace UT 
{
  const char ExecType_NSE_STOP_LOSS_TRIGGERED = 'T' ;

  const char ESM_NSE_SFX[] = "EQ" ;

  const char ID_SOURCE_MAREX[] = "101" ;

  const char HOST[] = "host" ;
  const char DBNAME[] = "dbname" ;
  const char USER[] = "user" ;

  const char ORD_STATUS_UPDATED = '8' ; // 8 - Rejected

  const char DUMMY_STR[] = "0" ;
  const char DUMMY_NUM = 0 ;
  //#define SYMBOL_DUMMY DUMMY_STR
  const FIX::Symbol SYMBOL_DUMMY( DUMMY_STR ) ;
  const FIX::OrigClOrdID ORIG_CL_ORD_ID_DUMMY( DUMMY_STR ) ;
  const FIX::OrderID ORDER_ID_DUMMY( DUMMY_STR ) ;
  const FIX::CumQty CUM_QTY_DUMMY( DUMMY_NUM ) ;
  const FIX::LeavesQty LEAVES_QTY_DUMMY( DUMMY_NUM ) ;

  namespace SIZE {
    const int BRANCH_ID = 3 ;
  }

  namespace POS {
    const int BRANCH_ID = 6 ;
  }

  const int ERRORCODE_EXCHANGE_NOT_CONNECTED = 1 ;
  const char STR_ERRORCODE_EXCHANGE_NOT_CONNECTED[] 
    = "Not connected to exchange " ;
}

const int BusinessRejectReason_INVALID_PRICE_INCREMENT_PLUS = 16 ;

// #define ORIG_CL_ORD_ID_DUMMY DUMMY_STR
#define CUM_QTY_DUMMY DUMMY_NUM
#define LEAVES_QTY_DUMMY DUMMY_NUM
#define AVG_PRICE_DUMMY DUMMY_NUM

#define ECL_MESSAGE_LEVEL 4
#define ECL_MODULE_ID "ECL"
#define OMS_TO_ECL_MESSAGE "Order from OMS"
#define BSE_TO_ECL_MESSAGE "Order from BSE"

#ifdef NDEBUG
  #define ECL_ORDER_LOG_FROM_OMS(ORDSTATUS) ;
  #define ECL_ORDER_LOG_FROM_BSE(STATUS) ;
  #define PRINT_TIME(A,B) ;
#else

  #define ECL_ORDER_LOG_FROM_OMS( ORDSTATUS ) \
    ORDER_LOG(ECL_MODULE_ID, \
              IntConverter::toLong( message.getField(FIX::FIELD::ClOrdID) ), \
              ORDSTATUS, \
              OMS_TO_ECL_MESSAGE ); \
  
  #define ECL_ORDER_LOG_FROM_BSE( STATUS ) \
    ORDER_LOG(ECL_MODULE_ID, \
              ombMessage.getClOrdId(), \
              STATUS, \
              BSE_TO_ECL_MESSAGE ); 
  
  #if WIN32
    #define PRINT_TIME( MSG, CLORDID ) {}
  #else
  
  #define PRINT_TIME( MSG, CLORDID ) \
    timeval currTime ; \
    gettimeofday( &currTime, NULL ); \
    std::cout << MSG << " ClOrdId " << CLORDID \
       << " at " << currTime.tv_sec << "." << currTime.tv_usec << std::endl ;
#endif
#endif

#endif
