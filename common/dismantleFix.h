#ifndef DISMANTLE_FIX_H
#define DISMANTLE_FIX_H

#ifndef NDEBUG // DO NOT INCLUDE IN RELEASE BUILDS

#include <iostream>
#include <iomanip>

#include <boost/unordered_map.hpp>

namespace UT
{
  class DismantleFix
  {
    public :
      static void initializeTagNames();
      static void initializeTagDescription();

      static void dismantle( std::string direction, std::string fixMessage );

    private :
      static boost::unordered_map< std::string , std::string> _fixTags;
      static boost::unordered_map< std::string , std::string> _fixTagsDesc;
  };
}

#endif // NDEBUG 

#endif // DISMANTLE_FIX_H
