# - Find Thrift
# Find the Thrift includes and client library
# This module defines
#  Thrift_INCLUDE_DIRS, where to find lzo*h
#  Thrift_LIBRARIES, the libraries needed to use Thrift.
#  Thrift_FOUND, If false, do not try to use Thrift.

if(Thrift_INCLUDE_DIRS AND Thrift_LIBRARIES AND Thrift_NB_LIBRARIES)
  set(Thrift_FOUND TRUE)
  
else(Thrift_INCLUDE_DIRS AND Thrift_LIBRARIES)
  
  find_path(Thrift_INCLUDE_DIRS Thrift.h
    /usr/include/
    /usr/local/include/
    /usr/include/thrift/
    /usr/local/include/thrift/
    /opt/thrift/include/
    $ENV{ProgramFiles}/thrift/*/include
    $ENV{SystemDrive}/thrift/*/include
    )
  
  if(WIN32)
    find_library(Thrift_LIBRARIES NAMES thrift
      PATHS
      $ENV{ProgramFiles}/thrift/*/lib
      $ENV{SystemDrive}/thrift/*/lib
      )
    find_library(Thrift_NB_LIBRARIES NAMES thriftnb
      PATHS
      $ENV{ProgramFiles}/thrift/*/lib
      $ENV{SystemDrive}/thrift/*/lib
      )
  else(WIN32)
    find_library(Thrift_LIBRARIES NAMES thrift
      PATHS
      /usr/lib
      /usr/lib/thrift
      /usr/local/lib
      /usr/local/lib/thrift
      /opt/thrift/lib
      )
    find_library(Thrift_NB_LIBRARIES NAMES thriftnb
      PATHS
      /usr/lib
      /usr/lib/thrift
      /usr/local/lib
      /usr/local/lib/thrift
      /opt/thrift/lib
      )
  endif(WIN32)
  
  if(Thrift_INCLUDE_DIRS AND Thrift_LIBRARIES AND Thrift_NB_LIBRARIES)
    set(Thrift_FOUND TRUE)
    message(STATUS "Found Thrift: ${Thrift_INCLUDE_DIRS}, ${Thrift_LIBRARIES}, ${Thrift_NB_LIBRARIES}")
  else(Thrift_INCLUDE_DIRS AND Thrift_LIBRARIES AND Thrift_NB_LIBRARIES)
    set(Thrift_FOUND FALSE)
    if (Thrift_FIND_REQUIRED)
      message(FATAL_ERROR "Thrift not found.")
    else (Thrift_FIND_REQUIRED)
      message(STATUS "Thrift not found.")
    endif (Thrift_FIND_REQUIRED)
  endif(Thrift_INCLUDE_DIRS AND Thrift_LIBRARIES AND Thrift_NB_LIBRARIES)
  
  mark_as_advanced(Thrift_INCLUDE_DIRS Thrift_LIBRARIES Thrift_NB_LIBRARIES)
  
endif(Thrift_INCLUDE_DIRS AND Thrift_LIBRARIES AND Thrift_NB_LIBRARIES)
