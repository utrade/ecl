## Copyright (c) 2010 Jamie Jones <jamie_jones_au@yahoo.com.au>
## This file is licensed under the GNU GPLv2 or any later versions,
##
## This module defines
## PostgreSQL_LIBRARIES
## PostgreSQL_FOUND, if false, do not try to link to PostgreSQL
## PostgreSQL_INCLUDE_DIRS, where to find the headers
##

FIND_PATH(PostgreSQL_INCLUDE_DIRS libpq-fe.h
    ${PostgreSQL_DIR}/include
    ${PostgreSQL_DIR}/include/postgresql
    $ENV{PostgreSQL_DIR}/include
    $ENV{PostgreSQL_DIR}/include/postgresql
    $ENV{PostgreSQL_DIR}
    /usr/local/include
    /usr/local/include/postgresql
    /usr/include
    /usr/include/postgresql
    /sw/include # Fink
    /opt/local/include # DarwinPorts
    /opt/csw/include # Blastwave
    /opt/include
)

FIND_LIBRARY(PostgreSQL_LIBRARIES
  if(WIN32)
    NAMES libpq
  else(WIN32)
    NAMES pq
  endif(WIN32)
    PATHS
    ${PostgreSQL_DIR}/lib
    $ENV{PostgreSQL_DIR}/lib
    $ENV{PostgreSQL_DIR}
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/lib
    /usr/local/lib64
    /usr/lib
    /usr/lib64
    /sw/lib
    /opt/local/lib
    /opt/csw/lib
    /opt/lib
)

IF(PostgreSQL_LIBRARIES)
    IF (NOT PostgreSQL_FIND_QUIETLY)
    MESSAGE(STATUS "Found the PostgreSQL library at ${PostgreSQL_LIBRARIES}")
    MESSAGE(STATUS "Found the PostgreSQL headers at ${PostgreSQL_INCLUDE_DIRS}")
    ENDIF (NOT PostgreSQL_FIND_QUIETLY)
ENDIF(PostgreSQL_LIBRARIES)

IF(NOT PostgreSQL_LIBRARIES)
    IF (PostgreSQL_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "PostgreSQL Not Found.Check Environmental variable PostgresSQL_DIR")
    ENDIF (PostgreSQL_FIND_REQUIRED)
ENDIF(NOT PostgreSQL_LIBRARIES)
