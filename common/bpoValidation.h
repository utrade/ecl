/*******************************************************************************
* Date      | Author | Notes                                                   *
* 18 Nov 13 | Jovito | Task #1979 : DATAFEEDER LAYER FOR MONEYUTRADE AND UTRADE*
*******************************************************************************/

#ifndef UT_BPO_VALIDATION_H
#define UT_BPO_VALIDATION_H

#include <boost/program_options.hpp>

namespace UT
{
  class BpoValidation 
  {
    public :
    static bool isValid( 
        const boost::program_options::options_description &options,
        const boost::program_options::variables_map &vm,
        const std::string &configFile,
        const std::string &module ) ;
  };
}
#endif // UT_BPO_VALIDATION_H
