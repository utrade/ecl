/*******************************************************************************
* Date      | Author | Notes                                                   *
* 18 Nov 13 | Jovito | Task #1979 : DATAFEEDER LAYER FOR MONEYUTRADE AND UTRADE*
* 10 Jan 14 | Jovito | Task #XXXX : Added error messages in UdpReceiver and    *
*                                   Modified errorlog.h build for windows.     *
*******************************************************************************/
#ifndef ERROR_LOG_H
#define ERROR_LOG_H

// DISABLE DEBUG BUILD
// #define NDEBUG

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <boost/format.hpp>
#ifndef _MSC_VER
  #include <sys/time.h>
#endif

#define NORDERLOG

#include "logger.h"

#ifndef _MSC_VER
  #include "../config.h"
#endif

#define DEFINE_MSG_HEADER(err_mnemonic)                                        \
  namespace ut {                                                               \
    namespace message {                                                        \
      extern int  __ERRNUM_ ## err_mnemonic;                                   \
      extern std::string __ERRTXT_ ## err_mnemonic;                            \
    }                                                                          \
  }


#define DEFINE_MSG(err_num,err_mnemonic,err_text)                              \
  namespace ut {                                                               \
    namespace message {                                                        \
  int  __ERRNUM_ ## err_mnemonic = err_num;                                    \
  std::string __ERRTXT_ ## err_mnemonic = err_text;                            \
    }                                                                          \
  }

///////////////////////////////////////////
// environment variable, which should be //
// used to identify debug level          //
///////////////////////////////////////////

#define ENV_DEBUG_LEVEL "DEBUG_LEVEL"

//////////////////////////
// debugging levels     //
// 1 = Fatal (FATAL)    //
// 2 = + Error (ERROR)  //
// 3 = + Warning (WARN) //
// 4 = + Info (INFO)    //
//////////////////////////

#define FATAL_LEVEL 1
#define ERROR_LEVEL 2
#define WARN_LEVEL  3
#define INFO_LEVEL  4

//////////////////////////////////////////
// get debug level from the environment //
//////////////////////////////////////////

int getDebugLevel() ;

std::string getCurrentTime() ;

#define __BEGIN_MSG__(level,err_mnemonic)                                      \
  std::cerr << getCurrentTime() << " : "                                       \
  << #level << ": "                                                            \
  << ut::message::__ERRNUM_ ## err_mnemonic                                    \
  << ": ";

#define MSG_LEVEL_0(level,err_mnemonic) {                                      \
    if (getDebugLevel() >= level ## _LEVEL) {                                  \
      __BEGIN_MSG__(level,err_mnemonic);                                       \
      std::cerr << ut::message::__ERRTXT_ ## err_mnemonic                      \
                << std::endl;                                                  \
    }                                                                          \
  }

#define MSG_LEVEL_1(level,err_mnemonic,param1) {                               \
    if (getDebugLevel() >= level ## _LEVEL) {                                  \
      __BEGIN_MSG__(level,err_mnemonic);                                       \
      std::cerr << boost::format(ut::message::__ERRTXT_ ## err_mnemonic)       \
        % param1                                                               \
                << std::endl;                                                  \
    }                                                                          \
  }

#define MSG_LEVEL_2(level,err_mnemonic,param1,param2) {                        \
                          if (getDebugLevel() >=level ## _LEVEL) {             \
      __BEGIN_MSG__(level,err_mnemonic);                                       \
      std::cerr << boost::format(ut::message::__ERRTXT_ ## err_mnemonic)       \
        % param1                                                               \
        % param2                                                               \
                << std::endl;                                                  \
    }                                                                          \
  }

#define MSG_LEVEL_3(level,err_mnemonic,param1,param2,param3) {                 \
    if (getDebugLevel() >= level ## _LEVEL) {                                  \
      __BEGIN_MSG__(level,err_mnemonic);                                       \
      std::cerr << boost::format(ut::message::__ERRTXT_ ## err_mnemonic)       \
        % param1                                                               \
        % param2                                                               \
        % param3                                                               \
                << std::endl;                                                  \
    }                                                                          \
  }

