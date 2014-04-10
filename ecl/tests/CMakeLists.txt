#add_executable(testEcl 
#    testEcl
#)

#target_link_libraries(XXXX 
#  omb
#  nnf
#  common
#  mcx
#  instinetEcl
#  tradingTechEcl
#  ${OPENSSL_LIBRARIES}
#  ${SOCI_LIBRARIES} 
#  ${SOCIPOSTGRESQL_LIBRARIES} 
#  ${PostgreSQL_LIBRARIES} 
#  ${Boost_SYSTEM_LIBRARY}
#  ${Boost_PROGRAM_OPTIONS_LIBRARY}
#  ${Boost_THREAD_LIBRARY}
#  ${Boost_DATE_TIME_LIBRARY}
#  ${Boost_SERIALIZATION_LIBRARY}
#  ${Boost_REGEX_LIBRARY}
#  ${Boost_CHRONO_LIBRARY}
#  ${QUICKFIX_LIBRARIES}
#)

SET(EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/tests)

add_executable(testEcl 
    testEcl.cpp
    roundTripTime.cpp
    placeOrder.cpp
)

target_link_libraries(testEcl 
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
  target_link_libraries(testEcl  
    ws2_32.lib
    )
ENDIF(WIN32)


add_executable(testQuickFix
    testQuickFix
)
target_link_libraries(testQuickFix 
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
  target_link_libraries(testQuickFix  
    ws2_32.lib
    )
ENDIF(WIN32)

