## Find SOCIPOSTGRESQL
##
## Copyright (c) 2010 Jamie Jones <jamie_jones_au@yahoo.com.au>
## This file is licensed under the GNU GPLv2 or any later versions,
##
## This module defines
## SOCIPOSTGRESQL_LIBRARIES
## SOCIPOSTGRESQL_FOUND, if false, do not try to link to SOCIPOSTGRESQL
## SOCIPOSTGRESQL_INCLUDE_DIRS, where to find the headers
##

FIND_PATH(SOCIPOSTGRESQL_INCLUDE_DIRS postgresql/soci-postgresql.h
    ${SOCIPOSTGRESQL_DIR}/include
    ${SOCIPOSTGRESQL_DIR}/include/soci
    $ENV{SOCIPOSTGRESQL_DIR}/include
    $ENV{SOCIPOSTGRESQL_DIR}/include/soci
    $ENV{SOCIPOSTGRESQL_DIR}
    /usr/local/include
    /usr/local/include/soci
    /usr/include
    /usr/include/soci
    /sw/include # Fink
    /opt/local/include # DarwinPorts
    /opt/csw/include # Blastwave
    /opt/include
)

FIND_LIBRARY(SOCIPOSTGRESQL_LIBRARIES
  IF(WIN32)
    NAMES libsoci_postgresql
  ELSE(WIN32)
    NAMES soci_postgresql
  ENDIF(WIN32)
    PATHS
    ${SOCIPOSTGRESQL_DIR}/lib
    $ENV{SOCIPOSTGRESQL_DIR}/lib
    $ENV{SOCIPOSTGRESQL_DIR}
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

IF(SOCIPOSTGRESQL_LIBRARIES)
    IF (NOT SOCIPOSTGRESQL_FIND_QUIETLY)
    MESSAGE(STATUS "Found the SOCIPOSTGRESQL library at ${SOCIPOSTGRESQL_LIBRARIES}")
    MESSAGE(STATUS "Found the SOCIPOSTGRESQL headers at ${SOCIPOSTGRESQL_INCLUDE_DIRS}")
    ENDIF (NOT SOCIPOSTGRESQL_FIND_QUIETLY)
ENDIF(SOCIPOSTGRESQL_LIBRARIES)

IF(NOT SOCIPOSTGRESQL_LIBRARIES)
    IF (SOCIPOSTGRESQL_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "SOCIPOSTGRESQL Not Found.")
    ENDIF (SOCIPOSTGRESQL_FIND_REQUIRED)
ENDIF(NOT SOCIPOSTGRESQL_LIBRARIES)
