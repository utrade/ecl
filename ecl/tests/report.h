/*******************************************************************************
* Date      | Name   | Description                                             *
* 03 Oct 13 | Jovito | Req #1848 : Test Cases For ECL                          *
*******************************************************************************/

#ifndef UT_REPORT_H
#define UT_REPORT_H

#ifndef _MSC_VER
#include <sys/time.h>
#endif

namespace UT
{
  class Report
  {
    public :
      Report() ;
      long getTickCount() ;
      void start() ;
      void reset() ; // same as start. Just different name
      void report( const std::string &message, long count ) ;
      void display( const std::string &message, long count ) ;

    private :
      long _beginTick ;
  };

  /*****************************************************************************
  * Returns the current time in ms                                             *
  *****************************************************************************/
  inline long Report::getTickCount()
  {
#ifndef WIN32
    timeval tv;
    gettimeofday( &tv, 0 );
    long millsec = tv.tv_sec * 1000;
    millsec += ( long ) tv.tv_usec / ( 1000 );

    return ( long ) millsec;
#else 
    return GetTickCount() ;
#endif
  }

  /*****************************************************************************
   * Start the report                                                          *
   *  This is the time after which we being executing our commands             *
   * To check multiple situations, we can always call start, report, start     *
   * Or create multiple report objects                                         *
   ****************************************************************************/
  inline void Report::start()
  {
    _beginTick = getTickCount() ;
  }

  inline void Report::reset()
  {
    _beginTick = getTickCount() ;
  }
  
  /*****************************************************************************
  * Same as start                                                              *
  *****************************************************************************/
  inline Report::Report() 
  {
    _beginTick = getTickCount() ;
  }

  /*****************************************************************************
   * Displays the report message                                               *
   *  Calculated as current time - begin time                                  *
   * This does not reset the begin time so that we can continue using it       *
   ****************************************************************************/
  inline void Report::report( const std::string &message, long count ) 
  {
    long time = getTickCount() - _beginTick ;
    double seconds = ( double ) time / 1000.0 ;
    double num_per_second = count / seconds;

    std::cout 
      << message << " : " << std::endl 
      << "    num: " << count
      << ", seconds: " << seconds
      << ", num_per_second: " << num_per_second << std::endl;
  }

  /*****************************************************************************
  * Same as report                                                             *
  *****************************************************************************/
  inline void Report::display( const std::string &message, long count ) 
  {
    report( message, count ) ;
  }
}
#endif // UT_REPORT_H
