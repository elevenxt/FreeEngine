# coding:utf-8

__author__ = 'xt'

from exportgamedata.AnalysisGameData import AnalysisGameData


def writehead(ofile):
    ofile.write("\n")
    ofile.write("#ifndef _GAMEDATA_IMPL_\n")
    ofile.write("#define _GAMEDATA_IMPL_\n\n")
    ofile.write("#include <exception>\n")


def writetail(ofile):
    ofile.write("\n\n#endif\n")


def toCppInterfaceType(rawt):
    if rawt == "int":
        return "int"
    if rawt == "str":
        return "const char*"
    return rawt


def implToInterPostFix(rawt):
    if rawt == "str":
        return ".c_str()"
    return ""


def toCppImplType(rawt):
    if rawt == "int":
        return "int"
    if rawt == "str":
        return "std::string"
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

    ofile.write("class  {}Impl : public {}, public MarkDirty{{\n".format(key, key))
    ofile.write("   private: {}Impl(const {}Impl&) = delete;".format(key, key))
    ofile.write("   private: void operator=(const {}Impl&) = delete;".format(key))

    ofile.write("public:\n")
    # 构造函数
    ofile.write("   {}Impl(){{\n".format(key))
    for ik, iv, idx in vali:
        count = iv["count"]
        status = "0"
        if iv["db"] != 0 and iv["sync"] != 0:
            status = "IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY"
        elif iv["db"] != 0 and iv["sync"] == 0:
            status = "IMarkDirty::DB_DIRTY"
        elif iv["db"] == 0 and iv["sync"] != 0:
            status = "IMarkDirty::SYNC_DIRTY"

        if isCompoundType(iv["type"]):
            if count == 1:
                ofile.write("       m{}.init(this, {}, {});\n".format(ik, idx, status))
            else:
                ofile.write("       for(int i=0; i<{}; i++){{;\n".format(count))
                ofile.write("           m{}[i].init(this, {}, {});\n".format(ik, idx, status))
                ofile.write("       }\n")
        elif iv["type"] == "int":
            if count == 1:
                ofile.write("       m{} = {}();\n".format(ik, iv["type"]))
            else:
                ofile.write("       for(int i=0; i<{}; i++){{;\n".format(count))
                ofile.write("           m{}[i] = {}();\n".format(ik, iv["type"]))
                ofile.write("       }\n")

    ofile.write("   }\n")

    # get和set函数
    for ik, iv, idx in vali:
        interType = toCppInterfaceType(iv["type"])
        cpp2interfix = implToInterPostFix(iv["type"])

        dirtyType = "0"
        if iv["db"] != 0 and iv["sync"] != 0:
            dirtyType = "IMarkDirty::DB_DIRTY | IMarkDirty::SYNC_DIRTY"
        elif iv["db"] != 0 and iv["sync"] == 0:
            dirtyType = "IMarkDirty::DB_DIRTY"
        elif iv["db"] == 0 and iv["sync"] != 0:
            dirtyType = "IMarkDirty::SYNC_DIRTY"

        ofile.write("   //{}\n".format(iv["desc"]))
        # 基础类型，单值
        if iv["count"] == 1 and (not isCompoundType(iv["type"])):
            ofile.write("   virtual {} get{}(){{\n".format(interType, ik))
            ofile.write("       return m{}{};\n".format(ik, cpp2interfix))
            ofile.write("   }\n")
            ofile.write("   virtual void set{}({} val){{\n".format(ik, interType))
            ofile.write("       m{} = val;\n".format(ik))
            ofile.write("       markDirty({}, {});\n".format(idx, dirtyType))
            ofile.write("   }\n")
        # 复合类型，单值
        elif iv["count"] == 1 and (isCompoundType(iv["type"])):
            ofile.write("   virtual {}& get{}(){{\n".format(interType, ik))
            ofile.write("       return m{};\n".format(ik))
            ofile.write("   }\n")
        # 基本类型，多值
        elif iv["count"] > 1 and (not isCompoundType(iv["type"])):
            ofile.write("   virtual int size{}(){{return {};}}\n".format(ik, iv["count"]))
            ofile.write("   virtual {} get{}(int idx){{\n".format(interType, ik))
            ofile.write('       if(idx < 0 || idx >= {}){{throw std::out_of_range("{}");}}\n'.format(iv["count"], ik))
            ofile.write("       return m{}[idx]{};\n".format(ik, cpp2interfix))
            ofile.write("   }\n")
            ofile.write("   virtual void set{}(int idx, {} val){{\n".format(ik, interType))
            ofile.write('       if(idx < 0 || idx >= {}){{throw std::out_of_range("{}");}}\n'.format(iv["count"], ik))
            ofile.write("       m{}[idx] = val;\n".format(ik))
            ofile.write("       markDirty({}, {});\n".format(idx, dirtyType))
            ofile.write("   }\n")
        # 复合类型，多值
        elif iv["count"] > 1 and (isCompoundType(iv["type"])):
            ofile.write("   virtual int size{}(){{return {};}}\n".format(ik, iv["count"]))
            ofile.write("   virtual {}& get{}(int idx){{\n".format(interType, ik))
            ofile.write('       if(idx < 0 || idx >= {}){{throw std::out_of_range("{}");}}\n'.format(iv["count"], ik))
            ofile.write("       return m{}[idx];\n".format(ik))
            ofile.write("   }\n")

    ofile.write("   void toProto({}Proto* proto, bool db, bool sync, bool all=false){{\n".format(key))
    for ik, iv, idx in vali:
        ofile.write("       if(all || (db && {}) || (sync && {} && isDirty({}, IMarkDirty::SYNC_DIRTY))){{\n" \
                    .format(iv["db"], iv["sync"], idx))
        # 基础类型，单值
        if iv["count"] == 1 and (not isCompoundType(iv["type"])):
            ofile.write("           proto->set_{}(m{});\n".format(ik.lower(), ik))
        # 复合类型，单值
        elif iv["count"] == 1 and (isCompoundType(iv["type"])):
            ofile.write("           m{}.toProto(proto->mutable_{}(), db, sync, all);\n".format(ik, ik.lower()))
        # 基本类型，多值
        elif iv["count"] > 1 and (not isCompoundType(iv["type"])):
            ofile.write("           for(int i=proto->{}_size(); i<{}; i++){{proto->add_{}({}());}}\n".format(ik.lower(),
                                                                                                             iv[
                                                                                                                 "count"],
                                                                                                             ik.lower(),
                                                                                                             toCppImplType(
                                                                                                                 iv[
                                                                                                                     "type"])))
            ofile.write("           for(int i=0; i<{}; i++){{\n".format(iv["count"]))
            ofile.write("               proto->set_{}(i, m{}[i]);\n".format(ik.lower(), ik))
            ofile.write("           }\n")
        # 复合类型，多值
        elif iv["count"] > 1 and (isCompoundType(iv["type"])):
            for i in range(iv["count"]):
                ofile.write("           if (all || (db && {}) || (sync && {} && m{}[{}].isDirty(IMarkDirty::SYNC_DIRTY))){{\n".format(iv["db"], iv["sync"], ik, i))
                ofile.write("               m{}[{}].toProto(proto->mutable_{}()->mutable__v{}(), db, sync, all);\n".format(ik, i, ik.lower(), i))
                ofile.write("           }\n")
        ofile.write("       }\n")
    ofile.write("   }\n")

    ofile.write("   void fromProto(const {}Proto& proto){{\n".format(key))
    for ik, iv, idx in vali:
        # 基础类型，单值
        if iv["count"] == 1 and (not isCompoundType(iv["type"])):
            ofile.write("       m{} = proto.{}();\n".format(ik, ik.lower()))
        # 复合类型，单值
        elif iv["count"] == 1 and (isCompoundType(iv["type"])):
            ofile.write("       m{}.fromProto(proto.{}());\n".format(ik, ik.lower()))
        # 基本类型，多值
        elif iv["count"] > 1 and (not isCompoundType(iv["type"])):
            ofile.write("       for(int i=0; i<{} && i<proto.size_{}(); i++){{\n".format(iv["count"]), ik.lower())
            ofile.write("            m{}[i] = proto.{}(i);\n".format(ik, ik.lower()))
            ofile.write("       }\n")
        # 复合类型，多值
        elif iv["count"] > 1 and (isCompoundType(iv["type"])):
            ofile.write("       if (proto.has_{}()){{\n".format(ik.lower()))
            for i in range(iv["count"]):
                ofile.write("           if (proto.{}().has__v{}()){{\n".format(ik.lower(), i))
                ofile.write("               m{}[{}].fromProto(proto.{}()._v{}());\n".format(ik, i, ik.lower(), i))
                ofile.write("           }\n")
            ofile.write("       }\n")

    ofile.write("   }\n")

    ofile.write("private:\n")
    for ik, iv, idx in vali:
        cppType = toCppImplType(iv["type"])
        ofile.write("   //{}\n".format(iv["desc"]))
        # 基础类型，单值
        if iv["count"] == 1 and (not isCompoundType(iv["type"])):
            ofile.write("   {}  m{};\n".format(cppType, ik))
        # 复合类型，单值
        elif iv["count"] == 1 and (isCompoundType(iv["type"])):
            ofile.write("   {}Impl  m{};\n".format(cppType, ik))
        # 基本类型，多值
        elif iv["count"] > 1 and (not isCompoundType(iv["type"])):
            ofile.write("   {}  m{}[{}];\n".format(cppType, ik, iv["count"]))
        # 复合类型，多值
        elif iv["count"] > 1 and (isCompoundType(iv["type"])):
            ofile.write("   {}Impl  m{}[{}];\n".format(cppType, ik, iv["count"]))

    ofile.write("};\n\n")
    pass


class ToCppImpl:
    @staticmethod
    def convert(outfname):
        ofile = open(outfname, 'w')

        writehead(ofile)
        datas = AnalysisGameData.getData()

        ofile.write("/**这是由程序生成的代码，不要尝试手动修改!*/\n")
        ofile.write('#include <string>\n')
        ofile.write('#include "gamedata.pb.h"\n')
        ofile.write('#include "MarkDirty.h"\n')
        ofile.write('#include "GameData.h"\n\n')

        for key, val in datas:
            ofile.write("class {};\n".format(key))
        ofile.write("\n")

        for key, val in datas:
            writemsg(ofile, key, val)
        writetail(ofile)
