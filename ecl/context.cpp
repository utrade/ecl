#include "context.h"
#include "omsHandler.h"

#include "../common/constants.h"

#include "../common/errorMessages.h"
#include "../common/bpoValidation.h"

namespace UT { namespace ECL
{
  Context::Context() 
    : _cmdLineOptions( "Command Line Options" ),
    _config( "Configuration" )
  {
    DEBUG_1( "Adding Generic options" ) ;
    /******************************************************************
     * Generic Options                                                *
     ******************************************************************/
    bpo::options_description genericOptions("Generic options");
    genericOptions.add_options()
      ("version,v", "print version string")
      ("help,h", "produce help message")
      ("config,c",
       bpo::value<std::string>(&_configFile)->default_value("utrade.conf"),
       "configuration file.")
      ;

    DEBUG_1( "Adding Ecl Specific options" ) ;
    /******************************************************************
     * ECL Specific Options                                            *
     ******************************************************************/
    _config.add_options()
      ( "ECL.settings_file", 
        bpo::value<std::string>(&_eclOmsSettingsFile), 
        "Settings file to configure ECL" ) 
      ( "ECL.no_of_threads",
        bpo::value< size_t > ( &_noOfThreads ),
        "Number of threads to use in ECL " ) ;

    /******************************************************************
     * PLUS Specific Options                                           *
     ******************************************************************/
#if defined(WITH_PLUS_FIX44)
    DEBUG_1( "Adding Plus Specific Options" ) ;
    _config.add_options()
      ("ECL.plus_settings", 
       bpo::value<std::string>(&_plusSettingsFile), 
       "FIX Settings file for PLUS. Leave blank to deactivate") ;
#endif 

    /******************************************************************
     * EsmNse Specific Options                                           *
     ******************************************************************/
#if defined(WITH_ESMNSE_FIX42)
    DEBUG_1( "Adding EsmNse Specific Options" ) ;
    _config.add_options()
      ("ECL.esmnse_settings", 
       bpo::value<std::string>(&_esmNseSettingsFile), 
       "FIX Settings file for ESMNSE. Leave blank to deactivate") ;
#endif 

    _cmdLineOptions.add( genericOptions ).add( _config );
  }

  bool Context::init( int argc, char *argv[] ) 
  {
    try
    {
      if( !readConfig( argc, argv ) )
      {
        DEBUG_1( "Error in config file" ) ;
        return false ;
      }

      return initAdaptors() ;
    }
    catch( std::exception &e )
    {
      ERROR_2( ERROR_DURING_CONFIGURATION, "ECL", e.what() ) ;
      return false ;
    }
  }

  bool Context::readConfig( int argc, char *argv[] ) 
  {
    DEBUG_1( "Reading Config File" ) 
    try 
    {
      store( bpo::command_line_parser( argc, argv ).
          options( _cmdLineOptions ).run(), _variablesMap );

      notify( _variablesMap );

      if(  _variablesMap .count("help") )
      {
        std::cout << _cmdLineOptions << "\n";
        return false;
      }

      if ( _variablesMap .count("version")) {
        std::cout << "uTrade ECL version " VERSION_STRING "\n";
        return false;
      }

      std::ifstream ifs( _configFile.c_str() );

      if (ifs) 
      {
        store( bpo::parse_config_file( ifs, _config, true),  _variablesMap );
        notify( _variablesMap );
      }
      else 
      {
        ERROR_2( CONFIG_ERROR_FILE_MISSING, "ECL", _configFile ) ;
        return false; 
      }

    }
    catch( boost::program_options::error &e) 
    {
      ERROR_3( CONFIG_ERROR_BAD_DATA, _configFile, "ECL", e.what() ) ;
      return false;
    }
    catch(std::exception& e) 
    {
      ERROR_2( CONFIG_ERROR_INI_PARSE, "ECL", e.what() ) ;
      return false;
    }

    if( ! UT::BpoValidation::isValid( 
          _config,
          _variablesMap,
          _configFile,
          "ECL" ) )
    {
      return false ;
    }

    return true ;
  }

