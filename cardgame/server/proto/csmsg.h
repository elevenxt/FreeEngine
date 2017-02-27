#ifndef _us_csmsg_ids_
#define _us_csmsg_ids_

#include "csmsg.pb.h"

enum csmsg_ids{
	cs_buy_hero_id = 5,
	cs_login_id = 3,
	cs_pack_hero_id = 7,
	cs_challenge_mission_id = 9,
	cs_disconnect_id = 2,
	cs_friend_add_id = 11,
	cs_select_teammember_id = 8,
	cs_connect_id = 1,
	cs_charge_id = 4,
	cs_shop_item_id = 6,
	cs_talk_id = 10,
	cs_friend_mobility_id = 12,
};

struct csmsg_group;

template<typename GROUP, typename ST>
struct msg_st2id;

template<>
struct msg_st2id<csmsg_group, cs_buy_hero>{enum{ID=cs_buy_hero_id};};
template<>
struct msg_st2id<csmsg_group, cs_login>{enum{ID=cs_login_id};};
template<>
struct msg_st2id<csmsg_group, cs_pack_hero>{enum{ID=cs_pack_hero_id};};
template<>
struct msg_st2id<csmsg_group, cs_challenge_mission>{enum{ID=cs_challenge_mission_id};};
template<>
struct msg_st2id<csmsg_group, cs_disconnect>{enum{ID=cs_disconnect_id};};
template<>
struct msg_st2id<csmsg_group, cs_friend_add>{enum{ID=cs_friend_add_id};};
template<>
struct msg_st2id<csmsg_group, cs_select_teammember>{enum{ID=cs_select_teammember_id};};
template<>
struct msg_st2id<csmsg_group, cs_connect>{enum{ID=cs_connect_id};};
template<>
struct msg_st2id<csmsg_group, cs_charge>{enum{ID=cs_charge_id};};
template<>
struct msg_st2id<csmsg_group, cs_shop_item>{enum{ID=cs_shop_item_id};};
template<>
struct msg_st2id<csmsg_group, cs_talk>{enum{ID=cs_talk_id};};
template<>
struct msg_st2id<csmsg_group, cs_friend_mobility>{enum{ID=cs_friend_mobility_id};};


template<typename GROUP, int ID>
struct msg_id2st;

template<>
struct msg_id2st<csmsg_group, cs_buy_hero_id>{typedef cs_buy_hero ST;};
template<>
struct msg_id2st<csmsg_group, cs_login_id>{typedef cs_login ST;};
template<>
struct msg_id2st<csmsg_group, cs_pack_hero_id>{typedef cs_pack_hero ST;};
template<>
struct msg_id2st<csmsg_group, cs_challenge_mission_id>{typedef cs_challenge_mission ST;};
template<>
struct msg_id2st<csmsg_group, cs_disconnect_id>{typedef cs_disconnect ST;};
template<>
struct msg_id2st<csmsg_group, cs_friend_add_id>{typedef cs_friend_add ST;};
template<>
struct msg_id2st<csmsg_group, cs_select_teammember_id>{typedef cs_select_teammember ST;};
template<>
struct msg_id2st<csmsg_group, cs_connect_id>{typedef cs_connect ST;};
template<>
struct msg_id2st<csmsg_group, cs_charge_id>{typedef cs_charge ST;};
template<>
struct msg_id2st<csmsg_group, cs_shop_item_id>{typedef cs_shop_item ST;};
template<>
struct msg_id2st<csmsg_group, cs_talk_id>{typedef cs_talk ST;};
template<>
struct msg_id2st<csmsg_group, cs_friend_mobility_id>{typedef cs_friend_mobility ST;};


#endif