#define MSG_LEVEL_4(level,err_mnemonic,param1,param2,param3,param4) {          \
    if (getDebugLevel() >= level ## _LEVEL) {                                  \
      __BEGIN_MSG__(level,err_mnemonic);                                       \
      std::cerr << boost::format(ut::message::__ERRTXT_ ## err_mnemonic)       \
        % param1                                                               \
        % param2                                                               \
        % param3                                                               \
        % param4                                                               \
                << std::endl;                                                  \
    }                                                                          \
  }

#define INFO_0(err_mnemonic) MSG_LEVEL_0(INFO,err_mnemonic)
#define INFO_1(err_mnemonic,param1) MSG_LEVEL_1(INFO,err_mnemonic,param1)
#define INFO_2(err_mnemonic,param1,param2)                                     \
  MSG_LEVEL_2(INFO,err_mnemonic,param1,param2)
#define INFO_3(err_mnemonic,param1,param2,param3)                              \
  MSG_LEVEL_3(INFO,err_mnemonic,param1,param2,param3)

#define WARN_0(err_mnemonic) MSG_LEVEL_0(WARN,err_mnemonic)
#define WARN_1(err_mnemonic,param1) MSG_LEVEL_1(WARN,err_mnemonic,param1)
#define WARN_2(err_mnemonic,param1,param2)                                     \
  MSG_LEVEL_2(WARN,err_mnemonic, param1, param2)
#define WARN_3(err_mnemonic,param1,param2,param3)                              \
  MSG_LEVEL_3(WARN,err_mnemonic,param1,param2,param3)

#define ERROR_0(err_mnemonic) MSG_LEVEL_0(ERROR,err_mnemonic)
#define ERROR_1(err_mnemonic,param1) MSG_LEVEL_1(ERROR,err_mnemonic,param1)
#define ERROR_2(err_mnemonic,param1,param2)                                    \
  MSG_LEVEL_2(ERROR,err_mnemonic, param1, param2)
#define ERROR_3(err_mnemonic,param1,param2,param3)                             \
  MSG_LEVEL_3(ERROR,err_mnemonic,param1,param2,param3)
#define ERROR_4(err_mnemonic,param1,param2,param3,param4)                      \
  MSG_LEVEL_4(ERROR,err_mnemonic,param1,param2,param3,param4)

#define FATAL_0(err_mnemonic) MSG_LEVEL_0(FATAL,err_mnemonic)
#define FATAL_1(err_mnemonic,param1) MSG_LEVEL_1(FATAL,err_mnemonic,param1)
#define FATAL_2(err_mnemonic,param1,param2)                                    \
  MSG_LEVEL_2(FATAL,err_mnemonic,param1,param2)
#define FATAL_3(err_mnemonic,param1,param2,param3)                             \
  MSG_LEVEL_3(FATAL,err_mnemonic,param1,param2,param3)

#define TS_LENGTH 26

#ifdef LOG_TIMESTAMP
#define _PRINT_TIMESTAMP                                                       \
 {                                                                             \
 char timestamp[TS_LENGTH];                                                    \
 time_t curTime = time(0);                                                     \
 ctime_r(&curTime, &(timestamp[0]));                                           \
 timestamp[TS_LENGTH - 2] = 0;                                                 \
 memmove(&(timestamp[0]), &(timestamp[0]) + 4, TS_LENGTH - 4);                 \
 std::cout << timestamp << " ";                                                \
 }
#else
#define _PRINT_TIMESTAMP {}
#endif

