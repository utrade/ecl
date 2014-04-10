# - Find ZMQ
# Find the ZMQ includes and client library
# This module defines
#  ZMQ_INCLUDE_DIRS, where to find zmq.hpp
#  ZMQ_LIBRARIES, the libraries needed to use ZMQ.
#  ZMQ_FOUND, If false, do not try to use ZMQ.

if(ZMQ_INCLUDE_DIRS AND ZMQ_LIBRARIES)
   set(ZMQ_FOUND TRUE)

else(ZMQ_INCLUDE_DIRS AND ZMQ_LIBRARIES)

  find_path(ZMQ_INCLUDE_DIRS zmq.hpp
      /usr/include/
      /usr/local/include/
      /usr/include/zmq/
      /usr/local/include/zmq/
      /opt/zmq/include/
      $ENV{ProgramFiles}/zmq/*/include
      $ENV{SystemDrive}/zmq/*/include
      )

if(WIN32)
  find_library(ZMQ_LIBRARIES NAMES zmq
      PATHS
      $ENV{ProgramFiles}/zmq/*/lib
      $ENV{SystemDrive}/zmq/*/lib
      )
else(WIN32)
  find_library(ZMQ_LIBRARIES NAMES zmq
      PATHS
      /usr/lib
      /usr/lib/zmq
      /usr/local/lib
      /usr/local/lib/zmq
      /opt/zmq/lib
      )
endif(WIN32)

if(ZMQ_INCLUDE_DIRS AND ZMQ_LIBRARIES)
    set(ZMQ_FOUND TRUE)
    message(STATUS "Found ZMQ: ${ZMQ_INCLUDE_DIRS}, ${ZMQ_LIBRARIES}")
  else(ZMQ_INCLUDE_DIRS AND ZMQ_LIBRARIES)
    set(ZMQ_FOUND FALSE)
    if (ZMQ_FIND_REQUIRED)
      message(FATAL_ERROR "ZMQ not found.")
      else (ZMQ_FIND_REQUIRED)
        message(STATUS "ZMQ not found.")
        endif (ZMQ_FIND_REQUIRED)
endif(ZMQ_INCLUDE_DIRS AND ZMQ_LIBRARIES)

  mark_as_advanced(ZMQ_INCLUDE_DIRS ZMQ_LIBRARIES)

endif(ZMQ_INCLUDE_DIRS AND ZMQ_LIBRARIES)
