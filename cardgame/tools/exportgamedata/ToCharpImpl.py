# coding:utf-8

__author__ = 'xt'

from exportgamedata.AnalysisGameData import AnalysisGameData


def writehead(ofile):
    ofile.write("\n")
    ofile.write("\n")


def writetail(ofile):
    ofile.write("\n\n\n")


def toCSharpType(rawt):
    if rawt == "int":
        return "int"
    if rawt == "str":
        return "byte[]"
    return rawt


def isCompoundType(rawt):
    if rawt == "int" or rawt == "str":
        return False
    return True


def writemsg(ofile, key, val):
    vali = []
    idx = -1
    for ik, iv in val.items():
        idx += 1
        vali.append((ik, iv, idx))

    ofile.write("public class  {}{{\n".format(key))

    for ik, iv, idx in vali:
        cppType = toCSharpType(iv["type"])
        ofile.write("   //{}\n".format(iv["desc"]))
        # 单值
        if iv["count"] == 1:
            ofile.write("   public {}  m{};\n".format(cppType, ik))
            ofile.write("   public bool  isDirty{};\n".format(ik))
        # 多值
        elif iv["count"] > 1:
            ofile.write("   public {}[]  m{} =new {}[{}];\n".format(cppType, ik, cppType, iv["count"]))
            ofile.write("   public bool[]  isDirty{} =new bool[{}];\n".format(ik, iv["count"]))

    ofile.write("   public bool  isDirty;\n")

    ofile.write("   public void clearDirty(){\n")
    for ik, iv, idx in vali:
        # 单值
        if iv["count"] == 1:
            if isCompoundType(iv["type"]):
                ofile.write("       if(isDirty{}){{m{}.clearDirty();}}\n".format(ik, ik))
            ofile.write("       isDirty{} = false;\n".format(ik))
        # 多值
        elif iv["count"] > 1:
            if isCompoundType(iv["type"]):
                ofile.write("       for (int i=0; i<{}; i++) if(isDirty{}[i]){{m{}[i].clearDirty();}}\n" \
                            .format(iv["count"], ik, ik))
            ofile.write("       for (int i=0; i<{}; i++){{ isDirty{}[i] = false;}}\n".format(iv["count"], ik))
    ofile.write("   }\n")

    ofile.write("};\n\n")
    pass


class ToCharpImpl:
    @staticmethod
    def convert(outfname):
        ofile = open(outfname, 'w')

        writehead(ofile)
        datas = AnalysisGameData.getData()

        ofile.write("/**这是由程序生成的代码，不要尝试手动修改!*/\n")
        for key, val in datas:
            writemsg(ofile, key, val)
        writetail(ofile)
