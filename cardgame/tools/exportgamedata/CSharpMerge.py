# coding:utf-8

from exportgamedata.AnalysisGameData import AnalysisGameData

def isCompoundType(rawt):
    if rawt == "int" or rawt == "str":
        return False
    return True


def writehead(ofile):
    ofile.write("/**这是由程序生成的代码，不要尝试手动修改!*/\n\n")
    ofile.write("namespace gamedata{public class ProtoMerge{\n")


def writetail(ofile):
    ofile.write("}}\n")


def writemsg(ofile, key, val):
    ofile.write("public static void merge(ref {} to, {}Proto from){{\n".format(key, key))

    ofile.write("   if(from == null) return;\n")
    ofile.write("   if(to == null) {{to = new {}();}}\n".format(key))

    for ik, iv in val.items():
        count = iv["count"]
        # 基础类型，单值
        if iv["count"] == 1 and (not isCompoundType(iv["type"])):
            ofile.write("   if(from.{}Specified) {{to.m{} = from.{};to.isDirty{}=true;}}\n".format(ik, ik, ik, ik))
        # 复合类型，单值
        elif iv["count"] == 1 and (isCompoundType(iv["type"])):
            ofile.write("   if(from.{} != null){{\n".format(ik))
            ofile.write("       merge(ref to.m{}, from.{});\n".format(ik, ik))
            ofile.write("       to.isDirty = true;\n")
            ofile.write("   }\n")

        # 基础类型，多值
        if iv["count"] > 1 and (not isCompoundType(iv["type"])):
            ofile.write(
                "   for(int i=0; i<from.{}.Count; i++){{to.m{}[i] = from.{}[i];to.isDirty{}[i] = true;}}\n".format(ik,
                                                                                                                   ik,
                                                                                                                   ik,
                                                                                                                   ik))
        # 复合类型，多值
        elif iv["count"] > 1 and (isCompoundType(iv["type"])):
            for i in range(iv["count"]):
                ofile.write("   if (from.{} != null && from.{}._v{} != null) {{\n".format(ik, ik, i))
                ofile.write("       merge(ref to.m{}[{}], from.{}._v{});\n".format(ik, i, ik, i))
                ofile.write("       to.isDirty = true;\n")
                ofile.write("   }\n")

    ofile.write("}\n")


class CSharpMerge:
    @staticmethod
    def convert(outfname):
        ofile = open(outfname, 'w')

        writehead(ofile)
        datas = AnalysisGameData.getData()

        for key, val in datas:
            writemsg(ofile, key, val)
        writetail(ofile)
