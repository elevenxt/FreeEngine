
#ifndef _FF_BATTLE_LOGIC
#define _FF_BATTLE_LOGIC

#include <cinttypes>
#include <vector>

#include "Singleton.h"

namespace ff
{
	class BattleLogic : public Singleton<BattleLogic>
	{
	public:
		enum ACT
		{
			ATK = 0,
			DIE = 1,
			RES = 2,
		};

		static const int32_t MAX_ROUND = 30;
		static const int32_t CHAR_NUM = 6;

		struct Action
		{
			uint8_t act;
			uint8_t from;
			uint8_t to;
			int32_t value;
		};

		struct Character
		{
			uint8_t pos;
			int32_t hp;
			int32_t atk;
			int32_t id;
		};

		static bool	makeBattleReport(std::vector<Action>& acts, std::vector<Character> lChar, std::vector<Character> rChar);

	private:
		static void makeAction(std::vector<Action>& acts, BattleLogic::Character p, std::vector<BattleLogic::Character>& chars);
	};
}

#endif