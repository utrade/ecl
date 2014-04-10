# - Find Protobuf
# Find the Protobuf includes and client library
# This module defines
#  Protobuf_INCLUDE_DIRS, where to find protobuf.hpp
#  Protobuf_LIBRARIES, the libraries needed to use Protobuf.
#  Protobuf_FOUND, If false, do not try to use Protobuf.

if(Protobuf_INCLUDE_DIRS AND Protobuf_LIBRARIES)
   set(Protobuf_FOUND TRUE)

else(Protobuf_INCLUDE_DIRS AND Protobuf_LIBRARIES)

  find_path(Protobuf_INCLUDE_DIRS google/protobuf/stubs/common.h
      /usr/include/
      /usr/local/include/
      /usr/include/protobuf/
      /usr/local/include/protobuf/
      /opt/protobuf/include/
      $ENV{ProgramFiles}/protobuf/*/include
      $ENV{SystemDrive}/protobuf/*/include
      )

if(WIN32)
  find_library(Protobuf_LIBRARIES NAMES protobuf
      PATHS
      $ENV{ProgramFiles}/protobuf/*/lib
      $ENV{SystemDrive}/protobuf/*/lib
      )
else(WIN32)
  find_library(Protobuf_LIBRARIES NAMES protobuf
      PATHS
      /usr/lib
      /usr/lib/protobuf
      /usr/local/lib
      /usr/local/lib/protobuf
      /opt/protobuf/lib
      )
endif(WIN32)

if(Protobuf_INCLUDE_DIRS AND Protobuf_LIBRARIES)
    set(Protobuf_FOUND TRUE)
    message(STATUS "Found Protobuf: ${Protobuf_INCLUDE_DIRS}, ${Protobuf_LIBRARIES}")
  else(Protobuf_INCLUDE_DIRS AND Protobuf_LIBRARIES)
    set(Protobuf_FOUND FALSE)
    if (Protobuf_FIND_REQUIRED)
      message(FATAL_ERROR "Protobuf not found.")
      else (Protobuf_FIND_REQUIRED)
        message(STATUS "Protobuf not found.")
        endif (Protobuf_FIND_REQUIRED)
  endif(Protobuf_INCLUDE_DIRS AND Protobuf_LIBRARIES)

  mark_as_advanced(Protobuf_INCLUDE_DIRS Protobuf_LIBRARIES)

endif(Protobuf_INCLUDE_DIRS AND Protobuf_LIBRARIES)
