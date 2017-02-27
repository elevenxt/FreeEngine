
#include "BattleLogic.h"
#include "base.h"

using namespace ff;

bool BattleLogic::makeBattleReport(std::vector<Action>& acts, std::vector<Character> lChar, std::vector<Character> rChar)
{
	SYS_VERIFY_RV(lChar.size() <= CHAR_NUM, false);
	SYS_VERIFY_RV(rChar.size() <= CHAR_NUM, false);

	for (Character& c : rChar)
	{
		c.pos += 6;
	}

	for (int i=0; i<MAX_ROUND; i++)
	{
		for (Character p : lChar)
		{
			makeAction(acts, p, rChar);
			if (rChar.empty())
			{
				break;
			}
		}
		if (rChar.empty())
		{
			Action act;
			act.act = RES;
			act.value = 1;
			acts.push_back(act);
			return true;
		}

		for (Character p : rChar)
		{
			makeAction(acts, p, lChar);
			if (lChar.empty())
			{
				break;
			}
		}

		if (lChar.empty())
		{
			Action act;
			act.act = RES;
			act.value = 0;
			acts.push_back(act);
			return false;
		}
	}

	Action act;
	act.act = RES;
	act.value = 0;
	acts.push_back(act);
	return false;
}

void BattleLogic::makeAction(std::vector<Action>& acts, BattleLogic::Character p, std::vector<BattleLogic::Character>& chars)
{
	Action act;
	int32_t ridx = rand() % chars.size();
	act.from = p.pos;
	act.to = chars[ridx].pos;
	act.act = ATK;
	act.value = (int32_t)(p.atk * (0.5f + rand()%100/100.0f));
	acts.push_back(act);

	chars[ridx].hp -= act.value;
	if (chars[ridx].hp <= 0)
	{
		act.act = DIE;
		acts.push_back(act);
		chars.erase(chars.begin() + ridx);
	}	
}