__author__ = 'xt'

from exportgamedata.AnalysisGameData import AnalysisGameData


def writehead(ofile):
    ofile.write("\n\n\n")


def writetail(ofile):
    ofile.write("\n\n\n")


def protoType(rawt):
    if rawt == "int":
        return "int32"
    if rawt == "str":
        return "bytes"
    return rawt + "Proto"


def writemsg(ofile, key, val):
    arrays = []
    for ik, iv in val.items():
        if iv["count"] > 1:
            arrays.append((ik, iv))

    for ik, iv in arrays:
        arrname = "_" + key + ik
        ofile.write("message    {}Proto\n{{\n".format(arrname))
        for i in range(0, iv["count"]):
            ofile.write("   optional   {}  _v{} = {};\n" \
                        .format(protoType(iv["type"]), i, i + 1))
        ofile.write("}\n\n")

    ofile.write("message    {}Proto\n{{\n".format(key))
    for ik, iv in val.items():
        ofile.write("   //{}\n".format(iv["desc"]))
        if iv["count"] == 1:
            ofile.write("   optional {} {} = {};\n".format(protoType(iv["type"]), ik, iv["id"]))
        else:
            arrname = "_" + key + ik
            ofile.write("   optional {}Proto {} = {};\n".format(arrname, ik, iv["id"]))

    ofile.write("}\n\n")
    pass


class ToProtobuf:
    @staticmethod
    def convert(outfname):
        ofile = open(outfname, 'w')

        writehead(ofile)
        datas = AnalysisGameData.getData()
        for key, val in datas:
            writemsg(ofile, key, val)
        writetail(ofile)
