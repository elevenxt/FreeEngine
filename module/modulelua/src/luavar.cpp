
#include "luavar.h"
#include "var.h"
#include "StringUtil.h"

using namespace ff;

static const char* mtname = "__var_mt";

static void pushVar(lua_State* L, var* v)
{
	if (v == nullptr)
	{
		lua_pushnil(L);
		return;
	}

	switch (v->type)
	{
	case VT_UNKNOWN:
		lua_pushnil(L);
		break;
	case VT_INT:
		lua_pushinteger(L, v->val.n);
		break;
	case VT_STRING:
		lua_pushstring(L, v->val.str->c_str());
		break;
	case VT_POINTER:
		lua_pushlightuserdata(L, v->val.ptr);
		break;
	default:
	{
		void* vd = lua_newuserdata(L, sizeof(var*));
		*(var**)vd = v;
		lua_getglobal(L, "__var_mt");
		lua_setmetatable(L, -2);
	}
	break;
	}
}

static void toVar(var* v, lua_State* L, int idx)
{
	if (lua_isstring(L, -1))
	{
		const char* val = lua_tostring(L, -1);
		varopts::set_str(v, val);
	}
	else if (lua_isnumber(L, -1))
	{
		int val = lua_tointeger(L, -1);
		varopts::set_int(v, val);
	}
	else if (lua_islightuserdata(L, -1))
	{
		void* val = lua_touserdata(L, -1);
		varopts::set_ptr(v, val);
	}
	else if (lua_isuserdata(L, -1))
	{
		var* val = *(var**)lua_touserdata(L, -1);
		varopts::set_var(v, val);
	}
}

static int globaldata_totable(lua_State* L)
{
	if (!lua_isuserdata(L, -1))
	{
		return 0;
	}

	var* v = *(var**)lua_touserdata(L, -1);
	lua_newtable(L);
	switch (v->type)
	{
	case VT_VECTOR:
	{
		int idx = 1;
		for (std::vector<var*>::iterator iter = v->val.vec->begin();
			iter != v->val.vec->end(); ++iter)
		{
			lua_pushinteger(L, idx);
			idx++;
			pushVar(L, *iter);
			lua_settable(L, -3);
		}
	}
		break;
	case VT_MAP:
	{
		for (std::map<std::string, var*>::iterator iter = v->val.kv->begin();
			iter != v->val.kv->end(); ++iter)
		{
			lua_pushstring(L, iter->first.c_str());
			pushVar(L, iter->second);
			lua_settable(L, -3);
		}
	}
		break;
	default:
		return 0;
		break;
	}
	
	return 1;
}

static void globaldata_fromtable(var* v, lua_State* L, int idx)
{
	if (!lua_istable(L, idx) || v->type != VarType::VT_MAP)
	{
		return;
	}
	
	lua_pushnil(L);
	while (lua_next(L, -2)) {
		/* 此时栈上 -1 处为 value, -2 处为 key */
		var tmp;
		varopts::init(&tmp);
		toVar(&tmp, L, -1);
		varopts::set(v, lua_tostring(L, -2), &tmp);
		varopts::uninit(&tmp);

		lua_pop(L, 1);
	}

	return;
}

static int globaldata_index(lua_State* L)
{
	var* v = *(var**)lua_touserdata(L, -2);
	const char* key = lua_tostring(L, -1);

	var* rv = varopts::get_map(v, key);
	pushVar(L, rv);
	return 1;
}

static int globaldata_newindex(lua_State* L)
{
	var* v = *(var**)lua_touserdata(L, -3);
	const char* key = lua_tostring(L, -2);

	if (lua_isstring(L, -1))
	{
		const char* val = lua_tostring(L, -1);
		var tmp;
		varopts::init(&tmp);
		varopts::set_str(&tmp, val);
		varopts::set(v, key, &tmp);
		varopts::uninit(&tmp);
	}
	else if (lua_isnumber(L, -1))
	{
		int val = lua_tointeger(L, -1);
		var tmp;
		varopts::init(&tmp);
		varopts::set_int(&tmp, val);
		varopts::set(v, key, &tmp);
	}
	else if (lua_isuserdata(L, -1))
	{
		var* val = *(var**)lua_touserdata(L, -1);
		varopts::set(v, key, val);
	}

	return 0;
}

