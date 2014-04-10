# - Find OPENSSL
# Find the OPENSSL includes and client library
# This module defines
#  OPENSSL_INCLUDE_DIRS, where to find openssl/md5.h
#  OPENSSL_LIBRARIES, the libraries needed to use OPENSSL.
#  OPENSSL_FOUND, If false, do not try to use OPENSSL.

if(OPENSSL_INCLUDE_DIRS AND OPENSSL_LIBRARIES)
  set(OPENSSL_FOUND TRUE)

else(OPENSSL_INCLUDE_DIRS AND OPENSSL_LIBRARIES)

  find_path(OPENSSL_INCLUDE_DIRS openssl/md5.h
      /usr/include/
      /usr/local/include/
      /usr/include/openssl/
      /usr/local/include/openssl/
      /opt/openssl/include/
      $ENV{ProgramFiles}/openssl/include
      $ENV{SystemDrive}/uickfix/include
      $ENV{OPENSSL_DIR}/include
      )

if(WIN32)
  find_library(OPENSSL_LIBRARIES NAMES libeay32
      PATHS
      $ENV{ProgramFiles}/quickfix/*/lib
      $ENV{SystemDrive}/quickfix/*/lib
      $ENV{OPENSSL_DIR}/lib
      $ENV{OPENSSL_DIR}/
      )
else(WIN32)
  find_library(OPENSSL_LIBRARIES NAMES crypto
      PATHS
      /usr/include/
      /usr/local/include/
      /usr/include/openssl/
      /usr/local/include/openssl/
      /opt/openssl/lib/
      )
endif(WIN32)

#if(OPENSSL_INCLUDE_DIRS AND OPENSSL_LIBRARIES)
if(OPENSSL_INCLUDE_DIRS )
    set(OPENSSL_FOUND TRUE)
    message(STATUS "Found OPENSSL: ${OPENSSL_INCLUDE_DIRS}, ${OPENSSL_LIBRARIES}")
  else(OPENSSL_INCLUDE_DIRS )
    set(OPENSSL_FOUND FALSE)
    if (OPENSSL_FIND_REQUIRED)
      message(FATAL_ERROR "OPENSSL not found.Check Environment Variable OPENSSL_DIR")
      else (OPENSSL_FIND_REQUIRED)
        message(STATUS "OPENSSL not found.")
        endif (OPENSSL_FIND_REQUIRED)
      endif(OPENSSL_INCLUDE_DIRS )

    endif(OPENSSL_INCLUDE_DIRS AND OPENSSL_LIBRARIES)
