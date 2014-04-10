/*******************************************************************************
* Date      | Author | Notes                                                   *
* 18 Nov 13 | Jovito | Task #1979 : DATAFEEDER LAYER FOR MONEYUTRADE AND UTRADE*
*******************************************************************************/

#include "bpoValidation.h"

#include "errorMessages.h"

namespace UT
{
  bool BpoValidation:: isValid( 
        const boost::program_options::options_description &options,
        const boost::program_options::variables_map &vm,
        const std::string &configFile,
        const std::string &module ) 
  {
    namespace bpo = boost::program_options ;

    bool validationSuccessful = true ;

    const std::vector< boost::shared_ptr<bpo::option_description> >& myoptions
      = options.options() ;

    for( int i = myoptions.size() - 1; i >= 0 ; i-- )
    {
      if( vm.count( myoptions[ i ]->long_name() ) == 0 )
      {
        ERROR_3( CONFIG_ERROR_KEY_MISSING, 
                 configFile, 
                 module,
                 myoptions[ i ]->long_name() ) ;

        // options [ i ]->description() -- Text
        validationSuccessful = false ;
      }
    }

    return validationSuccessful ;
  }
}
