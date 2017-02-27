#ifndef _CFG_DATA_IMPL_
#define _CFG_DATA_IMPL_
#include <map>
#include <string>
#include <vector>
#include "ValueOpt.h"
#include "cfg_data.h"
class cfg_miselite_impl : public cfg_miselite{
   public: static cfg_miselite_impl& instance(){static cfg_miselite_impl ins;return ins;}
   public: class data : public cfg_miselite::data{
       public: virtual int get_id(){return mid;};
       public: int mid;
       public: virtual int get_heros1(){return mheros1;};
       public: int mheros1;
       public: virtual int get_heros2(){return mheros2;};
       public: int mheros2;
       public: virtual int get_heros3(){return mheros3;};
       public: int mheros3;
       public: virtual int get_heros4(){return mheros4;};
       public: int mheros4;
       public: virtual int get_heros5(){return mheros5;};
       public: int mheros5;
       public: virtual int get_heros6(){return mheros6;};
       public: int mheros6;
       public: virtual const char* get_des(){return mdes.c_str();};
       public: std::string mdes;
   };
   public: virtual cfg_miselite::data* get(int key){;
       return &mMapData[key];
    }
   public: virtual void forEach(ForEach cb){;
   for(auto kv : mMapData){cb(kv.second);}
   }
   public: static bool doLoad(std::vector<std::vector<std::string>> content){
       if(instance().mNewLoadedData != 0){return false;}
       std::map<int, data>* mapData = new std::map<int, data>();
       for (std::vector<std::string>& line : content){
           if(line.size() != 8){delete mapData;return false;}
           data _d;
           _d.mid = (int)ff::ValueOpt::convert<float>(line[0]);
           _d.mheros1 = (int)ff::ValueOpt::convert<float>(line[1]);
           _d.mheros2 = (int)ff::ValueOpt::convert<float>(line[2]);
           _d.mheros3 = (int)ff::ValueOpt::convert<float>(line[3]);
           _d.mheros4 = (int)ff::ValueOpt::convert<float>(line[4]);
           _d.mheros5 = (int)ff::ValueOpt::convert<float>(line[5]);
           _d.mheros6 = (int)ff::ValueOpt::convert<float>(line[6]);
           _d.mdes = line[7];
           int _k = _d.mid;
           (*mapData)[_k] = _d;
       }
       instance().mNewLoadedData = mapData;
       return true;
   }
   public: void tryChangeCfg(){
       if(mNewLoadedData == 0){return;}
       mMapData = *mNewLoadedData;
       delete mNewLoadedData;
       mNewLoadedData = 0;
   }
   private: std::map<int, data> mMapData;
   private: std::map<int, data>* mNewLoadedData = 0;
};
class cfg_misnormal_impl : public cfg_misnormal{
   public: static cfg_misnormal_impl& instance(){static cfg_misnormal_impl ins;return ins;}
   public: class data : public cfg_misnormal::data{
       public: virtual int get_id(){return mid;};
       public: int mid;
       public: virtual int get_heros1(){return mheros1;};
       public: int mheros1;
       public: virtual int get_heros2(){return mheros2;};
       public: int mheros2;
       public: virtual int get_heros3(){return mheros3;};
       public: int mheros3;
       public: virtual int get_heros4(){return mheros4;};
       public: int mheros4;
       public: virtual int get_heros5(){return mheros5;};
       public: int mheros5;
       public: virtual int get_heros6(){return mheros6;};
       public: int mheros6;
       public: virtual const char* get_des(){return mdes.c_str();};
       public: std::string mdes;
   };
   public: virtual cfg_misnormal::data* get(int key){;
       return &mMapData[key];
    }
   public: virtual void forEach(ForEach cb){;
   for(auto kv : mMapData){cb(kv.second);}
   }
   public: static bool doLoad(std::vector<std::vector<std::string>> content){
       if(instance().mNewLoadedData != 0){return false;}
       std::map<int, data>* mapData = new std::map<int, data>();
       for (std::vector<std::string>& line : content){
           if(line.size() != 8){delete mapData;return false;}
           data _d;
           _d.mid = (int)ff::ValueOpt::convert<float>(line[0]);
           _d.mheros1 = (int)ff::ValueOpt::convert<float>(line[1]);
           _d.mheros2 = (int)ff::ValueOpt::convert<float>(line[2]);
           _d.mheros3 = (int)ff::ValueOpt::convert<float>(line[3]);
           _d.mheros4 = (int)ff::ValueOpt::convert<float>(line[4]);
           _d.mheros5 = (int)ff::ValueOpt::convert<float>(line[5]);
           _d.mheros6 = (int)ff::ValueOpt::convert<float>(line[6]);
           _d.mdes = line[7];
           int _k = _d.mid;
           (*mapData)[_k] = _d;
       }
       instance().mNewLoadedData = mapData;
       return true;
   }
   public: void tryChangeCfg(){
       if(mNewLoadedData == 0){return;}
       mMapData = *mNewLoadedData;
       delete mNewLoadedData;
       mNewLoadedData = 0;
   }
   private: std::map<int, data> mMapData;
   private: std::map<int, data>* mNewLoadedData = 0;
};
class cfg_mishero_impl : public cfg_mishero{
   public: static cfg_mishero_impl& instance(){static cfg_mishero_impl ins;return ins;}
   public: class data : public cfg_mishero::data{
       public: virtual int get_id(){return mid;};
       public: int mid;
       public: virtual int get_heros1(){return mheros1;};
       public: int mheros1;
       public: virtual int get_heros2(){return mheros2;};
       public: int mheros2;
       public: virtual int get_heros3(){return mheros3;};
       public: int mheros3;
       public: virtual int get_heros4(){return mheros4;};
       public: int mheros4;
       public: virtual int get_heros5(){return mheros5;};
       public: int mheros5;
       public: virtual int get_heros6(){return mheros6;};
       public: int mheros6;
       public: virtual const char* get_des(){return mdes.c_str();};
       public: std::string mdes;
   };
   public: virtual cfg_mishero::data* get(int key){;
       return &mMapData[key];
    }
   public: virtual void forEach(ForEach cb){;
   for(auto kv : mMapData){cb(kv.second);}
   }
   public: static bool doLoad(std::vector<std::vector<std::string>> content){
       if(instance().mNewLoadedData != 0){return false;}
       std::map<int, data>* mapData = new std::map<int, data>();
       for (std::vector<std::string>& line : content){
           if(line.size() != 8){delete mapData;return false;}
           data _d;
           _d.mid = (int)ff::ValueOpt::convert<float>(line[0]);
           _d.mheros1 = (int)ff::ValueOpt::convert<float>(line[1]);
           _d.mheros2 = (int)ff::ValueOpt::convert<float>(line[2]);
           _d.mheros3 = (int)ff::ValueOpt::convert<float>(line[3]);
           _d.mheros4 = (int)ff::ValueOpt::convert<float>(line[4]);
           _d.mheros5 = (int)ff::ValueOpt::convert<float>(line[5]);
           _d.mheros6 = (int)ff::ValueOpt::convert<float>(line[6]);
           _d.mdes = line[7];
           int _k = _d.mid;
           (*mapData)[_k] = _d;
       }
       instance().mNewLoadedData = mapData;
       return true;
   }
   public: void tryChangeCfg(){
       if(mNewLoadedData == 0){return;}
       mMapData = *mNewLoadedData;
       delete mNewLoadedData;
       mNewLoadedData = 0;
   }
   private: std::map<int, data> mMapData;
   private: std::map<int, data>* mNewLoadedData = 0;
};
class cfg_heros_impl : public cfg_heros{
   public: static cfg_heros_impl& instance(){static cfg_heros_impl ins;return ins;}
   public: class data : public cfg_heros::data{
       public: virtual int get_id(){return mid;};
       public: int mid;
       public: virtual const char* get_name(){return mname.c_str();};
       public: std::string mname;
       public: virtual int get_atk(){return matk;};
       public: int matk;
       public: virtual int get_hp(){return mhp;};
       public: int mhp;
       public: virtual int get_up(){return mup;};
       public: int mup;
       public: virtual const char* get_des(){return mdes.c_str();};
       public: std::string mdes;
   };
   public: virtual cfg_heros::data* get(int key){;
       return &mMapData[key];
    }
   public: virtual void forEach(ForEach cb){;
   for(auto kv : mMapData){cb(kv.second);}
   }
   public: static bool doLoad(std::vector<std::vector<std::string>> content){
       if(instance().mNewLoadedData != 0){return false;}
       std::map<int, data>* mapData = new std::map<int, data>();
       for (std::vector<std::string>& line : content){
           if(line.size() != 6){delete mapData;return false;}
           data _d;
           _d.mid = (int)ff::ValueOpt::convert<float>(line[0]);
           _d.mname = line[1];
           _d.matk = (int)ff::ValueOpt::convert<float>(line[2]);
           _d.mhp = (int)ff::ValueOpt::convert<float>(line[3]);
           _d.mup = (int)ff::ValueOpt::convert<float>(line[4]);
           _d.mdes = line[5];
           int _k = _d.mid;
           (*mapData)[_k] = _d;
       }
       instance().mNewLoadedData = mapData;
       return true;
   }
   public: void tryChangeCfg(){
       if(mNewLoadedData == 0){return;}
       mMapData = *mNewLoadedData;
       delete mNewLoadedData;
       mNewLoadedData = 0;
   }
   private: std::map<int, data> mMapData;
   private: std::map<int, data>* mNewLoadedData = 0;
};
class cfg_mgr_impl : public cfg_mgr{
   public: static cfg_mgr_impl& instance(){static cfg_mgr_impl ins;return ins;}
   public: virtual cfg_miselite& get_cfg_miselite(){
       return cfg_miselite_impl::instance();
   }
   public: virtual cfg_misnormal& get_cfg_misnormal(){
       return cfg_misnormal_impl::instance();
   }
   public: virtual cfg_mishero& get_cfg_mishero(){
       return cfg_mishero_impl::instance();
   }
   public: virtual cfg_heros& get_cfg_heros(){
       return cfg_heros_impl::instance();
   }
   public: void trychangecfg(){
   cfg_miselite_impl::instance().tryChangeCfg();
   cfg_misnormal_impl::instance().tryChangeCfg();
   cfg_mishero_impl::instance().tryChangeCfg();
   cfg_heros_impl::instance().tryChangeCfg();
   }
};
#endif
