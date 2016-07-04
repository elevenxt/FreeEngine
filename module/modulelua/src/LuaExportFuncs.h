/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/


#ifndef _LUA_EXPORT_FUNCS_
#define _LUA_EXPORT_FUNCS_

#include <functional>
#include <map>
#include <string>

#include "Singleton.h"
#include "lua.hpp"
#include "CallFromLuaTraits.h"
#include "LuaFunc.h"
#include "luaoptutil.h"
#include "StringUtil.h"
#include "base.h"

namespace ff
{
	class FuncBindData
	{
	public:
		virtual int doLuaCall(lua_State* L) = 0;
	};

	template<typename FUNC>
	class _LFCF : public FuncBindData
	{
	public:
		_LFCF(FUNC func)
		{
			mf = func;
		}

		virtual int doLuaCall(lua_State* L)
		{
			using call_traits = call_from_lua_traits<FUNC>;
			LuaFunc::call_from_lua_impl(L, mf, make_index_sequence<call_traits::arg_count>());
			return 1;
		}

	private:
		FUNC mf;
	};

	template<typename C, typename FUNC>
	class _LFMF : public FuncBindData
	{
	public:
		_LFMF(C* c, FUNC func)
		{
			mc = c;
			mf = func;
		}

		virtual int doLuaCall(lua_State* L)
		{
			using call_traits = call_from_lua_traits<FUNC>;
			LuaFunc::call_from_lua_impl_o(L, mc, mf, make_index_sequence<call_traits::arg_count>());
			return 1;
		}

	private:
		C*	 mc;
		FUNC mf;
	};

	////////////////////////////////////////////////////////////////
	// 成员函数调用
	template<typename C, typename FUNC>
	class _MTMF : public FuncBindData
	{
	public:
		_MTMF(FUNC func)
		{
			mf = func;
		}

		virtual int doLuaCall(lua_State* L)
		{
			using call_traits = call_from_lua_traits<FUNC>;
			C* mc = LuaTypeConvert<C*>::from_lua(L, -(int)call_traits::arg_count - 1);
			SYS_VERIFY_RV(mc != 0, 0);
			LuaFunc::call_from_lua_impl_o(L, mc, mf, make_index_sequence<call_traits::arg_count>());
			return 1;
		}

	private:
		FUNC mf;
	};

	// c++函数到lua函数的导出库
	class LuaExportFuncs : public Singleton<LuaExportFuncs>
	{
	private:
		static int FuncEnter(lua_State* L)
		{
			FuncBindData* fbData = (FuncBindData*)(lua_touserdata(L, lua_upvalueindex(1)));
			if (fbData == nullptr)
			{
				lua_pushstring(L, "upval is null");
				lua_error(L);
				return 0;
			}
			return fbData->doLuaCall(L);
		}

	public:
		bool isExist(const std::string& tab)
		{
			return mFuncs.find(tab) != mFuncs.end() || mCFuncs.find(tab) != mCFuncs.end();
		}

		template<typename FUNC>
		bool registerFunc(const std::string& tab, FUNC func)
		{
			if (isExist(tab))
			{
				return false;
			}

			mFuncs[tab] = new _LFCF<FUNC>(func);
			return true;
		}

		bool registerFunc(const std::string& tab, int(*func)(lua_State*))
		{
			if (isExist(tab))
			{
				return false;
			}

			mCFuncs[tab] = func;
			return true;
		}

		template<typename C, typename FUNC>
		bool registerFunc(const std::string& tab, C* c, FUNC func)
		{
			if (isExist(tab))
			{
				return false;
			}

			mFuncs[tab] = new _LFMF<C, FUNC>(c, func);
			return true;
		}

		template<typename C, typename FUNC>
		bool registerMt(const char* tab, const char* name, FUNC func)
		{
			std::map<std::string, FuncBindData*>& data = mMtFuncs[tab];
			if (data.find(name) != data.end())
			{
				return false;
			}

			data[name] = new _MTMF<C, FUNC>(func);
			return true;
		}

