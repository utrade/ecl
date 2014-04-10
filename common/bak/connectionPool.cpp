#include "connectionPool.h"
#include "errorMessages.h"

#include <fstream>

namespace UT {

  std::auto_ptr<soci::connection_pool> ConnectionPool::_pool;

  bool ConnectionPool::_initialized = false;

  void ConnectionPool::initialize(int poolSize,
                                  const std::string& host,
                                  const std::string& port,
                                  const std::string& user,
                                  const std::string& password,
                                  const std::string& dbname)
    throw (soci::soci_error)
  {
    if (_initialized == true)
    {
      return;
    }

    _pool.reset(new soci::connection_pool(poolSize));

    for (int i = 0; i < poolSize; i++)
    {
      soci::session& sql = _pool->at(i);
      sql.open(soci::postgresql, 
               "host=" + host + " " +
               "port=" + port + " " +
               "user=" + user + " " +
               "password=" + password + " " +
               "dbname=" + dbname);
    }
    
    _initialized = true;
  }

  soci::connection_pool& ConnectionPool::get()
  {
    return *(_pool);
  }

  bool ConnectionPool::init( 
      int argc, 
      char* argv[],
      const std::string &configFile,
      boost::program_options::options_description &visible1,
      bool execute
      )
  {
    try
    {
      std::string dbHost, dbPort, dbName, dbUser, dbPassword;
      int dbPoolSize ;

      try {
        // both on command line and config file options
        boost::program_options::options_description config(
            "Database Configuration ");
        config.add_options()
          ("DB.host",
             boost::program_options::value<std::string>(&dbHost)
              ->default_value("rocky"),
             "Database host")
          ("DB.port",
             boost::program_options::value<std::string>(&dbPort)
               ->default_value("5432"),
             "Database port")
          ("DB.dbname",
             boost::program_options::value<std::string>(&dbName)
               ->default_value("utradedb"),
             "Database name")
          ("DB.user",
             boost::program_options::value<std::string>(&dbUser)
               ->default_value("utrade"),
             "Database user")
          ("DB.password",
             boost::program_options::value<std::string>(&dbPassword)
               ->default_value("password"),
             "Database password")
          ("DB.poolSize",
             boost::program_options::value<int>(&dbPoolSize)->default_value(4),
             "Pool size to use for db connections")
          ;

        visible1.add(config);
        if( !execute ) return true;

        boost::program_options::variables_map vm;
        try
        {
          store( boost::program_options::command_line_parser(argc, argv).  
                 options(config).run(), vm);
        }
        catch(boost::program_options::error &e) {
        }

        notify(vm);

        std::ifstream ifs(configFile.c_str());
        if (ifs) {
          store(parse_config_file(ifs, config, true), vm);
          notify(vm);
        }
        else {
          std::cout << "Unable to open file: " << configFile << "\n"
            << "Using default configuration values"
            << std::endl;
        }

      }
      catch(boost::program_options::error &e) {
        ERROR_1( PROBLEM_DB_SETTINGS, e.what() ) ;
        exit( 1 ) ;
      }
      catch(std::exception& e) {
        ERROR_1( PROBLEM_DB_SETTINGS, e.what() ) ;
        exit( 1 ) ;
      }

      // Initialize Soci Connection pool
      std::cout << "Establishing db Connection " << std::endl ;

      UT::ConnectionPool::initialize( 
          dbPoolSize, dbHost, dbPort, dbUser, dbPassword, dbName);  
    }
    catch( std::exception &e ) {
      ERROR_1( PROBLEM_DB_CONNECTIVITY, e.what() ) ;
      exit( 1 ) ;
    }
    return true;
  }
  
} //namespace UT
