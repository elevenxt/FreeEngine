#ifndef _CFG_LOADER_
#define _CFG_LOADER_
#include <string>
#include <vector>
#include "cfg_data_impl.h"
class cfg_loader{
public: static bool reload(std::string tab, std::vector<std::vector<std::string>> data){
   if(tab == "miselite"){
       return cfg_miselite_impl::instance().doLoad(data);
   }
   if(tab == "misnormal"){
       return cfg_misnormal_impl::instance().doLoad(data);
   }
   if(tab == "mishero"){
       return cfg_mishero_impl::instance().doLoad(data);
   }
   if(tab == "heros"){
       return cfg_heros_impl::instance().doLoad(data);
   }
   return true;
   }
};
#endif
