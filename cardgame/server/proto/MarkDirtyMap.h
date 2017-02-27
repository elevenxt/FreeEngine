
#ifndef _MARK_DIRTYMAP_
#define _MARK_DIRTYMAP_

#include <map>
#include "IMarkDirty.h"

class MarkDirtyMap : public IMarkDirty
{
public:
	void init(IMarkDirty* parent, int idx, int toParentType)
	{
		mParent = parent;
		mParent->addChild(idx, this);
		mIdxInParent = idx;
		mToParentType = toParentType;
		clearDirty(~0);
	}

	int getIdxInParent()
	{
		return mIdxInParent;
	}

protected:
	MarkDirtyMap()
	{
		mParent = nullptr;
		mIdxInParent = -1;
		mToParentType = 0;
		clearDirty(~0);
	}

public:
	virtual void markDirty(int idx, int type)
	{
		int nOld = mStatus[idx];
		int toParentType = ((~nOld) & type) & mToParentType;
		mStatus[idx] = nOld | type;
		mDirty = mDirty | type;

		if (mParent != nullptr && toParentType != 0)
		{
			mParent->markDirty(mIdxInParent, toParentType);
		}
	}

	bool isDirty(int type)
	{
		return mDirty & type;
	}

	bool isDirty(int idx, int type)
	{
		std::map<int, int>::iterator iter = mStatus.find(idx);
		if (iter == mStatus.end())
		{
			return false;
		}

		return iter->second & type;
	}

	void clearDirty(int type)
	{
		std::map<int, int>::iterator iter = mStatus.begin();

		for (; iter != mStatus.end();)
		{
			iter->second = iter->second & (~type);
			if (iter->second == 0)
			{
				mStatus.erase(iter++);
			}		
			else
			{
				++iter;
			}
		}

		mDirty = mDirty & (~type);

		clearChildDirty(type);
	}

	std::vector<int> getAllDirtyChild(int type)
	{
		std::vector<int> vecDirty;
		std::map<int, int>::iterator iter = mStatus.begin();
		for (; iter != mStatus.end(); ++iter)
		{
			if (iter->second & type)
			{
				vecDirty.push_back(iter->first);
			}
		}

		return vecDirty;
	}

	void remove(int idx)
	{
		mStatus.erase(idx);
		removeChild(idx);
	}

private:
	int				  mToParentType;
	// 已经标脏的孩子数
	int				  mDirty;
	// 有哪些孩子标脏了
	std::map<int,int> mStatus;
	// 父节点
	IMarkDirty*		  mParent;
	// 在父节点中的索引
	int				  mIdxInParent;
};

#endif