#ifndef LOGGER_H
#define LOGGER_H

#include <sstream>
#include <string>

#pragma GCC diagnostic ignored "-Wformat"

#ifdef WIN32
 #define openlog(A,B,C){}
 #define syslog(A,B){}
 #define LOG_CONS 0
 #define LOG_PID 0
 #define LOG_PERROR 0
 #define LOG_LOCAL0 0
 #define LOG_INFO 0
#else
 #include <syslog.h>
#endif


namespace UT {

  class Logger
  {
  public:
    Logger(const std::string& program,
           int facility)
      : _facility(facility)
    {
        openlog(program.c_str(), LOG_CONS | LOG_PID | LOG_PERROR, _facility);
    }

    void log(int level,
             const std::string& message)
    {
      syslog(level | _facility, message.c_str());
    }

  private:
    int _facility;
  };

  class OrderLog
  {
  public:
    static OrderLog* getInstance()
    {
      static OrderLog _log;
      return &_log;
    }

    void log(const std::string& moduleId,
             long orderId,
             const std::string& status,
             const std::string& text)
    {
      std::stringstream ss;
      ss << moduleId
         << ":"
         << orderId
         << ":"
         << status
         << ":"
         << text;
      _orderLog.log(LOG_INFO, ss.str());
    }

  private:
    OrderLog()
      : _orderLog("orderlogs", LOG_LOCAL0)
    {
    }

    Logger _orderLog;
  };
    

}

#endif
