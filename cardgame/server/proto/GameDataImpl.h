
#ifndef _GAMEDATA_IMPL_
#define _GAMEDATA_IMPL_

#include <exception>
/**这是由程序生成的代码，不要尝试手动修改!*/
#include <string>
#include "gamedata.pb.h"
#include "MarkDirty.h"
#include "GameData.h"

class PlayerSummary;
class Guild;
class FriendInfo;
class BaseInfo;
class SysInfo;
class Card;
class Package;
class TeamInfo;
class PlayerData;

class  PlayerSummaryImpl : public PlayerSummary, public MarkDirty{
   private: PlayerSummaryImpl(const PlayerSummaryImpl&) = delete;   private: void operator=(const PlayerSummaryImpl&) = delete;public:
   PlayerSummaryImpl(){
       mLevel = int();
   }
   //等级
   virtual int getLevel(){
       return mLevel;
   }
   virtual void setLevel(int val){
       mLevel = val;
       markDirty(0, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
   }
   //id
   virtual const char* getId(){
       return mId.c_str();
   }
   virtual void setId(const char* val){
       mId = val;
       markDirty(1, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
   }
   //角色名
   virtual const char* getName(){
       return mName.c_str();
   }
   virtual void setName(const char* val){
       mName = val;
       markDirty(2, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
   }
   void toProto(PlayerSummaryProto* proto, bool db, bool sync, bool all=false){
       if(all || (db && 1) || (sync && 1 && isDirty(0, IMarkDirty::SYNC_DIRTY))){
           proto->set_level(mLevel);
       }
       if(all || (db && 1) || (sync && 1 && isDirty(1, IMarkDirty::SYNC_DIRTY))){
           proto->set_id(mId);
       }
       if(all || (db && 1) || (sync && 1 && isDirty(2, IMarkDirty::SYNC_DIRTY))){
           proto->set_name(mName);
       }
   }
   void fromProto(const PlayerSummaryProto& proto){
       mLevel = proto.level();
       mId = proto.id();
       mName = proto.name();
   }
private:
   //等级
   int  mLevel;
   //id
   std::string  mId;
   //角色名
   std::string  mName;
};

class  GuildImpl : public Guild, public MarkDirty{
   private: GuildImpl(const GuildImpl&) = delete;   private: void operator=(const GuildImpl&) = delete;public:
   GuildImpl(){
       for(int i=0; i<30; i++){;
           mGuildMember[i].init(this, 0, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
       }
       mLevel = int();
       mId = int();
       mChairman = int();
   }
   //公会成员
   virtual int sizeGuildMember(){return 30;}
   virtual PlayerSummary& getGuildMember(int idx){
       if(idx < 0 || idx >= 30){throw std::out_of_range("GuildMember");}
       return mGuildMember[idx];
   }
   //公会名
   virtual const char* getName(){
       return mName.c_str();
   }
   virtual void setName(const char* val){
       mName = val;
       markDirty(1, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
   }
   //公会等级
   virtual int getLevel(){
       return mLevel;
   }
   virtual void setLevel(int val){
       mLevel = val;
       markDirty(2, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
   }
   //公会id
   virtual int getId(){
       return mId;
   }
   virtual void setId(int val){
       mId = val;
       markDirty(3, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
   }
   //会长id
   virtual int getChairman(){
       return mChairman;
   }
   virtual void setChairman(int val){
       mChairman = val;
       markDirty(4, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
   }
   void toProto(GuildProto* proto, bool db, bool sync, bool all=false){
       if(all || (db && 1) || (sync && 1 && isDirty(0, IMarkDirty::SYNC_DIRTY))){
           if (all || (db && 1) || (sync && 1 && mGuildMember[0].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[0].toProto(proto->mutable_guildmember()->mutable__v0(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mGuildMember[1].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[1].toProto(proto->mutable_guildmember()->mutable__v1(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mGuildMember[2].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[2].toProto(proto->mutable_guildmember()->mutable__v2(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mGuildMember[3].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[3].toProto(proto->mutable_guildmember()->mutable__v3(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mGuildMember[4].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[4].toProto(proto->mutable_guildmember()->mutable__v4(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mGuildMember[5].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[5].toProto(proto->mutable_guildmember()->mutable__v5(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mGuildMember[6].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[6].toProto(proto->mutable_guildmember()->mutable__v6(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mGuildMember[7].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[7].toProto(proto->mutable_guildmember()->mutable__v7(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mGuildMember[8].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[8].toProto(proto->mutable_guildmember()->mutable__v8(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mGuildMember[9].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[9].toProto(proto->mutable_guildmember()->mutable__v9(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mGuildMember[10].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[10].toProto(proto->mutable_guildmember()->mutable__v10(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mGuildMember[11].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[11].toProto(proto->mutable_guildmember()->mutable__v11(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mGuildMember[12].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[12].toProto(proto->mutable_guildmember()->mutable__v12(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mGuildMember[13].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[13].toProto(proto->mutable_guildmember()->mutable__v13(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mGuildMember[14].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[14].toProto(proto->mutable_guildmember()->mutable__v14(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mGuildMember[15].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[15].toProto(proto->mutable_guildmember()->mutable__v15(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mGuildMember[16].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[16].toProto(proto->mutable_guildmember()->mutable__v16(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mGuildMember[17].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[17].toProto(proto->mutable_guildmember()->mutable__v17(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mGuildMember[18].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[18].toProto(proto->mutable_guildmember()->mutable__v18(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mGuildMember[19].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[19].toProto(proto->mutable_guildmember()->mutable__v19(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mGuildMember[20].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[20].toProto(proto->mutable_guildmember()->mutable__v20(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mGuildMember[21].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[21].toProto(proto->mutable_guildmember()->mutable__v21(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mGuildMember[22].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[22].toProto(proto->mutable_guildmember()->mutable__v22(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mGuildMember[23].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[23].toProto(proto->mutable_guildmember()->mutable__v23(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mGuildMember[24].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[24].toProto(proto->mutable_guildmember()->mutable__v24(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mGuildMember[25].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[25].toProto(proto->mutable_guildmember()->mutable__v25(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mGuildMember[26].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[26].toProto(proto->mutable_guildmember()->mutable__v26(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mGuildMember[27].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[27].toProto(proto->mutable_guildmember()->mutable__v27(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mGuildMember[28].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[28].toProto(proto->mutable_guildmember()->mutable__v28(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mGuildMember[29].isDirty(IMarkDirty::SYNC_DIRTY))){
               mGuildMember[29].toProto(proto->mutable_guildmember()->mutable__v29(), db, sync, all);
           }
       }
       if(all || (db && 1) || (sync && 1 && isDirty(1, IMarkDirty::SYNC_DIRTY))){
           proto->set_name(mName);
       }
       if(all || (db && 1) || (sync && 1 && isDirty(2, IMarkDirty::SYNC_DIRTY))){
           proto->set_level(mLevel);
       }
       if(all || (db && 1) || (sync && 1 && isDirty(3, IMarkDirty::SYNC_DIRTY))){
           proto->set_id(mId);
       }
       if(all || (db && 1) || (sync && 1 && isDirty(4, IMarkDirty::SYNC_DIRTY))){
           proto->set_chairman(mChairman);
       }
   }
   void fromProto(const GuildProto& proto){
       if (proto.has_guildmember()){
           if (proto.guildmember().has__v0()){
               mGuildMember[0].fromProto(proto.guildmember()._v0());
           }
           if (proto.guildmember().has__v1()){
               mGuildMember[1].fromProto(proto.guildmember()._v1());
           }
           if (proto.guildmember().has__v2()){
               mGuildMember[2].fromProto(proto.guildmember()._v2());
           }
           if (proto.guildmember().has__v3()){
               mGuildMember[3].fromProto(proto.guildmember()._v3());
           }
           if (proto.guildmember().has__v4()){
               mGuildMember[4].fromProto(proto.guildmember()._v4());
           }
           if (proto.guildmember().has__v5()){
               mGuildMember[5].fromProto(proto.guildmember()._v5());
           }
           if (proto.guildmember().has__v6()){
               mGuildMember[6].fromProto(proto.guildmember()._v6());
           }
           if (proto.guildmember().has__v7()){
               mGuildMember[7].fromProto(proto.guildmember()._v7());
           }
           if (proto.guildmember().has__v8()){
               mGuildMember[8].fromProto(proto.guildmember()._v8());
           }
           if (proto.guildmember().has__v9()){
               mGuildMember[9].fromProto(proto.guildmember()._v9());
           }
           if (proto.guildmember().has__v10()){
               mGuildMember[10].fromProto(proto.guildmember()._v10());
           }
           if (proto.guildmember().has__v11()){
               mGuildMember[11].fromProto(proto.guildmember()._v11());
           }
           if (proto.guildmember().has__v12()){
               mGuildMember[12].fromProto(proto.guildmember()._v12());
           }
           if (proto.guildmember().has__v13()){
               mGuildMember[13].fromProto(proto.guildmember()._v13());
           }
           if (proto.guildmember().has__v14()){
               mGuildMember[14].fromProto(proto.guildmember()._v14());
           }
           if (proto.guildmember().has__v15()){
               mGuildMember[15].fromProto(proto.guildmember()._v15());
           }
           if (proto.guildmember().has__v16()){
               mGuildMember[16].fromProto(proto.guildmember()._v16());
           }
           if (proto.guildmember().has__v17()){
               mGuildMember[17].fromProto(proto.guildmember()._v17());
           }
           if (proto.guildmember().has__v18()){
               mGuildMember[18].fromProto(proto.guildmember()._v18());
           }
           if (proto.guildmember().has__v19()){
               mGuildMember[19].fromProto(proto.guildmember()._v19());
           }
           if (proto.guildmember().has__v20()){
               mGuildMember[20].fromProto(proto.guildmember()._v20());
           }
           if (proto.guildmember().has__v21()){
               mGuildMember[21].fromProto(proto.guildmember()._v21());
           }
           if (proto.guildmember().has__v22()){
               mGuildMember[22].fromProto(proto.guildmember()._v22());
           }
           if (proto.guildmember().has__v23()){
               mGuildMember[23].fromProto(proto.guildmember()._v23());
           }
           if (proto.guildmember().has__v24()){
               mGuildMember[24].fromProto(proto.guildmember()._v24());
           }
           if (proto.guildmember().has__v25()){
               mGuildMember[25].fromProto(proto.guildmember()._v25());
           }
           if (proto.guildmember().has__v26()){
               mGuildMember[26].fromProto(proto.guildmember()._v26());
           }
           if (proto.guildmember().has__v27()){
               mGuildMember[27].fromProto(proto.guildmember()._v27());
           }
           if (proto.guildmember().has__v28()){
               mGuildMember[28].fromProto(proto.guildmember()._v28());
           }
           if (proto.guildmember().has__v29()){
               mGuildMember[29].fromProto(proto.guildmember()._v29());
           }
       }
       mName = proto.name();
       mLevel = proto.level();
       mId = proto.id();
       mChairman = proto.chairman();
   }
private:
   //公会成员
   PlayerSummaryImpl  mGuildMember[30];
   //公会名
   std::string  mName;
   //公会等级
   int  mLevel;
   //公会id
   int  mId;
   //会长id
   int  mChairman;
};

class  FriendInfoImpl : public FriendInfo, public MarkDirty{
   private: FriendInfoImpl(const FriendInfoImpl&) = delete;   private: void operator=(const FriendInfoImpl&) = delete;public:
   FriendInfoImpl(){
       mInfo.init(this, 0, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
       mMobility = int();
   }
   //基本信息
   virtual PlayerSummary& getInfo(){
       return mInfo;
   }
   //可以领取的移动力
   virtual int getMobility(){
       return mMobility;
   }
   virtual void setMobility(int val){
       mMobility = val;
       markDirty(1, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
   }
   void toProto(FriendInfoProto* proto, bool db, bool sync, bool all=false){
       if(all || (db && 1) || (sync && 1 && isDirty(0, IMarkDirty::SYNC_DIRTY))){
           mInfo.toProto(proto->mutable_info(), db, sync, all);
       }
       if(all || (db && 1) || (sync && 1 && isDirty(1, IMarkDirty::SYNC_DIRTY))){
           proto->set_mobility(mMobility);
       }
   }
   void fromProto(const FriendInfoProto& proto){
       mInfo.fromProto(proto.info());
       mMobility = proto.mobility();
   }
private:
   //基本信息
   PlayerSummaryImpl  mInfo;
   //可以领取的移动力
   int  mMobility;
};

class  BaseInfoImpl : public BaseInfo, public MarkDirty{
   private: BaseInfoImpl(const BaseInfoImpl&) = delete;   private: void operator=(const BaseInfoImpl&) = delete;public:
   BaseInfoImpl(){
       mEliteLine = int();
       mLevel = int();
       mMainLine = int();
       mExp = int();
       mOffTime = int();
       mDiamond = int();
       mGold = int();
       mMobility = int();
       mHeroLine = int();
   }
   //精英通关关卡
   virtual int getEliteLine(){
       return mEliteLine;
   }
   virtual void setEliteLine(int val){
       mEliteLine = val;
       markDirty(0, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
   }
   //角色名
   virtual const char* getName(){
       return mName.c_str();
   }
   virtual void setName(const char* val){
       mName = val;
       markDirty(1, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
   }
   //角色等级
   virtual int getLevel(){
       return mLevel;
   }
   virtual void setLevel(int val){
       mLevel = val;
       markDirty(2, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
   }
   //主线通关关卡
   virtual int getMainLine(){
       return mMainLine;
   }
   virtual void setMainLine(int val){
       mMainLine = val;
       markDirty(3, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
   }
   //角色经验
   virtual int getExp(){
       return mExp;
   }
   virtual void setExp(int val){
       mExp = val;
       markDirty(4, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
   }
   //最近离线时间
   virtual int getOffTime(){
       return mOffTime;
   }
   virtual void setOffTime(int val){
       mOffTime = val;
       markDirty(5, IMarkDirty::DB_DIRTY);
   }
   //钻石
   virtual int getDiamond(){
       return mDiamond;
   }
   virtual void setDiamond(int val){
       mDiamond = val;
       markDirty(6, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
   }
   //金币
   virtual int getGold(){
       return mGold;
   }
   virtual void setGold(int val){
       mGold = val;
       markDirty(7, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
   }
   //移动力
   virtual int getMobility(){
       return mMobility;
   }
   virtual void setMobility(int val){
       mMobility = val;
       markDirty(8, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
   }
   //英雄通关关卡
   virtual int getHeroLine(){
       return mHeroLine;
   }
   virtual void setHeroLine(int val){
       mHeroLine = val;
       markDirty(9, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
   }
   //角色id
   virtual const char* getId(){
       return mId.c_str();
   }
   virtual void setId(const char* val){
       mId = val;
       markDirty(10, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
   }
   void toProto(BaseInfoProto* proto, bool db, bool sync, bool all=false){
       if(all || (db && 1) || (sync && 1 && isDirty(0, IMarkDirty::SYNC_DIRTY))){
           proto->set_eliteline(mEliteLine);
       }
       if(all || (db && 1) || (sync && 1 && isDirty(1, IMarkDirty::SYNC_DIRTY))){
           proto->set_name(mName);
       }
       if(all || (db && 1) || (sync && 1 && isDirty(2, IMarkDirty::SYNC_DIRTY))){
           proto->set_level(mLevel);
       }
       if(all || (db && 1) || (sync && 1 && isDirty(3, IMarkDirty::SYNC_DIRTY))){
           proto->set_mainline(mMainLine);
       }
       if(all || (db && 1) || (sync && 1 && isDirty(4, IMarkDirty::SYNC_DIRTY))){
           proto->set_exp(mExp);
       }
       if(all || (db && 1) || (sync && 0 && isDirty(5, IMarkDirty::SYNC_DIRTY))){
           proto->set_offtime(mOffTime);
       }
       if(all || (db && 1) || (sync && 1 && isDirty(6, IMarkDirty::SYNC_DIRTY))){
           proto->set_diamond(mDiamond);
       }
       if(all || (db && 1) || (sync && 1 && isDirty(7, IMarkDirty::SYNC_DIRTY))){
           proto->set_gold(mGold);
       }
       if(all || (db && 1) || (sync && 1 && isDirty(8, IMarkDirty::SYNC_DIRTY))){
           proto->set_mobility(mMobility);
       }
       if(all || (db && 1) || (sync && 1 && isDirty(9, IMarkDirty::SYNC_DIRTY))){
           proto->set_heroline(mHeroLine);
       }
       if(all || (db && 1) || (sync && 1 && isDirty(10, IMarkDirty::SYNC_DIRTY))){
           proto->set_id(mId);
       }
   }
   void fromProto(const BaseInfoProto& proto){
       mEliteLine = proto.eliteline();
       mName = proto.name();
       mLevel = proto.level();
       mMainLine = proto.mainline();
       mExp = proto.exp();
       mOffTime = proto.offtime();
       mDiamond = proto.diamond();
       mGold = proto.gold();
       mMobility = proto.mobility();
       mHeroLine = proto.heroline();
       mId = proto.id();
   }
private:
   //精英通关关卡
   int  mEliteLine;
   //角色名
   std::string  mName;
   //角色等级
   int  mLevel;
   //主线通关关卡
   int  mMainLine;
   //角色经验
   int  mExp;
   //最近离线时间
   int  mOffTime;
   //钻石
   int  mDiamond;
   //金币
   int  mGold;
   //移动力
   int  mMobility;
   //英雄通关关卡
   int  mHeroLine;
   //角色id
   std::string  mId;
};

class  SysInfoImpl : public SysInfo, public MarkDirty{
   private: SysInfoImpl(const SysInfoImpl&) = delete;   private: void operator=(const SysInfoImpl&) = delete;public:
   SysInfoImpl(){
       mServerTime = int();
       mOnlinePlayer = int();
   }
   //服务器名
   virtual const char* getServerName(){
       return mServerName.c_str();
   }
   virtual void setServerName(const char* val){
       mServerName = val;
       markDirty(0, IMarkDirty::SYNC_DIRTY);
   }
   //服务器当前时间
   virtual int getServerTime(){
       return mServerTime;
   }
   virtual void setServerTime(int val){
       mServerTime = val;
       markDirty(1, IMarkDirty::SYNC_DIRTY);
   }
   //在线用户数
   virtual int getOnlinePlayer(){
       return mOnlinePlayer;
   }
   virtual void setOnlinePlayer(int val){
       mOnlinePlayer = val;
       markDirty(2, IMarkDirty::SYNC_DIRTY);
   }
   void toProto(SysInfoProto* proto, bool db, bool sync, bool all=false){
       if(all || (db && 0) || (sync && 1 && isDirty(0, IMarkDirty::SYNC_DIRTY))){
           proto->set_servername(mServerName);
       }
       if(all || (db && 0) || (sync && 1 && isDirty(1, IMarkDirty::SYNC_DIRTY))){
           proto->set_servertime(mServerTime);
       }
       if(all || (db && 0) || (sync && 1 && isDirty(2, IMarkDirty::SYNC_DIRTY))){
           proto->set_onlineplayer(mOnlinePlayer);
       }
   }
   void fromProto(const SysInfoProto& proto){
       mServerName = proto.servername();
       mServerTime = proto.servertime();
       mOnlinePlayer = proto.onlineplayer();
   }
private:
   //服务器名
   std::string  mServerName;
   //服务器当前时间
   int  mServerTime;
   //在线用户数
   int  mOnlinePlayer;
};

class  CardImpl : public Card, public MarkDirty{
   private: CardImpl(const CardImpl&) = delete;   private: void operator=(const CardImpl&) = delete;public:
   CardImpl(){
       mId = int();
       mLeaderSkill = int();
       mLevel = int();
   }
   //卡牌id
   virtual int getId(){
       return mId;
   }
   virtual void setId(int val){
       mId = val;
       markDirty(0, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
   }
   //队长技能
   virtual int getLeaderSkill(){
       return mLeaderSkill;
   }
   virtual void setLeaderSkill(int val){
       mLeaderSkill = val;
       markDirty(1, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
   }
   //卡牌等级
   virtual int getLevel(){
       return mLevel;
   }
   virtual void setLevel(int val){
       mLevel = val;
       markDirty(2, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
   }
   void toProto(CardProto* proto, bool db, bool sync, bool all=false){
       if(all || (db && 1) || (sync && 1 && isDirty(0, IMarkDirty::SYNC_DIRTY))){
           proto->set_id(mId);
       }
       if(all || (db && 1) || (sync && 1 && isDirty(1, IMarkDirty::SYNC_DIRTY))){
           proto->set_leaderskill(mLeaderSkill);
       }
       if(all || (db && 1) || (sync && 1 && isDirty(2, IMarkDirty::SYNC_DIRTY))){
           proto->set_level(mLevel);
       }
   }
   void fromProto(const CardProto& proto){
       mId = proto.id();
       mLeaderSkill = proto.leaderskill();
       mLevel = proto.level();
   }
private:
   //卡牌id
   int  mId;
   //队长技能
   int  mLeaderSkill;
   //卡牌等级
   int  mLevel;
};

class  PackageImpl : public Package, public MarkDirty{
   private: PackageImpl(const PackageImpl&) = delete;   private: void operator=(const PackageImpl&) = delete;public:
   PackageImpl(){
       for(int i=0; i<60; i++){;
           mSlot[i].init(this, 0, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
       }
   }
   //背包物品
   virtual int sizeSlot(){return 60;}
   virtual Card& getSlot(int idx){
       if(idx < 0 || idx >= 60){throw std::out_of_range("Slot");}
       return mSlot[idx];
   }
   void toProto(PackageProto* proto, bool db, bool sync, bool all=false){
       if(all || (db && 1) || (sync && 1 && isDirty(0, IMarkDirty::SYNC_DIRTY))){
           if (all || (db && 1) || (sync && 1 && mSlot[0].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[0].toProto(proto->mutable_slot()->mutable__v0(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[1].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[1].toProto(proto->mutable_slot()->mutable__v1(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[2].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[2].toProto(proto->mutable_slot()->mutable__v2(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[3].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[3].toProto(proto->mutable_slot()->mutable__v3(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[4].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[4].toProto(proto->mutable_slot()->mutable__v4(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[5].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[5].toProto(proto->mutable_slot()->mutable__v5(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[6].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[6].toProto(proto->mutable_slot()->mutable__v6(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[7].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[7].toProto(proto->mutable_slot()->mutable__v7(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[8].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[8].toProto(proto->mutable_slot()->mutable__v8(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[9].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[9].toProto(proto->mutable_slot()->mutable__v9(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[10].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[10].toProto(proto->mutable_slot()->mutable__v10(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[11].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[11].toProto(proto->mutable_slot()->mutable__v11(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[12].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[12].toProto(proto->mutable_slot()->mutable__v12(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[13].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[13].toProto(proto->mutable_slot()->mutable__v13(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[14].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[14].toProto(proto->mutable_slot()->mutable__v14(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[15].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[15].toProto(proto->mutable_slot()->mutable__v15(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[16].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[16].toProto(proto->mutable_slot()->mutable__v16(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[17].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[17].toProto(proto->mutable_slot()->mutable__v17(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[18].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[18].toProto(proto->mutable_slot()->mutable__v18(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[19].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[19].toProto(proto->mutable_slot()->mutable__v19(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[20].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[20].toProto(proto->mutable_slot()->mutable__v20(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[21].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[21].toProto(proto->mutable_slot()->mutable__v21(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[22].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[22].toProto(proto->mutable_slot()->mutable__v22(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[23].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[23].toProto(proto->mutable_slot()->mutable__v23(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[24].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[24].toProto(proto->mutable_slot()->mutable__v24(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[25].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[25].toProto(proto->mutable_slot()->mutable__v25(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[26].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[26].toProto(proto->mutable_slot()->mutable__v26(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[27].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[27].toProto(proto->mutable_slot()->mutable__v27(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[28].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[28].toProto(proto->mutable_slot()->mutable__v28(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[29].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[29].toProto(proto->mutable_slot()->mutable__v29(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[30].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[30].toProto(proto->mutable_slot()->mutable__v30(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[31].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[31].toProto(proto->mutable_slot()->mutable__v31(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[32].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[32].toProto(proto->mutable_slot()->mutable__v32(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[33].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[33].toProto(proto->mutable_slot()->mutable__v33(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[34].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[34].toProto(proto->mutable_slot()->mutable__v34(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[35].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[35].toProto(proto->mutable_slot()->mutable__v35(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[36].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[36].toProto(proto->mutable_slot()->mutable__v36(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[37].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[37].toProto(proto->mutable_slot()->mutable__v37(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[38].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[38].toProto(proto->mutable_slot()->mutable__v38(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[39].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[39].toProto(proto->mutable_slot()->mutable__v39(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[40].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[40].toProto(proto->mutable_slot()->mutable__v40(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[41].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[41].toProto(proto->mutable_slot()->mutable__v41(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[42].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[42].toProto(proto->mutable_slot()->mutable__v42(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[43].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[43].toProto(proto->mutable_slot()->mutable__v43(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[44].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[44].toProto(proto->mutable_slot()->mutable__v44(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[45].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[45].toProto(proto->mutable_slot()->mutable__v45(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[46].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[46].toProto(proto->mutable_slot()->mutable__v46(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[47].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[47].toProto(proto->mutable_slot()->mutable__v47(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[48].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[48].toProto(proto->mutable_slot()->mutable__v48(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[49].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[49].toProto(proto->mutable_slot()->mutable__v49(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[50].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[50].toProto(proto->mutable_slot()->mutable__v50(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[51].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[51].toProto(proto->mutable_slot()->mutable__v51(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[52].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[52].toProto(proto->mutable_slot()->mutable__v52(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[53].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[53].toProto(proto->mutable_slot()->mutable__v53(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[54].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[54].toProto(proto->mutable_slot()->mutable__v54(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[55].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[55].toProto(proto->mutable_slot()->mutable__v55(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[56].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[56].toProto(proto->mutable_slot()->mutable__v56(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[57].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[57].toProto(proto->mutable_slot()->mutable__v57(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[58].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[58].toProto(proto->mutable_slot()->mutable__v58(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mSlot[59].isDirty(IMarkDirty::SYNC_DIRTY))){
               mSlot[59].toProto(proto->mutable_slot()->mutable__v59(), db, sync, all);
           }
       }
   }
   void fromProto(const PackageProto& proto){
       if (proto.has_slot()){
           if (proto.slot().has__v0()){
               mSlot[0].fromProto(proto.slot()._v0());
           }
           if (proto.slot().has__v1()){
               mSlot[1].fromProto(proto.slot()._v1());
           }
           if (proto.slot().has__v2()){
               mSlot[2].fromProto(proto.slot()._v2());
           }
           if (proto.slot().has__v3()){
               mSlot[3].fromProto(proto.slot()._v3());
           }
           if (proto.slot().has__v4()){
               mSlot[4].fromProto(proto.slot()._v4());
           }
           if (proto.slot().has__v5()){
               mSlot[5].fromProto(proto.slot()._v5());
           }
           if (proto.slot().has__v6()){
               mSlot[6].fromProto(proto.slot()._v6());
           }
           if (proto.slot().has__v7()){
               mSlot[7].fromProto(proto.slot()._v7());
           }
           if (proto.slot().has__v8()){
               mSlot[8].fromProto(proto.slot()._v8());
           }
           if (proto.slot().has__v9()){
               mSlot[9].fromProto(proto.slot()._v9());
           }
           if (proto.slot().has__v10()){
               mSlot[10].fromProto(proto.slot()._v10());
           }
           if (proto.slot().has__v11()){
               mSlot[11].fromProto(proto.slot()._v11());
           }
           if (proto.slot().has__v12()){
               mSlot[12].fromProto(proto.slot()._v12());
           }
           if (proto.slot().has__v13()){
               mSlot[13].fromProto(proto.slot()._v13());
           }
           if (proto.slot().has__v14()){
               mSlot[14].fromProto(proto.slot()._v14());
           }
           if (proto.slot().has__v15()){
               mSlot[15].fromProto(proto.slot()._v15());
           }
           if (proto.slot().has__v16()){
               mSlot[16].fromProto(proto.slot()._v16());
           }
           if (proto.slot().has__v17()){
               mSlot[17].fromProto(proto.slot()._v17());
           }
           if (proto.slot().has__v18()){
               mSlot[18].fromProto(proto.slot()._v18());
           }
           if (proto.slot().has__v19()){
               mSlot[19].fromProto(proto.slot()._v19());
           }
           if (proto.slot().has__v20()){
               mSlot[20].fromProto(proto.slot()._v20());
           }
           if (proto.slot().has__v21()){
               mSlot[21].fromProto(proto.slot()._v21());
           }
           if (proto.slot().has__v22()){
               mSlot[22].fromProto(proto.slot()._v22());
           }
           if (proto.slot().has__v23()){
               mSlot[23].fromProto(proto.slot()._v23());
           }
           if (proto.slot().has__v24()){
               mSlot[24].fromProto(proto.slot()._v24());
           }
           if (proto.slot().has__v25()){
               mSlot[25].fromProto(proto.slot()._v25());
           }
           if (proto.slot().has__v26()){
               mSlot[26].fromProto(proto.slot()._v26());
           }
           if (proto.slot().has__v27()){
               mSlot[27].fromProto(proto.slot()._v27());
           }
           if (proto.slot().has__v28()){
               mSlot[28].fromProto(proto.slot()._v28());
           }
           if (proto.slot().has__v29()){
               mSlot[29].fromProto(proto.slot()._v29());
           }
           if (proto.slot().has__v30()){
               mSlot[30].fromProto(proto.slot()._v30());
           }
           if (proto.slot().has__v31()){
               mSlot[31].fromProto(proto.slot()._v31());
           }
           if (proto.slot().has__v32()){
               mSlot[32].fromProto(proto.slot()._v32());
           }
           if (proto.slot().has__v33()){
               mSlot[33].fromProto(proto.slot()._v33());
           }
           if (proto.slot().has__v34()){
               mSlot[34].fromProto(proto.slot()._v34());
           }
           if (proto.slot().has__v35()){
               mSlot[35].fromProto(proto.slot()._v35());
           }
           if (proto.slot().has__v36()){
               mSlot[36].fromProto(proto.slot()._v36());
           }
           if (proto.slot().has__v37()){
               mSlot[37].fromProto(proto.slot()._v37());
           }
           if (proto.slot().has__v38()){
               mSlot[38].fromProto(proto.slot()._v38());
           }
           if (proto.slot().has__v39()){
               mSlot[39].fromProto(proto.slot()._v39());
           }
           if (proto.slot().has__v40()){
               mSlot[40].fromProto(proto.slot()._v40());
           }
           if (proto.slot().has__v41()){
               mSlot[41].fromProto(proto.slot()._v41());
           }
           if (proto.slot().has__v42()){
               mSlot[42].fromProto(proto.slot()._v42());
           }
           if (proto.slot().has__v43()){
               mSlot[43].fromProto(proto.slot()._v43());
           }
           if (proto.slot().has__v44()){
               mSlot[44].fromProto(proto.slot()._v44());
           }
           if (proto.slot().has__v45()){
               mSlot[45].fromProto(proto.slot()._v45());
           }
           if (proto.slot().has__v46()){
               mSlot[46].fromProto(proto.slot()._v46());
           }
           if (proto.slot().has__v47()){
               mSlot[47].fromProto(proto.slot()._v47());
           }
           if (proto.slot().has__v48()){
               mSlot[48].fromProto(proto.slot()._v48());
           }
           if (proto.slot().has__v49()){
               mSlot[49].fromProto(proto.slot()._v49());
           }
           if (proto.slot().has__v50()){
               mSlot[50].fromProto(proto.slot()._v50());
           }
           if (proto.slot().has__v51()){
               mSlot[51].fromProto(proto.slot()._v51());
           }
           if (proto.slot().has__v52()){
               mSlot[52].fromProto(proto.slot()._v52());
           }
           if (proto.slot().has__v53()){
               mSlot[53].fromProto(proto.slot()._v53());
           }
           if (proto.slot().has__v54()){
               mSlot[54].fromProto(proto.slot()._v54());
           }
           if (proto.slot().has__v55()){
               mSlot[55].fromProto(proto.slot()._v55());
           }
           if (proto.slot().has__v56()){
               mSlot[56].fromProto(proto.slot()._v56());
           }
           if (proto.slot().has__v57()){
               mSlot[57].fromProto(proto.slot()._v57());
           }
           if (proto.slot().has__v58()){
               mSlot[58].fromProto(proto.slot()._v58());
           }
           if (proto.slot().has__v59()){
               mSlot[59].fromProto(proto.slot()._v59());
           }
       }
   }
private:
   //背包物品
   CardImpl  mSlot[60];
};

class  TeamInfoImpl : public TeamInfo, public MarkDirty{
   private: TeamInfoImpl(const TeamInfoImpl&) = delete;   private: void operator=(const TeamInfoImpl&) = delete;public:
   TeamInfoImpl(){
       for(int i=0; i<5; i++){;
           mTeamMember[i].init(this, 0, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
       }
   }
   //团队成员
   virtual int sizeTeamMember(){return 5;}
   virtual Card& getTeamMember(int idx){
       if(idx < 0 || idx >= 5){throw std::out_of_range("TeamMember");}
       return mTeamMember[idx];
   }
   void toProto(TeamInfoProto* proto, bool db, bool sync, bool all=false){
       if(all || (db && 1) || (sync && 1 && isDirty(0, IMarkDirty::SYNC_DIRTY))){
           if (all || (db && 1) || (sync && 1 && mTeamMember[0].isDirty(IMarkDirty::SYNC_DIRTY))){
               mTeamMember[0].toProto(proto->mutable_teammember()->mutable__v0(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mTeamMember[1].isDirty(IMarkDirty::SYNC_DIRTY))){
               mTeamMember[1].toProto(proto->mutable_teammember()->mutable__v1(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mTeamMember[2].isDirty(IMarkDirty::SYNC_DIRTY))){
               mTeamMember[2].toProto(proto->mutable_teammember()->mutable__v2(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mTeamMember[3].isDirty(IMarkDirty::SYNC_DIRTY))){
               mTeamMember[3].toProto(proto->mutable_teammember()->mutable__v3(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mTeamMember[4].isDirty(IMarkDirty::SYNC_DIRTY))){
               mTeamMember[4].toProto(proto->mutable_teammember()->mutable__v4(), db, sync, all);
           }
       }
   }
   void fromProto(const TeamInfoProto& proto){
       if (proto.has_teammember()){
           if (proto.teammember().has__v0()){
               mTeamMember[0].fromProto(proto.teammember()._v0());
           }
           if (proto.teammember().has__v1()){
               mTeamMember[1].fromProto(proto.teammember()._v1());
           }
           if (proto.teammember().has__v2()){
               mTeamMember[2].fromProto(proto.teammember()._v2());
           }
           if (proto.teammember().has__v3()){
               mTeamMember[3].fromProto(proto.teammember()._v3());
           }
           if (proto.teammember().has__v4()){
               mTeamMember[4].fromProto(proto.teammember()._v4());
           }
       }
   }
private:
   //团队成员
   CardImpl  mTeamMember[5];
};

class  PlayerDataImpl : public PlayerData, public MarkDirty{
   private: PlayerDataImpl(const PlayerDataImpl&) = delete;   private: void operator=(const PlayerDataImpl&) = delete;public:
   PlayerDataImpl(){
       for(int i=0; i<30; i++){;
           mFriends[i].init(this, 0, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
       }
       mTeamInfo.init(this, 1, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
       mSysInfo.init(this, 2, IMarkDirty::SYNC_DIRTY);
       mPackage.init(this, 3, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
       mBaseInfo.init(this, 4, IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY);
   }
   //背包
   virtual int sizeFriends(){return 30;}
   virtual FriendInfo& getFriends(int idx){
       if(idx < 0 || idx >= 30){throw std::out_of_range("Friends");}
       return mFriends[idx];
   }
   //队伍信息
   virtual TeamInfo& getTeamInfo(){
       return mTeamInfo;
   }
   //系统信息
   virtual SysInfo& getSysInfo(){
       return mSysInfo;
   }
   //背包
   virtual Package& getPackage(){
       return mPackage;
   }
   //基本信息
   virtual BaseInfo& getBaseInfo(){
       return mBaseInfo;
   }
   void toProto(PlayerDataProto* proto, bool db, bool sync, bool all=false){
       if(all || (db && 1) || (sync && 1 && isDirty(0, IMarkDirty::SYNC_DIRTY))){
           if (all || (db && 1) || (sync && 1 && mFriends[0].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[0].toProto(proto->mutable_friends()->mutable__v0(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mFriends[1].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[1].toProto(proto->mutable_friends()->mutable__v1(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mFriends[2].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[2].toProto(proto->mutable_friends()->mutable__v2(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mFriends[3].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[3].toProto(proto->mutable_friends()->mutable__v3(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mFriends[4].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[4].toProto(proto->mutable_friends()->mutable__v4(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mFriends[5].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[5].toProto(proto->mutable_friends()->mutable__v5(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mFriends[6].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[6].toProto(proto->mutable_friends()->mutable__v6(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mFriends[7].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[7].toProto(proto->mutable_friends()->mutable__v7(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mFriends[8].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[8].toProto(proto->mutable_friends()->mutable__v8(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mFriends[9].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[9].toProto(proto->mutable_friends()->mutable__v9(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mFriends[10].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[10].toProto(proto->mutable_friends()->mutable__v10(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mFriends[11].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[11].toProto(proto->mutable_friends()->mutable__v11(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mFriends[12].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[12].toProto(proto->mutable_friends()->mutable__v12(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mFriends[13].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[13].toProto(proto->mutable_friends()->mutable__v13(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mFriends[14].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[14].toProto(proto->mutable_friends()->mutable__v14(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mFriends[15].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[15].toProto(proto->mutable_friends()->mutable__v15(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mFriends[16].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[16].toProto(proto->mutable_friends()->mutable__v16(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mFriends[17].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[17].toProto(proto->mutable_friends()->mutable__v17(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mFriends[18].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[18].toProto(proto->mutable_friends()->mutable__v18(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mFriends[19].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[19].toProto(proto->mutable_friends()->mutable__v19(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mFriends[20].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[20].toProto(proto->mutable_friends()->mutable__v20(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mFriends[21].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[21].toProto(proto->mutable_friends()->mutable__v21(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mFriends[22].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[22].toProto(proto->mutable_friends()->mutable__v22(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mFriends[23].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[23].toProto(proto->mutable_friends()->mutable__v23(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mFriends[24].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[24].toProto(proto->mutable_friends()->mutable__v24(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mFriends[25].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[25].toProto(proto->mutable_friends()->mutable__v25(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mFriends[26].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[26].toProto(proto->mutable_friends()->mutable__v26(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mFriends[27].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[27].toProto(proto->mutable_friends()->mutable__v27(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mFriends[28].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[28].toProto(proto->mutable_friends()->mutable__v28(), db, sync, all);
           }
           if (all || (db && 1) || (sync && 1 && mFriends[29].isDirty(IMarkDirty::SYNC_DIRTY))){
               mFriends[29].toProto(proto->mutable_friends()->mutable__v29(), db, sync, all);
           }
       }
       if(all || (db && 1) || (sync && 1 && isDirty(1, IMarkDirty::SYNC_DIRTY))){
           mTeamInfo.toProto(proto->mutable_teaminfo(), db, sync, all);
       }
       if(all || (db && 0) || (sync && 1 && isDirty(2, IMarkDirty::SYNC_DIRTY))){
           mSysInfo.toProto(proto->mutable_sysinfo(), db, sync, all);
       }
       if(all || (db && 1) || (sync && 1 && isDirty(3, IMarkDirty::SYNC_DIRTY))){
           mPackage.toProto(proto->mutable_package(), db, sync, all);
       }
       if(all || (db && 1) || (sync && 1 && isDirty(4, IMarkDirty::SYNC_DIRTY))){
           mBaseInfo.toProto(proto->mutable_baseinfo(), db, sync, all);
       }
   }
   void fromProto(const PlayerDataProto& proto){
       if (proto.has_friends()){
           if (proto.friends().has__v0()){
               mFriends[0].fromProto(proto.friends()._v0());
           }
           if (proto.friends().has__v1()){
               mFriends[1].fromProto(proto.friends()._v1());
           }
           if (proto.friends().has__v2()){
               mFriends[2].fromProto(proto.friends()._v2());
           }
           if (proto.friends().has__v3()){
               mFriends[3].fromProto(proto.friends()._v3());
           }
           if (proto.friends().has__v4()){
               mFriends[4].fromProto(proto.friends()._v4());
           }
           if (proto.friends().has__v5()){
               mFriends[5].fromProto(proto.friends()._v5());
           }
           if (proto.friends().has__v6()){
               mFriends[6].fromProto(proto.friends()._v6());
           }
           if (proto.friends().has__v7()){
               mFriends[7].fromProto(proto.friends()._v7());
           }
           if (proto.friends().has__v8()){
               mFriends[8].fromProto(proto.friends()._v8());
           }
           if (proto.friends().has__v9()){
               mFriends[9].fromProto(proto.friends()._v9());
           }
           if (proto.friends().has__v10()){
               mFriends[10].fromProto(proto.friends()._v10());
           }
           if (proto.friends().has__v11()){
               mFriends[11].fromProto(proto.friends()._v11());
           }
           if (proto.friends().has__v12()){
               mFriends[12].fromProto(proto.friends()._v12());
           }
           if (proto.friends().has__v13()){
               mFriends[13].fromProto(proto.friends()._v13());
           }
           if (proto.friends().has__v14()){
               mFriends[14].fromProto(proto.friends()._v14());
           }
           if (proto.friends().has__v15()){
               mFriends[15].fromProto(proto.friends()._v15());
           }
           if (proto.friends().has__v16()){
               mFriends[16].fromProto(proto.friends()._v16());
           }
           if (proto.friends().has__v17()){
               mFriends[17].fromProto(proto.friends()._v17());
           }
           if (proto.friends().has__v18()){
               mFriends[18].fromProto(proto.friends()._v18());
           }
           if (proto.friends().has__v19()){
               mFriends[19].fromProto(proto.friends()._v19());
           }
           if (proto.friends().has__v20()){
               mFriends[20].fromProto(proto.friends()._v20());
           }
           if (proto.friends().has__v21()){
               mFriends[21].fromProto(proto.friends()._v21());
           }
           if (proto.friends().has__v22()){
               mFriends[22].fromProto(proto.friends()._v22());
           }
           if (proto.friends().has__v23()){
               mFriends[23].fromProto(proto.friends()._v23());
           }
           if (proto.friends().has__v24()){
               mFriends[24].fromProto(proto.friends()._v24());
           }
           if (proto.friends().has__v25()){
               mFriends[25].fromProto(proto.friends()._v25());
           }
           if (proto.friends().has__v26()){
               mFriends[26].fromProto(proto.friends()._v26());
           }
           if (proto.friends().has__v27()){
               mFriends[27].fromProto(proto.friends()._v27());
           }
           if (proto.friends().has__v28()){
               mFriends[28].fromProto(proto.friends()._v28());
           }
           if (proto.friends().has__v29()){
               mFriends[29].fromProto(proto.friends()._v29());
           }
       }
       mTeamInfo.fromProto(proto.teaminfo());
       mSysInfo.fromProto(proto.sysinfo());
       mPackage.fromProto(proto.package());
       mBaseInfo.fromProto(proto.baseinfo());
   }
private:
   //背包
   FriendInfoImpl  mFriends[30];
   //队伍信息
   TeamInfoImpl  mTeamInfo;
   //系统信息
   SysInfoImpl  mSysInfo;
   //背包
   PackageImpl  mPackage;
   //基本信息
   BaseInfoImpl  mBaseInfo;
};



#endif
