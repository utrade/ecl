#include "errorlog.h"

int getDebugLevel()
{
  static int logLevel = 0;
  if (logLevel == 0) {                      
    if (getenv(ENV_DEBUG_LEVEL) == NULL) {
      logLevel = INFO_LEVEL;
    }
    else {
      char *level = getenv(ENV_DEBUG_LEVEL);
      if (strncmp(level, "FATAL", 5) == 0)
        logLevel = FATAL_LEVEL;
      else if (strncmp(level, "ERROR", 5) == 0)
        logLevel = ERROR_LEVEL;
      else if (strncmp(level, "WARN", 4) == 0)
        logLevel = WARN_LEVEL;
      else if (strncmp(level, "INFO", 4) == 0)
        logLevel = INFO_LEVEL;
      else
        logLevel = INFO_LEVEL;
    }
  }
  return logLevel;
}

std::string getCurrentTime() 
{
  static const char wday_name[][4] = {
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
  };
  static const char mon_name[][4] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
  };

  char result[36];

#ifndef _MSC_VER
  timespec currentTime ;
  clock_gettime(CLOCK_REALTIME, &currentTime ) ;

  tm *timeptr = localtime ( &currentTime.tv_sec );

  sprintf(result, "%.3s %.3s%3d %.2d:%.2d:%.2d.%.8d %d",
      wday_name[timeptr->tm_wday],
      mon_name[timeptr->tm_mon],
      timeptr->tm_mday, timeptr->tm_hour,
      timeptr->tm_min, timeptr->tm_sec, currentTime.tv_nsec,
      1900 + timeptr->tm_year);

#else // _MSC_VER
  time_t currentTime_tv_sec ;

  tm *timeptr = localtime ( &currentTime_tv_sec );

  sprintf(result, "%.3s %.3s%3d %.2d:%.2d:%.2d %d",
      wday_name[timeptr->tm_wday],
      mon_name[timeptr->tm_mon],
      timeptr->tm_mday, timeptr->tm_hour,
      timeptr->tm_min, timeptr->tm_sec,
      1900 + timeptr->tm_year);

#endif // _MSC_VER

  return std::string( result ) ;
}
