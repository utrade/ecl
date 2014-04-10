/*******************************************************************************
* Date      | Author | Notes                                                   *
* 03 Oct 13 | Jovito | Request #1646 : Updated CDS Version to 30500.           *
* 18 Nov 13 | Jovito | Task #1979 : DATAFEEDER LAYER FOR MONEYUTRADE AND UTRADE*
*******************************************************************************/

#ifndef UT_CONSTANTS_H
#define UT_CONSTANTS_H

#ifndef FRONTEND_ONLY
#include "../config.h"
#endif

#include "types.h"

namespace UT
{
  const int MAX_LENGTH_FOR_TCP_DATA = 1024*16 ;
  const int MAX_NO_OF_PACKETS = 10 ;
  const int MAX_LENGTH_FOR_PUBLISH = 1024 ;

  /******************************************************************
  * Markets Available                                               *
  ******************************************************************/
  const char MARKET_ID_ESM_NSE[] = "ESMNSE" ;
  const char MARKET_ID_ESM_BSE[] = "ESMBSE" ;
  const char MARKET_ID_BSE[] = "BSE" ;
  const char MARKET_ID_BSE_CD[] = "BSECDS" ;
  const char MARKET_ID_NSE[] = "NSE" ;
  const char MARKET_ID_MCX_COM[] = "MCX" ;
  const char MARKET_ID_MCX_SX[] = "MCXSX" ;
  const char MARKET_ID_NSE_FO[] = "NSEFO" ;
  const char MARKET_ID_NSE_CM[] = "NSECM" ;
  const char MARKET_ID_NSE_CDS[] = "NSECDS" ;
  const char MARKET_ID_PLUS[] = "GMEX" ;
  const char MARKET_ID_BSE_OMB[] = "BSE" ;
  const char MARKET_ID_ESM_MCX[] = "ESMMCX" ;
  const char MARKET_ID_ESM[] = "ESM" ;
  const char MARKET_ID_MAREX[] = "MAREX" ;
  const char MARKET_ID_MAREX_PREFIX[] ="M-" ;

  /******************************************************************
  * Price multipliers per market                                    *
  *  We send prices in Rupees.                                      *
  *   In some exchanges they have to be sent as paise               *
  *   This will be used for the conversion                          *
  ******************************************************************/
  const int PRICE_MULTIPLIER_NSE = 100 ;
  const int PRICE_MULTIPLIER_NSE_CDS = 10000000 ;
  const int PRICE_MULTIPLIER_BSE = 100 ;
  const int PRICE_MULTIPLIER_BSE_CDS = 10000 ;
  const int PRICE_MULTIPLIER_ESMNSE = 100 ;
  const int PRICE_MULTIPLIER_ESMBSE = 100 ;
  const int PRICE_MULTIPLIER_MCX = 100 ;
  //const int PRICE_MULTIPLIER_MAREX = 100.0 ;

  /******************************************************************
  * Configuration                                                   *
  ******************************************************************/
  const char DEFAULT_CONFIG_FILE[] = "utrade.conf" ;
  const char SERVER[] = "server" ;
  const char PORT[] = "port" ;
  const char RETRY_INTERVAL[] = "retry_interval" ;
  const char KEEP_ALIVE_INTERVAL[] = "keep_alive_interval" ;
  const char BROKER_ID[] = "broker_id" ;
  const char TRADER_ID[] = "trader_id" ;
  const char PASSWORD[] = "password" ;
  const char CHANGE_PASSWORD[] = "change_password" ;
  const char NEW_PASSWORD[] = "new_password" ;
  const char DOWNLOAD_OLD_ORDERS[] = "download_old_orders" ;
  const char APPLICATION_LOOKUP_IP[] = "application_lookup_ip" ;
  const char APPLICATION_LOOKUP_PORT[] = "application_lookup_port" ;
  const char PRIVATE_TOKEN_KEY[] = "private_token_key" ;
  const char BSE_MAX_PENDING_ORDERS[] = "throughput" ;
  const char EXCHANGE_VERSION[] = "version" ;

