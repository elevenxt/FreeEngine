__author__ = 'xt'

import os

from exportgamedata.AnalysisGameData import AnalysisGameData
from exportgamedata.CSharpMerge import CSharpMerge
from exportgamedata.ToCharpImpl import ToCharpImpl
from exportgamedata.ToCppImpl import ToCppImpl
from exportgamedata.ToCppInterface import ToCppInterface
from exportgamedata.ToProtobuf import ToProtobuf


class ExportGameData:
    @staticmethod
    def run(gameDataFile, protoDir, cppDir, csDir):
        AnalysisGameData.init(gameDataFile)
        ToProtobuf.convert(os.path.join(protoDir, "gamedata.proto"))
        ToCppInterface.convert(os.path.join(cppDir, "GameData.h"))
        ToCppImpl.convert(os.path.join(cppDir, "GameDataImpl.h"))
        CSharpMerge.convert(os.path.join(csDir, "ProtoMerge.cs"))
        ToCharpImpl.convert(os.path.join(csDir, "PlayerData.cs"))
