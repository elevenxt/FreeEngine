# coding:utf-8

__author__ = 'xt'

import os
import sys

datas = []


def isTypeInSet(coll, vt):
    if vt == "int" or vt == "str":
        return True
    return vt in coll


class AnalysisGameData:
    @staticmethod
    def init(gdFile):
        gdFile = os.path.abspath(gdFile)
        gdPath, gdFile = os.path.split(gdFile)

        if not gdPath in sys.path:
            sys.path.append(gdPath)
        import gamedata as gd

        alld = {}
        for val in dir(gd):
            if val.find('__') == 0:
                continue
            alld[val] = getattr(gd, val)

        # 按依赖关系排序
        finded = []
        while True:
            find = True
            for ik, iv in alld.items():
                find = True
                for k, v in iv.items():
                    if not isTypeInSet(finded, v["type"]):
                        find = False
                        break
                if find:
                    finded.append(ik)
                    datas.append((ik, iv))
                    del alld[ik]
                    break
            if not find and len(alld) > 0:
                raise Exception("loop depends")
            if len(alld) == 0:
                break

    @staticmethod
    def dbgshow():
        for k, v in datas.items():
            print(k, v)

    @staticmethod
    def getData():
        return datas
