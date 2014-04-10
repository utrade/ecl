/*******************************************************************************
* Date      | Name   | Description                                             *
* 03 Oct 13 | Jovito | Req #1848 : Test Cases For ECL                          *
*******************************************************************************/

#ifndef UT_TESTS_CONSTANTS_H
#define UT_TESTS_CONSTANTS_H

#ifndef _MSC_VER
#include <sys/time.h>

/*******************************************************************************
* There is a class to do this in report.h. But u can also use these here.      *
* Completely your choice                                                       *
*******************************************************************************/
inline long GetTickCount()
{
  timeval tv;
  gettimeofday( &tv, 0 );
  long millsec = tv.tv_sec * 1000;
  millsec += ( long ) tv.tv_usec / ( 1000 );

  return ( long ) millsec;
}
#endif

inline void report( int time, int count )
{
  double seconds = ( double ) time / 1000;
  double num_per_second = count / seconds;
  std::cout << std::endl << "    num: " << count
  << ", seconds: " << seconds
  << ", num_per_second: " << num_per_second << std::endl;
}

// Get a user input

inline std::string getUserInput( const std::string &msg )
{
  std::string userInput ;
  std::cout << msg << " : "  ;
  std::getline ( std::cin, userInput ) ;
  return userInput ;
}

#endif // UT_TESTS_CONSTANTS_H
