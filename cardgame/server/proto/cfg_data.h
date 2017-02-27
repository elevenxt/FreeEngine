#ifndef _CFG_DATA_
#define _CFG_DATA_
class cfg_miselite{
   public: class data{
       public: virtual int get_id() = 0;
       public: virtual int get_heros1() = 0;
       public: virtual int get_heros2() = 0;
       public: virtual int get_heros3() = 0;
       public: virtual int get_heros4() = 0;
       public: virtual int get_heros5() = 0;
       public: virtual int get_heros6() = 0;
       public: virtual const char* get_des() = 0;
   };
   public: virtual cfg_miselite::data* get(int key) = 0;
   public: typedef void(*ForEach)(data&);
   public: virtual void forEach(ForEach cb) = 0;
};
class cfg_misnormal{
   public: class data{
       public: virtual int get_id() = 0;
       public: virtual int get_heros1() = 0;
       public: virtual int get_heros2() = 0;
       public: virtual int get_heros3() = 0;
       public: virtual int get_heros4() = 0;
       public: virtual int get_heros5() = 0;
       public: virtual int get_heros6() = 0;
       public: virtual const char* get_des() = 0;
   };
   public: virtual cfg_misnormal::data* get(int key) = 0;
   public: typedef void(*ForEach)(data&);
   public: virtual void forEach(ForEach cb) = 0;
};
class cfg_mishero{
   public: class data{
       public: virtual int get_id() = 0;
       public: virtual int get_heros1() = 0;
       public: virtual int get_heros2() = 0;
       public: virtual int get_heros3() = 0;
       public: virtual int get_heros4() = 0;
       public: virtual int get_heros5() = 0;
       public: virtual int get_heros6() = 0;
       public: virtual const char* get_des() = 0;
   };
   public: virtual cfg_mishero::data* get(int key) = 0;
   public: typedef void(*ForEach)(data&);
   public: virtual void forEach(ForEach cb) = 0;
};
class cfg_heros{
   public: class data{
       public: virtual int get_id() = 0;
       public: virtual const char* get_name() = 0;
       public: virtual int get_atk() = 0;
       public: virtual int get_hp() = 0;
       public: virtual int get_up() = 0;
       public: virtual const char* get_des() = 0;
   };
   public: virtual cfg_heros::data* get(int key) = 0;
   public: typedef void(*ForEach)(data&);
   public: virtual void forEach(ForEach cb) = 0;
};
class cfg_mgr{
   public: virtual cfg_miselite& get_cfg_miselite() = 0;
   public: virtual cfg_misnormal& get_cfg_misnormal() = 0;
   public: virtual cfg_mishero& get_cfg_mishero() = 0;
   public: virtual cfg_heros& get_cfg_heros() = 0;
};
#endif