  /******************************************************************
  * FIX Constants not defined by them                               *
  ******************************************************************/
  const char FIX_ACCEPTOR[] = "acceptor" ;
  const char FIX_INITIATOR[] = "initiator" ;
  const char FIX_MARKET_DESTINATION[] = "MarketDestination" ;

  /******************************************************************
  * Market depth                                                    *
  ******************************************************************/
  const int MARKET_DEPTH = 5 ;

  /******************************************************************
  * Time Conversions                                                *
  ******************************************************************/

  enum
  {
    SECONDS_PER_DAY = 86400,
    SECONDS_PER_HOUR = 3600,
    SECONDS_PER_MINUTE = 60
  };

  const int DAYS_IN_MONTH[] = { 
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 } ;

  const int DAYS_BEFORE_MONTH[] = { 
    0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 } ;

  const LONG TIMEZONE_OFFSET_UTC_TO_IST = 19800 ;
  
  /******************************************************************
  * All configuration settings to be read from configuration file   *
  ******************************************************************/

  namespace THRIFT
  {
    const char THRIFT_SERVER[] = "THRIFT.host" ;
    const char THRIFT_SERVER_TEXT[] = "IP/Host of Thrift API" ;

    const char INTERNAL_PORT[] = "THRIFT.internal_port" ;
    const char INTERNAL_PORT_TEXT[] = "Port For Thrift API" ;

    const char EXTERNAL_PORT[] = "THRIFT.external_port" ;
    const char INTERNAL_THREADS[] = "THRIFT.internal_no_of_threads" ;
    const char EXTERNAL_THREADS[] = "THRIFT.external_no_of_threads" ;

  }

  namespace MDL
  {
    const char SUBSCRIPTION_PORT[] = "MDL.subscription_port" ;
    //const char MDL_IP[] = "MCL.mdl_ip" ;
    const char FIRST_FETCH_PORT[] = "MDL.first_fetch_port" ;
    const char FIX_SETTINGS_FILE[] = "MDL.fix_settings_file" ;
  }

  namespace MCL
  {
    const char NSE_INTERFACE_IP[] = "MCL.nse_interface_ip" ;
    const char NSE_INTERFACE_IP_TEXT[] 
      = "Interface IP of the NSE multicast data" ;

    const char NSE_MULTICAST_ADDR[] = "MCL.nse_multicast_address" ;
    const char NSE_MULTICAST_ADDR_TEXT[] 
      = "Multicast Address of NSE multicast data" ;

    const char NSECM_MULTICAST_PORT[] = "MCL.nsecm_multicast_port" ;
    const char NSECM_MULTICAST_PORT_TEXT[] 
      = "Multicast Port of NSE CM multicast data" ;

    const char NSECD_MULTICAST_PORT[] = "MCL.nsecd_multicast_port" ;
    const char NSECD_MULTICAST_PORT_TEXT[] 
      = "Multicast Port of NSE CD multicast data" ;

    const char NSEFO_MULTICAST_PORT[] = "MCL.nsefo_multicast_port" ;
    const char NSEFO_MULTICAST_PORT_TEXT[] 
      = "Multicast Port of NSE FO multicast data" ;

    const char BSE_PORT[] = "MCL.bse_port" ;

    const char ESMNSE_PORT[] = "MCL.esmnse_port" ;

    // const char BROADCAST_SERVER[] = "MCL.broadcast_server" ;
    // const char BROADCAST_PORT[] = "MCL.broadcast_port" ;

    const char PLUS_SETTINGS[] = "MCL.plus_settings" ;

    const char MCX_MULTICAST_INTERFACE_IP[] = "MCL.mcx_multicast_interface_ip" ;
    const char MCX_MULTICAST_ADDR[] = "MCL.mcx_multicast_server" ;
    const char MCX_COM_MULTICAST_PORT[] = "MCL.mcx_com_multicast_port" ;
    const char MCX_SX_MULTICAST_PORT[] = "MCL.mcx_sx_multicast_port" ;

