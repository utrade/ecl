cmake_minimum_required(VERSION 2.6)

add_definitions(-DWITH_ESMNSE_FIX42)
add_definitions(-DWITH_PLUS_FIX44)

project(uTrade)
set(uTrade_VERSION_MAJOR 0)
set(uTrade_VERSION_MINOR 0)
set(uTrade_VERSION_PATCH 1)

set(uTrade_VERSION_STRING
  "${uTrade_VERSION_MAJOR}.${uTrade_VERSION_MINOR}.${uTrade_VERSION_PATCH}")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
  message(STATUS "Setting Default Build Type : Debug ")
endif(NOT CMAKE_BUILD_TYPE)

if(CMAKE_BUILD_TYPE MATCHES "[Re][Ee][Ll][Ee][Aa][Ss][Ee]")
  set(uTrade_EXE_PREFIX "")
  set(uTrade_EXE_SUFFIX "")
  set(LIBRARY_OUTPUT_PATH ${uTrade_SOURCE_DIR}/lib/release)
else(CMAKE_BUILD_TYPE MATCHES "[Re][Ee][Ll][Ee][Aa][Ss][Ee]")
  set(uTrade_EXE_PREFIX "")
  set(uTrade_EXE_SUFFIX "")
  set(LIBRARY_OUTPUT_PATH ${uTrade_SOURCE_DIR}/lib/debug)
endif(CMAKE_BUILD_TYPE MATCHES "[Re][Ee][Ll][Ee][Aa][Ss][Ee]")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${uTrade_SOURCE_DIR}/config.h.in"
  "${uTrade_SOURCE_DIR}/config.h"
  )

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

  find_package(Boost 1.51 REQUIRED COMPONENTS
    python
    system
    filesystem
    serialization
    thread
    program_options
    regex
    chrono
    test_exec_monitor)

  # find_package(LibXml2 REQUIRED)
  # include_directories(${LIBXML2_INCLUDE_DIR})

include_directories(${Boost_INCLUDE_DIRS})

find_package(QUICKFIX REQUIRED)
include_directories(${QUICKFIX_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall ")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall ")

include_directories(${uTrade_SOURCE_DIR}/common)

set(INSTALL_TARGETS_DEFAULT RUNTIME DESTINATION .)

set(EXECUTABLE_OUTPUT_PATH ${uTrade_SOURCE_DIR}/bin)


add_subdirectory(common)
add_subdirectory(ecl)