static int globaldata_set(lua_State* L)
{
	var* v = *(var**)lua_touserdata(L, -3);	

	const char* key = lua_tostring(L, -2);
	std::vector<std::string> tbs = StringUtil::split(key, ".");
	var* cv = v;
	for (int32_t i = 0; i < (int32_t)tbs.size()-1; i++)
	{
		if (cv->type != VT_MAP)
		{
			varopts::copyvar(cv, varopts::create_map());
		}
		var* nv = varopts::get_map(cv, tbs[i].c_str());
		if (nv == nullptr)
		{
			varopts::set(cv, tbs[i], varopts::create_map());
			nv = varopts::get_map(cv, tbs[i].c_str());
		}
		cv = nv;
	}

	std::string lkey = tbs.back();
	if (lua_isstring(L, -1))
	{
		const char* val = lua_tostring(L, -1);
		var tmp;
		varopts::init(&tmp);
		varopts::set_str(&tmp, val);
		varopts::set(cv, lkey, &tmp);
		varopts::uninit(&tmp);
	}
	else if (lua_isnumber(L, -1))
	{
		int val = lua_tointeger(L, -1);
		var tmp;
		varopts::init(&tmp);
		varopts::set_int(&tmp, val);
		varopts::set(cv, lkey, &tmp);
	}
	else if (lua_islightuserdata(L, -1))
	{
		void* val = lua_touserdata(L, -1);
		var tmp;
		varopts::init(&tmp);
		varopts::set_ptr(&tmp, val);
		varopts::set(cv, lkey, &tmp);
		varopts::uninit(&tmp);
	}
	else if (lua_istable(L, -1))
	{
		var tmp;
		varopts::init(&tmp);
		varopts::set_map(&tmp);
		globaldata_fromtable(&tmp, L, -1);
		varopts::set(cv, lkey, &tmp);
		varopts::uninit(&tmp);
	}
	else if (lua_isuserdata(L, -1))
	{
		var* val = *(var**)lua_touserdata(L, -1);
		varopts::set(cv, lkey, val);
	}
	
	return 0;
}

static int globaldata_get(lua_State* L)
{
	var* v = *(var**)lua_touserdata(L, -2);

	const char* key = lua_tostring(L, -1);
	std::vector<std::string> tbs = StringUtil::split(key, ".");
	var* cv = v;
	for (int32_t i = 0; i < (int32_t)tbs.size() - 1; i++)
	{
		if (cv->type != VT_MAP)
		{
			return 0;
		}
		cv = varopts::get_map(cv, tbs[i].c_str());
	}

	cv = varopts::get_map(cv, tbs.back().c_str());
	pushVar(L, cv);

	return 1;
}

static void initVarMt(lua_State* L)
{
	lua_newtable(L);
	lua_pushstring(L, "__index");

	lua_newtable(L);
	lua_pushstring(L, "__index");
	lua_pushcfunction(L, globaldata_index);
	lua_rawset(L, -3);
	lua_pushstring(L, "__newindex");
	lua_pushcfunction(L, globaldata_newindex);
	lua_rawset(L, -3);
	lua_pushstring(L, "set");
	lua_pushcfunction(L, globaldata_set);
	lua_rawset(L, -3);
	lua_pushstring(L, "get");
	lua_pushcfunction(L, globaldata_get);
	lua_rawset(L, -3);
	lua_pushstring(L, "totable");
	lua_pushcfunction(L, globaldata_totable);
	lua_rawset(L, -3);
	lua_rawset(L, -3);
	lua_setglobal(L, mtname);
}

void LuaVar::pushVarMt(lua_State* L)
{
	lua_getglobal(L, mtname);
}
