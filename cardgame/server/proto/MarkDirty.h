
#ifndef _MARK_DIRTY_
#define _MARK_DIRTY_

#include <cinttypes>
#include <vector>
#include "IMarkDirty.h"

class MarkDirty : public IMarkDirty
{
private:
	static const int32_t MAX_SUPPORT_IDX = 65536;

public:
	void init(IMarkDirty* parent, int32_t idx, int32_t toParentType)
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
	MarkDirty()
	{
		mParent = nullptr;
		mIdxInParent = -1;
		mToParentType = 0;
		clearDirty(~0);
	}

	virtual void markDirty(int32_t idx, int32_t type)
	{
		if (idx<0 || idx>= MAX_SUPPORT_IDX)
		{
			throw new std::logic_error("out of bound.");
			return;
		}
		if (idx >= (int32_t)mStatus.size())
		{
			mStatus.resize(idx + 1, 0);
		}

		int32_t nOld = mStatus[idx];
		int32_t toParentType = ((~nOld) & type) & mToParentType;
		mStatus[idx] = nOld | type;
		mDirty = mDirty | type;

		if (mParent != nullptr && toParentType != 0)
		{
			mParent->markDirty(mIdxInParent, toParentType);
		}
	}

public:
	bool isDirty(int32_t type)
	{
		return mDirty & type;
	}

	bool isDirty(int32_t idx, int32_t type)
	{
		if (idx < 0 || idx >= (int32_t)mStatus.size())
		{
			return false;
		}
		return mStatus[idx] & type;
	}

	virtual void clearDirty(int32_t type)
	{
		for (int32_t i=0; i<(int32_t)mStatus.size(); i++)
		{
			mStatus[i] = (mStatus[i] & (~type));
		}
		mDirty = mDirty & (~type);

		clearChildDirty(type);
	}

	std::vector<int32_t> getAllDirtyChild(int32_t type)
	{
		std::vector<int32_t> vecDirty;
		for (int32_t i=0; i<(int32_t)mStatus.size(); i++)
		{
			if (mStatus[i] & type)
			{
				vecDirty.push_back(i);
			}
		}

		return vecDirty;
	}

private:
	int				  mToParentType;
	// 已经标脏的孩子数
	int				  mDirty;
	// 有哪些孩子标脏了
	std::vector<int32_t> mStatus;
	// 父节点
	IMarkDirty*		  mParent;
	// 在父节点中的索引
	int				  mIdxInParent;
};

#endif