#ifndef UT_ECL_CONTEXT_H
#define UT_ECL_CONTEXT_H

#include <boost/program_options.hpp>
#include <boost/scoped_ptr.hpp>

#include <quickfix/SessionSettings.h>
#include <quickfix/FileStore.h>
#include <quickfix/Log.h>
#include <quickfix/SocketInitiator.h>
#include <quickfix/ThreadedSocketAcceptor.h>

#include "adapters_fwd.h"

namespace UT { namespace ECL
{
  namespace bpo = boost::program_options ;
  class Context
  {
    public :
      /**
       * @brief Default Constructor.
       *   Initializes all the boost options that have to be read.
       * @param  
       * @return  
       */
      Context() ;

      /**
       * @brief Init the application with the arguments passed.
       * @param argv : count of arguments.
       * @param argc : actual arguments
       * @return true if init was successful.
       *         false otherwise.
       */
      bool init( int argv, char *argc[] ) ;

      /**
       * @brief Read the config file and save the variables.
       * @param argv : count of arguments.
       * @param argc : actual arguments
       * @return true if init was successful.
       *         false otherwise.
       */
      bool readConfig( int argv, char *argc[] ) ;

      /**
       * @brief Init the adaptors that will convert to and from
       * @return true if the adaptors were successfuly initialized.
       *         false if an error was faced during init.
       */
      bool initAdaptors() ;

      /**
       * @brief Start all the adapters.
       */
      bool start() ;

      /**
       * @brief Stop all the adapters.
       */
      bool stop() ;

    private :
      bpo::options_description _cmdLineOptions ;
      bpo::options_description _config ;
      bpo::variables_map _variablesMap ;

      std::string _configFile ;
      size_t _noOfThreads ;

      std::string _eclOmsSettingsFile ;

      boost::scoped_ptr< FIX::SessionSettings > _eclOmsSettings ;
      boost::scoped_ptr< FIX::FileStoreFactory > _eclOmsStoreFactory ;
      boost::scoped_ptr< FIX::ScreenLogFactory > _eclOmsLogFactory ;
      boost::scoped_ptr< FIX::ThreadedSocketAcceptor > _eclOmsAcceptor ;

#if defined(WITH_PLUS_FIX44)
      std::string _plusSettingsFile ;

      boost::scoped_ptr< FIX::SessionSettings > _plusSettings ;
      boost::scoped_ptr< FIX::FileStoreFactory > _plusStoreFactory ;
      boost::scoped_ptr< FIX::ScreenLogFactory > _plusLogFactory ;
      boost::scoped_ptr< FIX::SocketInitiator > _plusInitiator ;
#endif

#if defined(WITH_ESMNSE_FIX42)
      std::string _esmNseSettingsFile ;

      boost::scoped_ptr< FIX::SessionSettings > _esmNseSettings ;
      boost::scoped_ptr< FIX::FileStoreFactory > _esmNseStoreFactory ;
      boost::scoped_ptr< FIX::ScreenLogFactory > _esmNseLogFactory ;
      boost::scoped_ptr< FIX::SocketInitiator > _esmNseInitiator ;
#endif

  };
}}
#endif //  UT_ECL_CONTEXT_H
