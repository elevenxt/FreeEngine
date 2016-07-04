/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#ifndef _UTS_VAR_H_
#define _UTS_VAR_H_

#include <cinttypes>
#include <vector>
#include <map>

namespace ff
{
	enum VarType
	{
		VT_UNKNOWN,
		VT_INT,
		VT_STRING,
		VT_POINTER,
		VT_VECTOR,
		VT_MAP,
	};

	struct var
	{
		int8_t type;
		int8_t pad1;
		uint16_t cb;
		int32_t pad2;

		union
		{
			int64_t n;
			std::string*	str;
			void* ptr;
			std::vector<var*>*	vec;
			std::map<std::string, var*>* kv;
		} val;
	};

	class varopts
	{
	public:
		static var* create();
		static void free(var* v);

		static void init(var* v);
		static void uninit(var* v);

		static void set_int(var* v, int64_t n);
		static void set_str(var* v, const std::string& s);
		static void set_ptr(var* v, void* p);
		static void set_var(var* v, const var* p);
		static void set_map(var* v);
		static void set_vec(var* v);
		// vec²Ù×÷
		static bool push_back(var* v, var* p);
		static bool erase(var* v, int32_t key);
		static bool set(var* v, int32_t key, const var* p);
		static var* get_vec(var* v, int key);
		// map²Ù×÷
		static bool erase(var* v, const std::string& key);
		static bool set(var* v, const std::string& key, const var* p);		
		static void copyvar(var* dst, const var* src);
		static var* get_map(var* v, const char* key);		

		static var* create_int(int64_t v);
		static var* create_str(const char* v);
		static var* create_ptr(void* v);
		static var* create_vec();
		static var* create_map();
	};	
}

#endif