#ifndef CONNECTION_POOL_H
#define CONNECTION_POOL_H

#include <soci.h>
#include <postgresql/soci-postgresql.h>
#include <memory>

#include <boost-optional.h>
#include <boost/program_options.hpp>

using soci::use;
using soci::into;

namespace UT {

  class ConnectionPool
  {
  public:
    /////////////////////////////////////
    /// initializes the connection pool//
    /// @throws soci::soci_error       //
    /////////////////////////////////////

    static void initialize(int poolSize,
                    const std::string& host,
                    const std::string& port,
                    const std::string& user,
                    const std::string& password,
                    const std::string& dbname)
      throw (soci::soci_error);
    
    static soci::connection_pool& get();

    static bool init( 
        int argc, 
        char* argv[],
        const std::string &configFile,
        boost::program_options::options_description &visible1,
        bool execute = false 
        ) ;

    
  private:
    static std::auto_ptr<soci::connection_pool> _pool;
    static bool _initialized;
    
  };

} // namespace UT

#endif