    const char TT_SETTINGS[] = "MCL.tt_mcl_settings" ;
    const char TT_SENDER_ID[] = "MCL.tt_sender_id" ;
    const char TT_TARGET_ID[] = "MCL.tt_target_id" ;

    const char MAREX_SERVER[] = "MCL.marex_server" ;
    const char MAREX_USER_ID[] = "MCL.marex_user_id" ;
    const char MAREX_PASSWORD[] = "MCL.marex_password" ;

    const char USE_UNICAST[] 
      = "MCL.use_unicast" ;
    const char USE_UNICAST_TEXT[] 
      = "'1' if you want to send data over unicast" ;
    const char SEND_TO_UNICAST_ADDRESS[] 
      = "MCL.send_to_udp_address" ;
    const char SEND_TO_UNICAST_ADDRESS_TEXT[] 
      = "Udp Ip on which MCL sends Market Data" ;
    const char SEND_TO_UNICAST_PORT[] 
      = "MCL.send_to_udp_port" ;
    const char SEND_TO_UNICAST_PORT_TEXT[] 
      = "Udp Port on which MCL sends Market Data" ;

    const char SEND_TO_BROADCAST_INTERFACE_IP[] 
      = "MCL.send_to_broadcast_interface_ip" ;
    const char SEND_TO_BROADCAST_INTERFACE_IP_TEXT[] 
      = "Ip of the interface on which MCL sends Market Data" ;
    const char SEND_TO_BROADCAST_PORT[] 
      = "MCL.send_to_broadcast_port" ;
    const char SEND_TO_BROADCAST_PORT_TEXT[] 
      = "Broadcast Udp Port on which MCL sends Market Data";

    const char SEND_TO_MULTICAST_INTERFACE_IP[] 
      = "MCL.send_to_multicast_interface_ip" ;
    const char SEND_TO_MULTICAST_INTERFACE_IP_TEXT[] 
      = "Ip of the interface on which MCL sends Market Data" ;
    const char SEND_TO_MULTICAST_ADDRESS[] 
      = "MCL.send_to_multicast_address" ;
    const char SEND_TO_MULTICAST_ADDRESS_TEXT[] 
      = "Multicast Address e.g. 239.1.2.3 on which MCL sends Market Data" ;
    const char SEND_TO_MULTICAST_PORT[] 
      = "MCL.send_to_multicast_port" ;
    const char SEND_TO_MULTICAST_PORT_TEXT[] = 
      "Multicast Port on which MCL sends Market Data" ;

    const char USE_BROADCAST[] = "MCL.use_broadcast" ;
    const char USE_BROADCAST_TEXT[] 
      = "'1' if you want to send data over broadcast" ;
    const char USE_MULTICAST[] = "MCL.use_multicast" ;
    const char USE_MULTICAST_TEXT[] 
      = "'1' if you want to send data over multicast" ;

    const char NO_OF_THREADS[] = "MCL.no_of_threads" ;
    const char NO_OF_THREADS_TEXT[]
      = "Number of threads MCL should use to process market data" ;
  }

  namespace MARKET_DATA
  {
    const char CHARTS_FOLDER[] = "MarketData.save_folder_charts"; 
    const char CHARTS_FOLDER_TEXT[] 
      = "Save Market Data In This Folder For Charts" ;

    const char FREQUENCY[] = "MarketData.frequency" ;
    const char FREQUENCY_TEXT[] = "Frequency In Seconds For Saving Market Data";

    const char MONEY_UTRADE_FOLDER[] = "MarketData.save_folder_moneyutrade"; 
    const char MONEY_UTRADE_FOLDER_TEXT[] 
      = "Save Market Data In This Folder For MoneyUtrade" ;

  }
}

#endif // UT_CONSTANTS_H
