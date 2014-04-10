## Find Libevent
##
## Copyright (c) 2010 Jamie Jones <jamie_jones_au@yahoo.com.au>
## This file is licensed under the GNU GPLv2 or any later versions,
##
## This module defines
## Libevent_LIBRARIES
## Libevent_FOUND, if false, do not try to link to Libevent
## Libevent_INCLUDE_DIRS, where to find the headers
##

FIND_PATH(Libevent_INCLUDE_DIRS event.h
    ${Libevent_DIR}/include
    ${Libevent_DIR}/include/soci
    $ENV{Libevent_DIR}/include
    $ENV{Libevent_DIR}/include/soci
    $ENV{Libevent_DIR}
    /usr/local/include
    /usr/local/include/soci
    /usr/include
    /usr/include/soci
    /sw/include # Fink
    /opt/local/include # DarwinPorts
    /opt/csw/include # Blastwave
    /opt/include
)

FIND_LIBRARY(Libevent_LIBRARIES
    NAMES event
    PATH
    ${Libevent_DIR}/lib
    $ENV{Libevent_DIR}/lib
    $ENV{Libevent_DIR}
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

IF(Libevent_LIBRARIES)
    IF (NOT Libevent_FIND_QUIETLY)
    MESSAGE(STATUS "Found the Libevent library at ${Libevent_LIBRARIES}")
    MESSAGE(STATUS "Found the Libevent headers at ${Libevent_INCLUDE_DIRS}")
    ENDIF (NOT Libevent_FIND_QUIETLY)
ENDIF(Libevent_LIBRARIES)

IF(NOT Libevent_LIBRARIES)
    IF (Libevent_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Libevent Not Found.")
    ENDIF (Libevent_FIND_REQUIRED)
ENDIF(NOT Libevent_LIBRARIES)