		bool bindLua(lua_State* L)
		{
			int32_t ctop = lua_gettop(L);
			for (std::map<std::string, FuncBindData*>::iterator iter = mFuncs.begin();
				iter != mFuncs.end(); ++iter)
			{
				lua_settop(L, ctop);
				
				std::vector<std::string> tables = StringUtil::split(iter->first, ".");
				
				if (tables.size() == 0)
				{
					return false;
				}
				else if (tables.size() == 1)
				{
					lua_getglobal(L, tables[0].c_str());
					if (!lua_isnil(L, -1))
					{
						SYSLOG_ERROR("table [{}] already exist", iter->first);
						return false;
					}
					lua_pop(L, 1);
					lua_pushlightuserdata(L, iter->second);
					lua_pushcclosure(L, FuncEnter, 1);
					lua_setglobal(L, tables[0].c_str());
				}
				else
				{
					lua_getglobal(L, tables[0].c_str());
					if (!lua_istable(L, -1) && !lua_isnil(L, -1))
					{
						SYSLOG_ERROR("table [{}] already exist", iter->first);
						return false;
					}
					if (lua_isnil(L, -1))
					{
						lua_newtable(L);
						lua_pushstring(L, "__newindex");
						lua_pushcfunction(L, invalid_newindex);
						lua_rawset(L, -3);

						lua_pushvalue(L, -1);
						lua_setglobal(L, tables[0].c_str());
					}

					for (int32_t i = 1; i < (int32_t)tables.size() - 1; i++)
					{
						lua_getfield(L, -1, tables[i].c_str());
						if (!lua_istable(L, -1) && !lua_isnil(L, -1))
						{
							SYSLOG_ERROR("table [{}] already exist", iter->first);
							return false;
						}

						if (lua_isnil(L, -1))
						{
							lua_pop(L, 1);
							lua_newtable(L);
							lua_pushstring(L, "__newindex");
							lua_pushcfunction(L, invalid_newindex);
							lua_rawset(L, -3);

							lua_pushvalue(L, -1);
							lua_setfield(L, -3, tables[i].c_str());
						}
					}
					lua_getfield(L, -1, tables.back().c_str());
					if (!lua_isnil(L, -1))
					{
						SYSLOG_ERROR("table [{}] already exist", iter->first);
						return false;
					}
					lua_pop(L, 1);

					lua_pushstring(L, tables.back().c_str());
					lua_pushlightuserdata(L, iter->second);
					lua_pushcclosure(L, FuncEnter, 1);
					lua_rawset(L, -3);
				}				
			}
			
			for (std::map<std::string, lua_CFunction>::iterator iter = mCFuncs.begin();
				iter != mCFuncs.end(); ++iter)
			{
				lua_settop(L, ctop);

				std::vector<std::string> tables = StringUtil::split(iter->first, ".");

				if (tables.size() == 0)
				{
					return false;
				}
				
				lua_getglobal(L, tables[0].c_str());
				if (!lua_istable(L, -1) && !lua_isnil(L, -1))
				{
					SYSLOG_ERROR("table [{}] already exist", iter->first);
					return false;
				}
				if (lua_isnil(L, -1))
				{
					lua_newtable(L);
					lua_pushstring(L, "__newindex");
					lua_pushcfunction(L, invalid_newindex);
					lua_rawset(L, -3);

					lua_pushvalue(L, -1);
					lua_setglobal(L, tables[0].c_str());
				}

				for (int32_t i = 1; i < (int32_t)tables.size(); i++)
				{
					lua_getfield(L, -1, tables[i].c_str());
					if (!lua_istable(L, -1) && !lua_isnil(L, -1))
					{
						SYSLOG_ERROR("table [{}] already exist", iter->first);
						return false;
					}

					if (lua_isnil(L, -1))
					{
						lua_pop(L, 1);
						lua_newtable(L);
						lua_pushstring(L, "__newindex");
						lua_pushcfunction(L, invalid_newindex);
						lua_rawset(L, -3);

						lua_pushvalue(L, -1);
						lua_setfield(L, -3, tables[i].c_str());
					}
				}
				
				(*iter->second)(L);
			}

			for (std::map<std::string, std::map<std::string, FuncBindData*>>::iterator iter = mMtFuncs.begin();
				iter != mMtFuncs.end(); ++iter)
			{
				std::map<std::string, FuncBindData*>& data = iter->second;
				lua_getglobal(L, iter->first.c_str());
				if (!lua_istable(L, -1) && !lua_isnil(L, -1))
				{
					SYSLOG_ERROR("table [{}] already exist", iter->first);
					return false;
				}
				if (lua_isnil(L, -1))
				{
					lua_newtable(L);

					lua_pushstring(L, "__newindex");
					lua_pushcfunction(L, invalid_newindex);
					lua_rawset(L, -3);

					lua_pushstring(L, "__index");
					lua_pushvalue(L, -2);
					lua_rawset(L, -3);

					lua_pushvalue(L, -1);
					lua_setglobal(L, iter->first.c_str());
				}

				for (std::map<std::string, FuncBindData*>::iterator diter = data.begin();
					diter != data.end(); ++diter)
				{
					lua_getfield(L, -1, diter->first.c_str());
					if (!lua_isnil(L, -1))
					{
						SYSLOG_ERROR("table [{}.{}] already exist", iter->first, diter->first);
						return false;
					}
					lua_pop(L, 1);

					lua_pushstring(L, diter->first.c_str());
					lua_pushlightuserdata(L, diter->second);
					lua_pushcclosure(L, FuncEnter, 1);
					lua_rawset(L, -3);
				}				
			}

			return true;
		}

	private:
		std::map<std::string, FuncBindData*>	mFuncs;
		std::map<std::string, lua_CFunction>	mCFuncs;
		std::map<std::string, std::map<std::string, FuncBindData*>> mMtFuncs;

	};
}

#endif