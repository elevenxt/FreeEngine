
#ifndef _IMARK_DIRTY_
#define _IMARK_DIRTY_

#include <vector>
#include <map>

class IMarkDirty
{
public:
	enum
	{
		DB_DIRTY = 1 << 0,
		SYNC_DIRTY = 1 << 1,
	};

public:
	virtual void clearDirty(int type) = 0;
	virtual void markDirty(int idx, int type) = 0;

	void addChild(int idx, IMarkDirty* child)
	{
		mChilds[idx].push_back(child);
	}

	void removeChild(int idx)
	{
		mChilds.erase(idx);
	}

	void clearChildDirty(int type)
	{
		for (auto kv : mChilds)
		{
			for (IMarkDirty* md : kv.second)
			{
				md->clearDirty(type);
			}
		}
	}
private:
	std::map<int, std::vector<IMarkDirty*>>	mChilds;
};

#endif