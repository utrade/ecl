/*******************************************************************************
* Date      | Author | Notes                                                   *
* 18 Nov 13 | Jovito | Task #1979 : DATAFEEDER LAYER FOR MONEYUTRADE AND UTRADE*
*******************************************************************************/

#include "errorlog.h"

// Db Errors
DEFINE_MSG(5000, PROBLEM_DB_TRANSACTION_ENTRY, "Could not create DB transaction entry for orderId: %1%, Db error: %2%");
DEFINE_MSG(5001, PROBLEM_DB_TRADE_ENTRY, "Could not create DB trade entry for orderId: %1%, Db error: %2%");
DEFINE_MSG(5002, PROBLEM_DB_CREATE_ORDER, "Could not create DB order entry for orderId: %1%, Db error: %2%");
DEFINE_MSG(5003, PROBLEM_DB_UPDATE_ORDER, "Could not update DB order entry for orderId: %1%, Db error: %2%");
DEFINE_MSG(5004, PROBLEM_DB_FIND_ORDER, "Could not find DB entry for orderId: %1%");
DEFINE_MSG(5005, PROBLEM_EXCEPTION, " Error : %1%");

// Socket Errors. Range of 6000.
DEFINE_MSG(6000, PROBLEM_SOCKET_MULTICAST_JOIN, "Could Not Join Multicast Group %1% on port %2% and interface %3%. Reason %4%");
DEFINE_MSG(6001, PROBLEM_SOCKET_MULTICAST_BIND, "Could Not Bind to Multicast Group %1% on port %2%. Reason %3%");
DEFINE_MSG(6002, PROBLEM_SOCKET_UDP_BIND, "Could Not Bind to port %1%. Reason %2%");
DEFINE_MSG(6003, PROBLEM_SOCKET_ON_CONNECT_CLOSED, "Cant connect since socket has been closed" );
DEFINE_MSG(6004, INFO_SOCKET_RECONNECT_AFTER, "Reconnecting After %1%" );
DEFINE_MSG(6005, INFO_SOCKET_CONNECTING_TO, "Connecting to %1%" );
DEFINE_MSG(6006, INFO_SOCKET_NO_MORE_ENDPOINTS, "No more endpoints to connect to." );
DEFINE_MSG(6007, PROBLEM_SOCKET_ON_READ_CLOSED, "Cant connect since socket has been closed" );
DEFINE_MSG(6008, PROBLEM_SOCKET_TIMEOUT, "Timeout when reading from socket" ) ;
DEFINE_MSG(6009, PROBLEM_SOCKET_ON_CONNECT, "Error when connecting to socket : %1%" ) ;
DEFINE_MSG(6010, INFO_SOCKET_CONNECTED, "Successfully connected" ) ;
DEFINE_MSG(6011, PROBLEM_DB_CONNECTIVITY, "Could Not connect to database reason : %1% " ) ;
DEFINE_MSG(6012, PROBLEM_DB_SETTINGS, "Could not read settings for db connectivity : " ) ;
DEFINE_MSG(6013, PROBLEM_SOCKET_EOF, "The socket has been closed by the other end when reading from : %1%" ) ;
DEFINE_MSG(6014, CONFIG_NOT_FOUND_FOR_MARKET, "Config not found for market : %1%" ) ;
DEFINE_MSG(6015, CONFIGURING, "Configuring %1% for module %2% " )
DEFINE_MSG(6016, PROBLEM_SOCKET_ON_WRITE, "Error when writing on socket : %1%" ) ;

// File Errors. Range of 7000.
DEFINE_MSG(7000, CONFIG_ERROR_PTREE_KEY_MISSING, " Error in configuration for %1%, key missing in section %2% : %3% ");
DEFINE_MSG(7001, CONFIG_ERROR_KEY_MISSING, " Error in file '%1%' when configuring '%2%', key '%3%' is missing. \n\tCreate an entry for '%3%' in file '%1%' and restart '%2%'");
DEFINE_MSG(7002, CONFIG_ERROR_PTREE_BAD_DATA, " Error in configuration for %1%, data corrupted in section %2% : %3% ");
DEFINE_MSG(7003, CONFIG_ERROR_BAD_DATA, " Error in file '%1%' when configuring '%2%', data corrupted : %3% ");
DEFINE_MSG(7004, CONFIG_ERROR_PTREE_UNKNOWN, " Error in configuration for %1%, section %2% : %3% ");
DEFINE_MSG(7005, CONFIG_ERROR_FILE_MISSING, " Error in configuration for %1%, file %2% is missing " ) ;
DEFINE_MSG(7006, CONFIG_ERROR_INI_PARSE, " Error in configuration %1% : %2% " ) ;
DEFINE_MSG(7007, CONFIG_ERROR_READING_OMS_DESTINATION, " Error in configuration when reading oms destination: %1% " ) ;
DEFINE_MSG(7008, CONFIG_ERROR_READING_EXCHANGE_DESTINATIONS, " Error in configuration when reading exchange destinations: %1% " ) ;
DEFINE_MSG(7009, ERROR_DURING_CONFIGURATION, "Error During Configuration %1% : %2%" ) ;

// Exchange Errors. Range of 8000.
DEFINE_MSG(8000, EXCHANGE_LOGIN_ERROR, "%1% - %2% " );
DEFINE_MSG(8001, EXCHANGE_LOGIN_ERROR_END_CONNECTION, "%1% - %2% .. Disabling Connection " );
DEFINE_MSG(8002, EXCHANGE_RECONNECT, "Reconnecting to %1% after %2% seconds" );
DEFINE_MSG(8003, EXCHANGE_ERROR, "Received Error %1%" ) ;
DEFINE_MSG(8004, LOGON_SUCCESSFUL, "*********************** Logged On To %1% With %2% ***********************" ) ;
DEFINE_MSG(8005, UNKNOWN_DESTINATION, "%1% MarketDestination Not Set In Any Session Of Ecl Setting" ) ;
DEFINE_MSG(8006, PRICE_NOT_IN_CIRCUIT_LIMITS, "Price Is Not In Circuit Limits" ) ;
DEFINE_MSG(8007, INCORRECT_DATA_FORMAT, "Incorrect Data format for field %1%, Sending reject (Add later )");
DEFINE_MSG(8008, UNKNOWN_TCODE , "Unknown TCODE %1%" ) ;
DEFINE_MSG(8009, MESSAGE_NOT_HANDLED , "Message %1% is not handled currently " ) ;
DEFINE_MSG(8010, CONNECTED_TO, "Connect To %1%" ) ;
DEFINE_MSG(8011, DISCONNECTED_FROM, "Disconnect From %1%" ) ;
DEFINE_MSG(8012, SESSION_NOT_FOUND , "Could not find session %1% for market_id %2%. Check table appmaster.exchange_sessions" )
DEFINE_MSG(8013, DUPLICATE_START , "Initiator has already been started. Ignoring Request" ) ;
DEFINE_MSG(8014, EXCHANGE_MESSAGE, "%1% %2%" ) ;
DEFINE_MSG(8015, CANNOT_SEND_FIX_MSG , "ERROR when sending Fix Message : %1%" ) ;

// General problems
DEFINE_MSG(9000, CANNOT_CREATE_FILE, "Error When Creating File %1%" );
