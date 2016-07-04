
#include "var.h"

using namespace ff;

var* varopts::create()
{
	var* v = new var();
	init(v);
	return v;
}

void varopts::free(var* v)
{
	uninit(v);
	delete v;
}


void varopts::init(var* v)
{
	v->type = VT_UNKNOWN;
	v->cb = 0;
	v->val.n = 0;
}

void varopts::uninit(var* v)
{
	switch (v->type)
	{
	case VT_STRING:
		delete v->val.str;
		break;
	case VT_VECTOR:
		for (std::vector<var*>::iterator iter = v->val.vec->begin();
			iter != v->val.vec->end(); ++iter)
		{
			free(*iter);
		}		
		delete v->val.vec;
		break;
	case VT_MAP:
		for (std::map<std::string, var*>::iterator iter = v->val.kv->begin();
			iter != v->val.kv->end(); ++iter)
		{
			free(iter->second);
		}
		delete v->val.kv;
		break;
	}
	init(v);
}

void varopts::copyvar(var* dst, const var* src)
{
	uninit(dst);
	dst->type = src->type;
	switch (src->type)
	{
	case VT_INT:
		dst->val.n = src->val.n;
		break;
	case VT_STRING:
		dst->val.str = new std::string(*src->val.str);
		break;
	case VT_POINTER:
		dst->val.ptr = src->val.ptr;
		break;
	case VT_VECTOR:
		dst->val.vec = new std::vector<var*>(src->val.vec->size());
		for (int32_t i = 0; i < (int32_t)dst->val.vec->size(); i++)
		{
			(*dst->val.vec)[i] = create();
			copyvar((*dst->val.vec)[i], (*src->val.vec)[i]);
		}
		break;
	case VT_MAP:
		dst->val.kv = new std::map<std::string, var*>();
		for (std::map<std::string, var*>::iterator iter = src->val.kv->begin();
			iter != src->val.kv->end(); ++iter)
		{
			var* v = create();
			copyvar(v, iter->second);
			(*dst->val.kv)[iter->first] = v;
		}
		break;
	}
}

var* varopts::get_map(var* v, const char* key)
{
	if (v->type != VT_MAP)
	{
		return nullptr;
	}

	std::map<std::string, var*>::iterator iter = v->val.kv->find(key);
	if (iter == v->val.kv->end())
	{
		return nullptr;
	}

	return iter->second;
}

var* varopts::get_vec(var* v, int32_t key)
{
	if (v->type != VT_VECTOR || key<0 || key>= (int32_t)v->val.vec->size())
	{
		return nullptr;
	}

	return (*v->val.vec)[key];
}

void varopts::set_int(var* v, int64_t n)
{
	uninit(v);
	v->type = VT_INT;
	v->val.n = n;
}

void varopts::set_str(var* v, const std::string& s)
{
	uninit(v);
	v->type = VT_STRING;
	v->val.str = new std::string(s);
}

void varopts::set_ptr(var* v, void* p)
{
	uninit(v);
	v->type = VT_POINTER;
	v->val.ptr = p;
}

void varopts::set_var(var* v, const var* p)
{
	uninit(v);
	copyvar(v, p);
}

void varopts::set_map(var* v)
{
	uninit(v);
	v->type = VT_MAP;
	v->val.kv = new std::map<std::string, var*>();
}

void varopts::set_vec(var* v)
{
	uninit(v);
	v->type = VT_VECTOR;
	v->val.vec = new std::vector<var*>();
}

bool varopts::push_back(var* v, var* p)
{
	if (v->type != VT_VECTOR)
	{
		return false;
	}
	var* ev = create();
	copyvar(ev, p);
	v->val.vec->push_back(ev);
	return true;
}

bool varopts::erase(var* v, int32_t key)
{
	if (v->type != VT_VECTOR || key < 0 || key >= (int32_t)v->val.vec->size())
	{
		return false;
	}
	std::vector<var*>::iterator iter = v->val.vec->begin() + key;
	varopts::free(*iter);
	v->val.vec->erase(iter);
	return true;
}

bool varopts::erase(var* v, const std::string& key)
{
	if (v->type != VT_MAP)
	{
		return false;
	}
	std::map<std::string, var*>::iterator iter = v->val.kv->find(key);
	if (iter == v->val.kv->end())
	{
		return false;
	}
	varopts::free(iter->second);
	v->val.kv->erase(iter);
	return true;
}

bool varopts::set(var* v, int32_t key, const var* p)
{
	if (v->type != VT_VECTOR || key<0 || key >= (int32_t)v->val.vec->size())
	{
		return false;
	}
	var* ev = create();
	copyvar(ev, p);

	(*v->val.vec)[key] = ev;
	return true;
}

bool varopts::set(var* v, const std::string& key, const var* p)
{
	if (v->type != VT_MAP)
	{
		return false;
	}
	var* ev = create();
	copyvar(ev, p);
	(*v->val.kv)[key] = ev;
	return true;
}

var* varopts::create_int(int64_t v)
{
	var* pv = create();
	set_int(pv, v);
	return pv;
}

var* varopts::create_str(const char* v)
{
	var* pv = create();
	set_str(pv, v);
	return pv;
}

var* varopts::create_ptr(void* v)
{
	var* pv = create();
	set_ptr(pv, v);
	return pv;
}

var* varopts::create_vec()
{
	var* pv = create();
	pv->type = VT_VECTOR;
	pv->val.vec = new std::vector<var*>();
	return pv;
}

var* varopts::create_map()
{
	var* pv = create();
	pv->type = VT_MAP;
	pv->val.kv = new std::map<std::string, var*>();
	return pv;
}
