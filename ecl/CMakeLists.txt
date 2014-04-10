add_subdirectory(tests)

add_executable(ecl 
  eclMain.cpp 
  context.cpp 
  fixConverter.cpp

  omsHandler.cpp 

  esmNseAdapter.cpp 
  plusAdapter.cpp 
)

#grouping files in VS2010
SOURCE_GROUP(nse nse/* )
SOURCE_GROUP(mcx mcx/* )
#end of grouping files in VS2010

target_link_libraries(ecl 
  common
  ${OPENSSL_LIBRARIES}
  ${SOCI_LIBRARIES} 
  ${SOCIPOSTGRESQL_LIBRARIES} 
  ${PostgreSQL_LIBRARIES} 
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  ${Boost_DATE_TIME_LIBRARY}
  ${Boost_SERIALIZATION_LIBRARY}
  ${Boost_REGEX_LIBRARY}
  ${Boost_CHRONO_LIBRARY}
  ${QUICKFIX_LIBRARIES}
)

IF(WIN32)
  target_link_libraries(ecl 
    ws2_32.lib
    )
ENDIF(WIN32)

set_target_properties(ecl PROPERTIES
  OUTPUT_NAME "${uTrade_EXE_PREFIX}ecl${uTrade_EXE_SUFFIX}"
)

set_target_properties(ecl PROPERTIES
  COMPILE_FLAGS "-DENABLE_SSL -DUSE_SYSLOG"
)

install(TARGETS ecl
  RUNTIME
  DESTINATION bin
  COMPONENT applications
)
