#coding:utf-8

SysInfo = {
    "ServerTime":   {"type":"int", "id":1, "db":0, "sync":1, "count":1, "desc":"服务器当前时间"},
    "ServerName":   {"type":"str", "id":2, "db":0, "sync":1, "count":1, "desc":"服务器名"},
    "OnlinePlayer": {"type":"int", "id":3, "db":0, "sync":1, "count":1, "desc":"在线用户数"},
}

BaseInfo = {
    "Id":       {"type":"str", "id":1, "db":1, "sync":1, "count":1, "desc":"角色id"},
    "Name":     {"type":"str", "id":2, "db":1, "sync":1, "count":1, "desc":"角色名"},
    "Level":    {"type":"int", "id":3, "db":1, "sync":1, "count":1, "desc":"角色等级"},
    "Diamond":  {"type":"int", "id":4, "db":1, "sync":1, "count":1, "desc":"钻石"},
    "Gold":     {"type":"int", "id":5, "db":1, "sync":1, "count":1, "desc":"金币"},
    "Mobility": {"type":"int", "id":6, "db":1, "sync":1, "count":1, "desc":"移动力"},
    "Exp":      {"type":"int", "id":7, "db":1, "sync":1, "count":1, "desc":"角色经验"},
    "MainLine": {"type":"int", "id":8, "db":1, "sync":1, "count":1, "desc":"主线通关关卡"},
    "EliteLine":{"type":"int", "id":9, "db":1, "sync":1, "count":1, "desc":"精英通关关卡"},	
    "OffTime":  {"type":"int", "id":10, "db":1, "sync":0, "count":1, "desc":"最近离线时间"},
	"HeroLine":	{"type":"int", "id":11, "db":1, "sync":1, "count":1, "desc":"英雄通关关卡"},
}

Card = {
    "Id":       {"type":"int", "id":1, "db":1, "sync":1, "count":1, "desc":"卡牌id"},
    "Level":    {"type":"int", "id":2, "db":1, "sync":1, "count":1, "desc":"卡牌等级"},
    "LeaderSkill":{"type":"int", "id":3, "db":1, "sync":1, "count":1, "desc":"队长技能"},
}

TeamInfo = {
    "TeamMember":   {"type":"Card", "id":1, "db":1, "sync":1, "count":5, "desc":"团队成员"},
}

Package = {
    "Slot":   {"type":"Card", "id":1, "db":1, "sync":1, "count":60, "desc":"背包物品"},
}

PlayerSummary = {
    "Id":       {"type":"str", "id":1, "db":1, "sync":1, "count":1, "desc":"id"},
    "Name":     {"type":"str", "id":2, "db":1, "sync":1, "count":1, "desc":"角色名"},
    "Level":    {"type":"int", "id":3, "db":1, "sync":1, "count":1, "desc":"等级"},
}

Guild = {
    "Id":       {"type":"int", "id":1, "db":1, "sync":1, "count":1, "desc":"公会id"},
    "Chairman": {"type":"int", "id":2, "db":1, "sync":1, "count":1, "desc":"会长id"},
    "Name":     {"type":"str", "id":3, "db":1, "sync":1, "count":1, "desc":"公会名"},
    "Level":    {"type":"int", "id":4, "db":1, "sync":1, "count":1, "desc":"公会等级"},
    "GuildMember":{"type":"PlayerSummary", "id":5, "db":1, "sync":1, "count":30, "desc":"公会成员"},
}

FriendInfo = {
	"Info":		{"type":"PlayerSummary", "id":1, "db":1, "sync":1, "count":1, "desc":"基本信息"},
	"Mobility":	{"type":"int", "id":2, "db":1, "sync":1, "count":1, "desc":"可以领取的移动力"},
}

PlayerData = {
    "SysInfo":  {"type":"SysInfo", "id":1, "db":0, "sync":1, "count":1, "desc":"系统信息"},
    "BaseInfo": {"type":"BaseInfo", "id":2, "db":1, "sync":1, "count":1, "desc":"基本信息"},
    "TeamInfo": {"type":"TeamInfo", "id":3, "db":1, "sync":1, "count":1, "desc":"队伍信息"},
    "Package":  {"type":"Package", "id":4, "db":1, "sync":1, "count":1, "desc":"背包"},
	"Friends":  {"type":"FriendInfo", "id":5, "db":1, "sync":1, "count":30, "desc":"背包"},
}