  bool Context::initAdaptors() 
  {
    bool status = true ;

    _eclOmsSettings.reset( new FIX::SessionSettings( _eclOmsSettingsFile ) ) ;
    _eclOmsStoreFactory.reset( new FIX::FileStoreFactory( *_eclOmsSettings ) ) ;

    status = status & OmsHandler::getInstance().reset( _eclOmsSettingsFile ) ;

#ifdef NDEBUG
    try
    {
      DEBUG_1( "Init OMS Adapter" ) ;
      _eclOmsAcceptor = new FIX::ThreadedSocketAcceptor( 
          OmsHandler::getInstance(), 
          *_eclOmsStoreFactory, 
          *_eclOmsSettingsFile 
          );
    } 
    catch( std::exception &e ) {
      ERROR_2( ERROR_DURING_CONFIGURATION, "ECL-OMS-Acceptor", e.what() ) ;
      status = false ;
    }
#else
    try
    {
      DEBUG_1( "Init OMS Adapter" ) ;
      _eclOmsLogFactory.reset( 
          new FIX::ScreenLogFactory( _eclOmsSettingsFile ) );

      _eclOmsAcceptor.reset( new FIX::ThreadedSocketAcceptor( 
          OmsHandler::getInstance(), 
          *_eclOmsStoreFactory, 
          *_eclOmsSettings, 
          *_eclOmsLogFactory 
          ) );
    } 
    catch( std::exception &e ) {
      ERROR_2( ERROR_DURING_CONFIGURATION, "ECL-OMS-Acceptor", e.what() ) ;
      status = false ;
    }
#endif


#if defined(WITH_PLUS_FIX44)
    try
    {
      DEBUG_1( "Init Plus Adapter" ) ;
      if(  _variablesMap .count( "ECL.plus_settings" ) == 0 )
      {
        ERROR_3( CONFIG_ERROR_PTREE_KEY_MISSING, 
            UT::MARKET_ID_PLUS, 
            "ECL", 
            "plus_settings" 
            ) ;
        status = false ;
      }
      else if( _plusSettingsFile == "" )
      {
        ERROR_2( CONFIG_ERROR_FILE_MISSING, "ECL", _plusSettingsFile ) ;
        status = false ;
      }

      if( status )
      {
        DEBUG_1( "Creating Plus Objects" ) ;
        PlusAdapter::getInstance().reset( _plusSettingsFile ) ;

        _plusSettings.reset( new FIX::SessionSettings( _plusSettingsFile )) ;
        _plusStoreFactory.reset( new FIX::FileStoreFactory( *_plusSettings ) );

        _plusInitiator.reset( new FIX::SocketInitiator( 
            PlusAdapter::getInstance(), *_plusStoreFactory, *_plusSettings ) ) ;
      }
    } 
    catch( std::exception &e ) {
      ERROR_2( ERROR_DURING_CONFIGURATION, "ECL-PLUS-Initiator", e.what() ) ;
      status = false ;
    }

#endif

#if defined(WITH_ESMNSE_FIX42)
    try
    {
      DEBUG_1( "Init EsmNse Adapter" ) ;
      if(  _variablesMap .count( "ECL.esmnse_settings" ) == 0 )
      {
        ERROR_3( CONFIG_ERROR_PTREE_KEY_MISSING, 
            UT::MARKET_ID_ESM_NSE, 
            "ECL", 
            "esmnse_settings" 
            ) ;
        status = false ;
      }
      else if( _esmNseSettingsFile  == "" )
      {
        ERROR_2( CONFIG_ERROR_FILE_MISSING, "ECL", _esmNseSettingsFile ) ;
        status = false ;
      }

      if( status )
      {
        DEBUG_1( "Creating EsmNse Objects" ) ;
        EsmNseAdapter::getInstance().reset( _esmNseSettingsFile ) ;
        _esmNseSettings.reset( new FIX::SessionSettings( _esmNseSettingsFile ));

        _esmNseLogFactory.reset( 
            new FIX::ScreenLogFactory( _esmNseSettingsFile ) );

        _esmNseStoreFactory.reset( 
            new FIX::FileStoreFactory( *_esmNseSettings ) );

        _esmNseInitiator.reset( new FIX::SocketInitiator( 
            EsmNseAdapter::getInstance(), 
            *_esmNseStoreFactory, 
            *_esmNseSettings,
            *_esmNseLogFactory
            ) ) ;
      }
    } 
    catch( std::exception &e ) {
      ERROR_2( ERROR_DURING_CONFIGURATION, "ECL-ESMNSE-Initiator", e.what() ) ;
      status = false ;
    }

#endif

    DEBUG_2( "Returning ", status ) ;
    return status ;
  }

  bool Context::start() 
  {
    _eclOmsAcceptor->start();

#if defined(WITH_PLUS_FIX44)
    DEBUG_1( "Starting the Plus Initiator" ) ;
    _plusInitiator->start() ;
#endif

#if defined(WITH_ESMNSE_FIX42)
    DEBUG_1( "Starting the EsmNse Initiator" ) ;
    _esmNseInitiator->start() ;
#endif

    return true ;
  }

  bool Context::stop() 
  {
    if( _eclOmsAcceptor )
      _eclOmsAcceptor->stop() ;

#if defined(WITH_PLUS_FIX44)
    _plusInitiator->stop() ;
#endif

#if defined(WITH_ESMNSE_FIX42)
    _esmNseInitiator->stop() ;
#endif

    return true ;
  }
}}
