#ifndef _us_scmsg_ids_
#define _us_scmsg_ids_

#include "scmsg.pb.h"

enum scmsg_ids{
	sc_battle_report_id = 4,
	sc_player_data_id = 3,
	sc_talk_id = 2,
	sc_login_res_id = 1,
};

struct scmsg_group;

template<typename GROUP, typename ST>
struct msg_st2id;

template<>
struct msg_st2id<scmsg_group, sc_battle_report>{enum{ID=sc_battle_report_id};};
template<>
struct msg_st2id<scmsg_group, sc_player_data>{enum{ID=sc_player_data_id};};
template<>
struct msg_st2id<scmsg_group, sc_talk>{enum{ID=sc_talk_id};};
template<>
struct msg_st2id<scmsg_group, sc_login_res>{enum{ID=sc_login_res_id};};


template<typename GROUP, int ID>
struct msg_id2st;

template<>
struct msg_id2st<scmsg_group, sc_battle_report_id>{typedef sc_battle_report ST;};
template<>
struct msg_id2st<scmsg_group, sc_player_data_id>{typedef sc_player_data ST;};
template<>
struct msg_id2st<scmsg_group, sc_talk_id>{typedef sc_talk ST;};
template<>
struct msg_id2st<scmsg_group, sc_login_res_id>{typedef sc_login_res ST;};


#endif
