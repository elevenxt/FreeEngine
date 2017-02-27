# encoding: utf-8
__author__ = 'xt'

import os

dir = {
    # proto.exe 路径
    "proto.exe": "./protobuf/proto.exe",
    # proto文件目录
    "proto": "../proto/",
    # proto生成的c++文件路径
    "proto_target_cpp": "../server/proto/",
    # proto生成的c#文件路径
    "proto_target_cs": "../client/cardgame/Assets/logic/proto/",

    # 策划表格
    "cfg": "../tables/",
    # 读表代码c++生成路径
    "cfg_target_cpp": "../server/proto/",
    # 读表代码cs生成路径
    "cfg_target_cs": "../client/cardgame/Assets/logic/config/",
    # 表格数据生成目录
    "cfg_data_server": "../../bin/cardgame/cfg/",
    "cfg_data_client": "../client/cardgame/Assets/res/cfgdata/",
}


def makeDir(ddir):
    if not os.path.exists(ddir):
        os.makedirs(ddir)


if __name__ == "__main__":
    for ddir in dir.values():
        makeDir(ddir)

    # 1.生成数据同步代码，生成cpp代码，c#代码和一个proto文件
    from exportgamedata.ExportGameData import ExportGameData

    ExportGameData.run(os.path.join(dir["proto"], "gamedata.py") \
                       , dir["proto"], dir["proto_target_cpp"], dir["proto_target_cs"])

    # 2.生成proto代码
    from generateproto.makeproto import MakeProto

    MakeProto.run(dir["proto.exe"], dir["proto"] + "csmsg.proto", dir["proto_target_cpp"], dir["proto_target_cs"], True)
    MakeProto.run(dir["proto.exe"], dir["proto"] + "scmsg.proto", dir["proto_target_cpp"], dir["proto_target_cs"], True)
    MakeProto.run(dir["proto.exe"], dir["proto"] + "gamedata.proto", dir["proto_target_cpp"], dir["proto_target_cs"],
                  False)

    # 3.生成配置数据代码和数据
    from exportcfg.ExportCfg import ExportCfg

    ExportCfg.run(dir["cfg"], [dir["cfg_data_server"], dir["cfg_data_client"]] \
                  , dir["cfg_target_cpp"], dir["cfg_target_cs"])
