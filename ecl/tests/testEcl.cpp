/*******************************************************************************
* Date      | Name   | Description                                             *
* 03 Oct 13 | Jovito | Req #1848 : Test Cases For ECL                          *
*******************************************************************************/

/*******************************************************************************
* This is copied from quickfix/pt.cpp                                          *
*  It had a simple test case and was modified to meet our needs                *
* These are several test cases created and the user can specify                *
*  which test case he wishes to use                                            *
*******************************************************************************/
#undef NDEBUG

#include <iostream>
#include <quickfix/Application.h>
#include <quickfix/FieldConvertors.h>
#include <quickfix/Values.h>
#include <quickfix/FileStore.h>
#include <quickfix/SessionID.h>
#include <quickfix/Session.h>
#include <quickfix/DataDictionary.h>
#include <quickfix/Parser.h>
#include <quickfix/Utility.h>
#include <quickfix/SocketAcceptor.h>
#include <quickfix/SocketInitiator.h>
#include <quickfix/ThreadedSocketAcceptor.h>
#include <quickfix/ThreadedSocketInitiator.h>
#include <quickfix/fix42/Heartbeat.h>
#include <quickfix/fix42/NewOrderSingle.h>
#include <quickfix/fix42/QuoteRequest.h>

#include <boost/program_options.hpp>

#include "report.h"
#include "roundTripTime.h"
#include "placeOrder.h"
#include "../config.h"
#include "../common/errorMessages.h"

int main( int argc, char** argv )
{
  namespace bpo = boost::program_options;
  try
  {
    std::string configFile ;
    std::string omsEclSettings;

    try 
    {
      // only command-line options
      bpo::options_description genericOptions("Generic options");
      genericOptions.add_options()
        ("version,v", "print version string")
        ("help,h", "produce help message")
        ("config,c",
         bpo::value<std::string>(&configFile)->default_value("utrade.conf"),
         "configuration file.")
        ;

      // both on command line and config file options
      bpo::options_description configFileOptions( "Configuration" ) ;
      configFileOptions.add_options()
        ("OMS.ecl_settings",
           bpo::value<std::string>(&omsEclSettings)
             ->default_value("oms-ecl-settings"),
           "OMS-ECL QuickFIX settings file")
        ;

      bpo::options_description cmdLineOptions;
      cmdLineOptions.add(genericOptions).add(configFileOptions);

      bpo::variables_map vm;
      store(bpo::command_line_parser(argc, argv).
          options(cmdLineOptions).run(), vm);
      notify(vm);

      std::ifstream ifs(configFile.c_str());
      if (ifs) 
      {
        store(parse_config_file(ifs, configFileOptions, true), vm);
        notify(vm);
      }
      else 
      {
        std::cout << "Unable to open file: " << configFile 
                  << "\n" << std::endl ;
        return 1 ;
      }

      if (vm.count("help")) 
      {
        std::cout << cmdLineOptions << "\n";
        return 0;
      }

      if (vm.count("version")) 
      {
        std::cout << "uTrade OMS version " VERSION_STRING "\n";
        return 0;
      }

      bool validationSuccessful = true ;

      const std::vector< boost::shared_ptr<bpo::option_description> >& myoptions
        = configFileOptions.options() ;
      for( int i = myoptions.size() - 1; i >= 0 ; i-- )
      {
        if( vm.count( myoptions[ i ]->long_name() ) == 0 )
        {
          ERROR_3( CONFIG_ERROR_KEY_MISSING, configFile,  
                   "ECL_TEST", myoptions[ i ]->long_name()  ) ;
          validationSuccessful = false ;
        }
      }
      if( !validationSuccessful )
      {
        std::cout << "\n\nPress any key to exit ... " << std::endl ;
        std::cin.get() ;
        return 1 ;
      }
    }
    catch(boost::program_options::error &e) 
    {
      std::cout << "Bad Options: " << e.what() << std::endl;
      return 1;
    }
    catch(std::exception& e) 
    {
      std::cout << "Error when configuring : " << e.what() << std::endl ;
      return 1;
    }


    std::string command( "" ) ;

    while ( command != "0" )
    {
      std::cout
        << "\nOptions are : \n"
        << " 1. Place Orders\n"
        << " 2. Round Trip Time \n"
        << " 0. Exit "
        << std::endl;

      getline( std::cin, command ) ;

      if( command == "1" )
      {
        UT::ECL::TESTS::PlaceOrder p( omsEclSettings ) ;
      }
      else if( command == "2" )
      {
        UT::ECL::TESTS::RoundTripTime rtt( omsEclSettings ) ;
      } 
    }
  } catch( std::exception &e ) {
    std::cout << "Error : " << e.what() << std::endl ;
    return 1;
  }

  return 0;
}
