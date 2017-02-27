
import os

def exportData(files, targetdir):
    ofilename = '{}/cfg_data.cs'.format(targetdir)
    print('out put c# file {}'.format(ofilename))
    ofile = open(ofilename, 'w')

    typecvert = {'int':'int', 'float':'float', 'str':'string'}

    ofile.write('\nusing System.Collections.Generic;\n\n')
    for fn,fv in files:
        header = fv[2]
        dtype = fv[1]
        classname = 'cfg_' + fn
        ofile.write('public class {}{{\n'.format(classname))
        ofile.write('   public static {} instance = new {}();\n'.format(classname, classname))
        ofile.write('   public class data{\n')
        for i in range(len(header)):
            headname = header[i]
            headtype = dtype[i]
            ofile.write('       public {} {};\n'.format(typecvert[headtype], headname))
        ofile.write('   }\n')

        ofile.write('   private Dictionary<{}, data> mMapData = null;\n'.format(typecvert[dtype[0]]))
        ofile.write('   public Dictionary<{}, data> getMapData(){{\n'.format(typecvert[dtype[0]]))
        ofile.write('       return mMapData;\n')
        ofile.write('   }\n')
        ofile.write('   public data get({} k){{\n'.format(typecvert[dtype[0]]))
        ofile.write('       return mMapData[k];\n')
        ofile.write('   }\n')
        ofile.write('   public static object doLoad(List<string[]> content){\n')
        ofile.write('      Dictionary<{}, data> mapData = new Dictionary<{}, data>();\n'.format(typecvert[dtype[0]], typecvert[dtype[0]]))
        ofile.write('      foreach (string[] line in content){\n')
        ofile.write('           if(line.Length != {}){{return null;}}\n'.format(len(header)))
        ofile.write('           data _d = new data();\n')

        for i in range(len(header)):
            headname = header[i]
            headtype = dtype[i]
            if headtype == 'int':
                ofile.write('           _d.{} = (int)float.Parse(line[{}]);\n'.format(headname, i))
            elif headtype == 'float':
                ofile.write('           _d.{} = float.Parse(line[{}]);\n'.format(headname, i))
            elif headtype == 'str':
                ofile.write('           _d.{} = line[{}];\n'.format(headname, i))
            else:
                raise Exception('type error {}'.format(headtype))
        ofile.write('           {} _k = _d.{};\n'.format(typecvert[dtype[0]], header[0]))
        ofile.write('           mapData[_k] = _d;\n')
        ofile.write('       }\n')
        ofile.write('       return mapData;\n')
        ofile.write('   }\n')
        ofile.write('   public void doChangeCfg(object cfg){\n')
        ofile.write('       mMapData = cfg as Dictionary<{}, data>;\n'.format(typecvert[dtype[0]]))
        ofile.write('   }\n')
        ofile.write('}\n')

    ofile.close()

def exportLoader(data, targetdir):
    ofilename = '{}/cfg_loader.cs'.format(targetdir)
    print('out put c# loader {}'.format(ofilename))
    ofile = open(ofilename, 'w')

    ofile.write('\nusing System.Collections.Generic;\n\n')

    ofile.write('public class cfg_loader{\n')

    ofile.write('   public static Dictionary<string, object> load(Dictionary<string, List<string[]>> values){\n')
    ofile.write('       Dictionary<string, object> reloaded = new Dictionary<string, object>();\n')
    ofile.write('       foreach (KeyValuePair<string, List<string[]>> val in values){\n')
    ofile.write('           switch (val.Key){\n')
    for fn,fv in data:
        ofile.write('           case "{}":\n'.format(fn))
        ofile.write('               reloaded["{}"] = cfg_{}.doLoad(val.Value);\n'.format(fn, fn))
        ofile.write('               break;\n')

    ofile.write('           default:break;\n')
    ofile.write('           }\n')
    ofile.write('       }\n')
    ofile.write('       return reloaded;\n')
    ofile.write('   }\n')

    ofile.write('   public static void update(Dictionary<string, object> rloaded){\n')
    ofile.write('       foreach (KeyValuePair<string, object> item in rloaded){\n')
    ofile.write('           switch (item.Key){\n')
    for fn,fv in data:
        ofile.write('           case "{}":\n'.format(fn))
        ofile.write('               cfg_{}.instance.doChangeCfg(item.Value);\n'.format(fn))
        ofile.write('               break;\n')

    ofile.write('           default:break;\n')
    ofile.write('           }\n')
    ofile.write('       }\n')
    ofile.write('   }\n')
    ofile.write('}\n')

class ExportCsharp:
    @staticmethod
    def export(files, targetdir):
        if not os.path.exists(targetdir):
            os.makedirs(targetdir)
        exportData(files, targetdir)
        exportLoader(files, targetdir)

