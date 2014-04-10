# - Find LZO
# Find the LZO includes and client library
# This module defines
#  LZO_INCLUDE_DIRS, where to find lzo*h
#  LZO_LIBRARIES, the libraries needed to use LZO.
#  LZO_FOUND, If false, do not try to use LZO.

if(LZO_INCLUDE_DIRS AND LZO_LIBRARIES)
   set(LZO_FOUND TRUE)

else(LZO_INCLUDE_DIRS AND LZO_LIBRARIES)

  find_path(LZO_INCLUDE_DIRS lzo/lzo1x.h
      /usr/include/
      /usr/local/include/
      /usr/include/lzo/
      /usr/local/include/lzo/
      /opt/lzo/include/
      $ENV{ProgramFiles}/lzo/*/include
      $ENV{SystemDrive}/lzo/*/include
      $ENV{LZO_DIR}/include
      )

if(WIN32)
  find_library(LZO_LIBRARIES NAMES lzo2
      PATHS
      $ENV{ProgramFiles}/lzo/*/lib
      $ENV{SystemDrive}/lzo/*/lib
      $ENV{LZO_DIR}/lib
      $ENV{LZO_DIR}/
      )
else(WIN32)
  find_library(LZO_LIBRARIES NAMES lzo2
      PATHS
      /usr/lib
      /usr/lib/lzo
      /usr/local/lib
      /usr/local/lib/lzo
      /opt/lzo/lib
      )
endif(WIN32)

  if(LZO_INCLUDE_DIRS AND LZO_LIBRARIES)
    set(LZO_FOUND TRUE)
    message(STATUS "Found LZO: ${LZO_INCLUDE_DIRS}, ${LZO_LIBRARIES}")
  else(LZO_INCLUDE_DIRS AND LZO_LIBRARIES)
    set(LZO_FOUND FALSE)
    if (LZO_FIND_REQUIRED)
      message(FATAL_ERROR "LZO not found.Check Environment Variable LZO_DIR")
      else (LZO_FIND_REQUIRED)
        message(STATUS "LZO not found.Check Environment Variable LZO_DIR")
        endif (LZO_FIND_REQUIRED)
  endif(LZO_INCLUDE_DIRS AND LZO_LIBRARIES)

  mark_as_advanced(LZO_INCLUDE_DIRS LZO_LIBRARIES)

endif(LZO_INCLUDE_DIRS AND LZO_LIBRARIES)
