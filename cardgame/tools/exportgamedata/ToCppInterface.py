# coding:utf-8

__author__ = 'xt'

from exportgamedata.AnalysisGameData import AnalysisGameData


def writehead(ofile):
    ofile.write("\n")
    ofile.write("#ifndef _GAMEDATA_HEAD_\n")
    ofile.write("#define _GAMEDATA_HEAD_\n\n")


def writetail(ofile):
    ofile.write("\n\n#endif\n")


def protoType(rawt):
    if rawt == "int":
        return "int"
    if rawt == "str":
        return "const char*"
    return rawt + "&"


def isCompoundType(rawt):
    if rawt == "int" or rawt == "str":
        return False
    return True


def writemsg(ofile, key, val):
    ofile.write("class  {}{{\n".format(key))
    ofile.write("public:\n")
    for ik, iv in val.items():
        ofile.write("   //{}\n".format(iv["desc"]))
        # 基础类型，单值
        if iv["count"] == 1 and (not isCompoundType(iv["type"])):
            ofile.write("   virtual {} get{}() = 0;\n".format(protoType(iv["type"]), ik))
            ofile.write("   virtual void set{}({} val) = 0;\n".format(ik, protoType(iv["type"])))
        # 复合类型，单值
        elif iv["count"] == 1 and (isCompoundType(iv["type"])):
            ofile.write("   virtual {} get{}() = 0;\n".format(protoType(iv["type"]), ik))
        # 基本类型，多值
        elif iv["count"] > 1 and (not isCompoundType(iv["type"])):
            ofile.write("   virtual int size{}() = 0;\n".format(ik))
            ofile.write("   virtual {} get{}(int idx) = 0;\n".format(protoType(iv["type"]), ik))
            ofile.write("   virtual void set{}(int idx, {} val) = 0;\n".format(ik, protoType(iv["type"])))
        # 复合类型，多值
        elif iv["count"] > 1 and (isCompoundType(iv["type"])):
            ofile.write("   virtual int size{}() = 0;\n".format(ik))
            ofile.write("   virtual {} get{}(int idx) = 0;\n".format(protoType(iv["type"]), ik))

    ofile.write("};\n\n")


class ToCppInterface:
    @staticmethod
    def convert(outfname):
        ofile = open(outfname, 'w')

        writehead(ofile)
        datas = AnalysisGameData.getData()

        for key, val in datas:
            ofile.write("class {};\n".format(key))
        ofile.write("\n")

        for key, val in datas:
            writemsg(ofile, key, val)
        writetail(ofile)
