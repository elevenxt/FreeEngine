
#ifndef _GAMEDATA_HEAD_
#define _GAMEDATA_HEAD_

class PlayerSummary;
class Guild;
class FriendInfo;
class BaseInfo;
class SysInfo;
class Card;
class Package;
class TeamInfo;
class PlayerData;

class  PlayerSummary{
public:
   //等级
   virtual int getLevel() = 0;
   virtual void setLevel(int val) = 0;
   //id
   virtual const char* getId() = 0;
   virtual void setId(const char* val) = 0;
   //角色名
   virtual const char* getName() = 0;
   virtual void setName(const char* val) = 0;
};

class  Guild{
public:
   //公会成员
   virtual int sizeGuildMember() = 0;
   virtual PlayerSummary& getGuildMember(int idx) = 0;
   //公会名
   virtual const char* getName() = 0;
   virtual void setName(const char* val) = 0;
   //公会等级
   virtual int getLevel() = 0;
   virtual void setLevel(int val) = 0;
   //公会id
   virtual int getId() = 0;
   virtual void setId(int val) = 0;
   //会长id
   virtual int getChairman() = 0;
   virtual void setChairman(int val) = 0;
};

class  FriendInfo{
public:
   //基本信息
   virtual PlayerSummary& getInfo() = 0;
   //可以领取的移动力
   virtual int getMobility() = 0;
   virtual void setMobility(int val) = 0;
};

class  BaseInfo{
public:
   //精英通关关卡
   virtual int getEliteLine() = 0;
   virtual void setEliteLine(int val) = 0;
   //角色名
   virtual const char* getName() = 0;
   virtual void setName(const char* val) = 0;
   //角色等级
   virtual int getLevel() = 0;
   virtual void setLevel(int val) = 0;
   //主线通关关卡
   virtual int getMainLine() = 0;
   virtual void setMainLine(int val) = 0;
   //角色经验
   virtual int getExp() = 0;
   virtual void setExp(int val) = 0;
   //最近离线时间
   virtual int getOffTime() = 0;
   virtual void setOffTime(int val) = 0;
   //钻石
   virtual int getDiamond() = 0;
   virtual void setDiamond(int val) = 0;
   //金币
   virtual int getGold() = 0;
   virtual void setGold(int val) = 0;
   //移动力
   virtual int getMobility() = 0;
   virtual void setMobility(int val) = 0;
   //英雄通关关卡
   virtual int getHeroLine() = 0;
   virtual void setHeroLine(int val) = 0;
   //角色id
   virtual const char* getId() = 0;
   virtual void setId(const char* val) = 0;
};

class  SysInfo{
public:
   //服务器名
   virtual const char* getServerName() = 0;
   virtual void setServerName(const char* val) = 0;
   //服务器当前时间
   virtual int getServerTime() = 0;
   virtual void setServerTime(int val) = 0;
   //在线用户数
   virtual int getOnlinePlayer() = 0;
   virtual void setOnlinePlayer(int val) = 0;
};

class  Card{
public:
   //卡牌id
   virtual int getId() = 0;
   virtual void setId(int val) = 0;
   //队长技能
   virtual int getLeaderSkill() = 0;
   virtual void setLeaderSkill(int val) = 0;
   //卡牌等级
   virtual int getLevel() = 0;
   virtual void setLevel(int val) = 0;
};

class  Package{
public:
   //背包物品
   virtual int sizeSlot() = 0;
   virtual Card& getSlot(int idx) = 0;
};

class  TeamInfo{
public:
   //团队成员
   virtual int sizeTeamMember() = 0;
   virtual Card& getTeamMember(int idx) = 0;
};

class  PlayerData{
public:
   //背包
   virtual int sizeFriends() = 0;
   virtual FriendInfo& getFriends(int idx) = 0;
   //队伍信息
   virtual TeamInfo& getTeamInfo() = 0;
   //系统信息
   virtual SysInfo& getSysInfo() = 0;
   //背包
   virtual Package& getPackage() = 0;
   //基本信息
   virtual BaseInfo& getBaseInfo() = 0;
};



#endif
