#include <boost/thread.hpp>

#if defined(WIN32) 
// If you do not add this line, you get an error when compiling on windows
namespace boost {
    struct thread::dummy {};
}
#endif // WIN32


#include "context.h"


int main( int argc, char * argv[])
{
  UT::ECL::Context context ;

  if( ! context.init( argc, argv ) )
    return 1 ;

  context.start() ;

  std::string command ;
  while( command != "q" )
  {
    std::cin >> command ;
  }

  context.stop() ;

  return 0 ;
}