#ifndef NDEBUG
#define DEBUG_1(arg1) {                                                        \
    _PRINT_TIMESTAMP;                                                          \
    std::cout << "DEBUG: "                                                     \
              << "(" << __FILE__ << ":" << __LINE__ << "): "                   \
              << arg1                                                          \
              << std::endl;                                                    \
    fflush(stdout);                                                            \
}
#define DEBUG_2(arg1, arg2) {                                                  \
    _PRINT_TIMESTAMP;                                                          \
    std::cout << "DEBUG: "                                                     \
              << "(" << __FILE__ << ":" << __LINE__ << "): "                   \
              << arg1 << arg2                                                  \
              << std::endl;                                                    \
    fflush(stdout);                                                            \
}
#define DEBUG_3(arg1, arg2, arg3) {                                            \
    _PRINT_TIMESTAMP;                                                          \
    std::cout << "DEBUG: "                                                     \
              << "(" << __FILE__ << ":" << __LINE__ << "): "                   \
              << arg1 << arg2 << arg3                                          \
              << std::endl;                                                    \
    fflush(stdout);                                                            \
}
#define DEBUG_4(arg1, arg2, arg3, arg4) {                                      \
    _PRINT_TIMESTAMP;                                                          \
    std::cout << "DEBUG: "                                                     \
              << "(" << __FILE__ << ":" << __LINE__ << "): "                   \
              << arg1 << arg2 << arg3 << arg4                                  \
              << std::endl;                                                    \
    fflush(stdout);                                                            \
}

#else
#define DEBUG_1(arg1) {                                                        \
}
#define DEBUG_2(arg1, arg2) {                                                  \
}
#define DEBUG_3(arg1, arg2, arg3) {                                            \
}
#define DEBUG_3(arg1, arg2, arg3) {                                            \
}
#define DEBUG_4(arg1, arg2, arg3, arg4) {}
#endif

const std::string SQL_CREATE_ORDER_LOG = 
  "INSERT INTO order_logs ("
  "id, module_id, order_timestamp, order_id, status, text) "
  " values (:unsignedId, :moduleId, now(), :unsignedOrderId, :status, :text)";

#ifndef _MSC_VER

#define STD_EXCEPTION_MESSAGE { std::cerr                                      \
    <<"EXCEPTION occured at "                                                  \
    << "(" __FILE__ << ":" << __LINE__ << ":"                                  \
    << __PRETTY_FUNCTION__ << ") \n"                                           \
    << "    what():" << e.what()                                               \
    << std::endl; }

#else

#define STD_EXCEPTION_MESSAGE { std::cerr                                      \
    <<"EXCEPTION occured at "                                                  \
    << "(" __FILE__ << ":" << __LINE__ << ":"                                  \
    << "    what():" << e.what()                                               \
    << std::endl; }


#endif


#ifndef NORDERLOG

#ifdef USE_SYSLOG
#define ORDER_LOG(moduleId, orderId, status, text) {                           \
   OrderLog::getInstance()->log(moduleId, orderId, status, text);              \
 }
#else
#define ORDER_LOG(moduleId, orderId, status, text) {                           \
 soci::session sql(ConnectionPool::get());                                     \
  long long id = 0;                                                            \
  try {                                                                        \
    sql << "SELECT nextval('order_logs_seq')",                                 \
     into(id);                                                                 \
  }                                                                            \
  catch(const soci::soci_error& e)                                             \
  {                                                                            \
    std::cerr << "DB Exception occured :"                                      \
              << e.what()                                                      \
              << std::endl;                                                    \
    throw;                                                                     \
  }                                                                            \
  unsigned long unsignedOrderId = static_cast<unsigned long>(orderId);         \
  std::string moduleString = moduleId;                                         \
  std::string textString = text;                                               \
  try {                                                                        \
    sql << SQL_CREATE_ORDER_LOG,                                               \
      soci::use(id),                                                           \
      soci::use(std::string(moduleString)),                                    \
      soci::use(unsignedOrderId),                                              \
      soci::use(std::string(status)),                                          \
      soci::use(std::string(textString));                                      \
  } catch (std::exception const &e) {                                          \
    std::cerr << " error:" << e.what()<<'\n';                                  \
  }                                                                            \
 }
#endif
#else
#define ORDER_LOG(moduleId, orderId, status, text) {                           \
}
#endif

#endif
