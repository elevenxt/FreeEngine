
import os

def exportInterface(files, targetdir):
    ofilename = '{}/cfg_data.h'.format(targetdir)
    ofile = open(ofilename, 'w')
    ofile.write('#ifndef _CFG_DATA_\n')
    ofile.write('#define _CFG_DATA_\n')
    typecvert = {'int':'int', 'float':'float', 'str':'const char*'}
    for fn,fv in files:
        header = fv[2]
        dtype = fv[1]
        classname = 'cfg_' + fn
        ofile.write('class {}{{\n'.format(classname))
        ofile.write('   public: class data{\n')
        for i in range(len(header)):
            headname = header[i]
            headtype = dtype[i]
            ofile.write('       public: virtual {} get_{}() = 0;\n'.format( typecvert[headtype], headname))
        ofile.write('   };\n')
        ofile.write('   public: virtual {}::data* get({} key) = 0;\n'.format(classname, typecvert[dtype[0]]))
        ofile.write('   public: typedef void(*ForEach)(data&);\n')
        ofile.write('   public: virtual void forEach(ForEach cb) = 0;\n')
        ofile.write('};\n')

    ofile.write('class cfg_mgr{\n')
    for fn,fv in files:
        ofile.write('   public: virtual cfg_{}& get_cfg_{}() = 0;\n'.format(fn, fn))
    ofile.write('};\n')
    ofile.write('#endif\n')

def exportImpl(files, targetdir):
    ofilename = '{}/cfg_data_impl.h'.format(targetdir)
    ofile = open(ofilename, 'w')
    ofile.write('#ifndef _CFG_DATA_IMPL_\n')
    ofile.write('#define _CFG_DATA_IMPL_\n')
    ofile.write('#include <map>\n')
    ofile.write('#include <string>\n')
    ofile.write('#include <vector>\n')
    ofile.write('#include "ValueOpt.h"\n')
    ofile.write('#include "cfg_data.h"\n')

    tcinter = {'int':'int', 'float':'float', 'str':'const char*'}
    tcimpl = {'int':'int', 'float':'float', 'str':'std::string'}

    for fn,fv in files:
        header = fv[2]
        dtype = fv[1]
        classname = 'cfg_' + fn
        ofile.write('class {}_impl : public {}{{\n'.format(classname, classname))
        ofile.write('   public: static {}_impl& instance(){{static {}_impl ins;return ins;}}\n'\
                    .format(classname, classname))
        ofile.write('   public: class data : public {}::data{{\n'.format(classname))
        for i in range(len(header)):
            headname = header[i]
            headtype = dtype[i]
            if headtype == 'str':
                ofile.write('       public: virtual {} get_{}(){{return m{}.c_str();}};\n'\
                        .format( tcinter[headtype], headname, headname))
            else:
                ofile.write('       public: virtual {} get_{}(){{return m{};}};\n'\
                        .format( tcinter[headtype], headname, headname))
            ofile.write('       public: {} m{};\n'.format(tcimpl[headtype], headname))
        ofile.write('   };\n')
        ofile.write('   public: virtual {}::data* get({} key){{;\n'.format(classname, tcinter[dtype[0]]))
        ofile.write('       return &mMapData[key];\n')
        ofile.write('    }\n')

        ofile.write('   public: virtual void forEach(ForEach cb){;\n')
        ofile.write('   for(auto kv : mMapData){cb(kv.second);}\n')
        ofile.write('   }\n')

        ofile.write('   public: static bool doLoad(std::vector<std::vector<std::string>> content){\n')
        ofile.write('       if(instance().mNewLoadedData != 0){return false;}\n')
        ofile.write('       std::map<{}, data>* mapData = new std::map<{}, data>();\n'.format(tcimpl[dtype[0]], tcimpl[dtype[0]]))
        ofile.write('       for (std::vector<std::string>& line : content){\n')
        ofile.write('           if(line.size() != {}){{delete mapData;return false;}}\n'.format(len(header)))
        ofile.write('           data _d;\n')

        for i in range(len(header)):
            headname = header[i]
            headtype = dtype[i]
            if headtype == 'int':
                ofile.write('           _d.m{} = (int)ff::ValueOpt::convert<float>(line[{}]);\n'.format(headname, i))
            elif headtype == 'float':
                ofile.write('           _d.m{} = ff::ValueOpt::convert<float>(line[{}]);\n'.format(headname, i))
            elif headtype == 'str':
                ofile.write('           _d.m{} = line[{}];\n'.format(headname, i))
            else:
                raise Exception('type error {}'.format(headtype))
        ofile.write('           {} _k = _d.m{};\n'.format(tcimpl[dtype[0]], header[0]))
        ofile.write('           (*mapData)[_k] = _d;\n')
        ofile.write('       }\n')
        ofile.write('       instance().mNewLoadedData = mapData;\n')
        ofile.write('       return true;\n')
        ofile.write('   }\n')
        ofile.write('   public: void tryChangeCfg(){\n')
        ofile.write('       if(mNewLoadedData == 0){return;}\n')
        ofile.write('       mMapData = *mNewLoadedData;\n')
        ofile.write('       delete mNewLoadedData;\n')
        ofile.write('       mNewLoadedData = 0;\n')
        ofile.write('   }\n')

        ofile.write('   private: std::map<{}, data> mMapData;\n'.format(tcimpl[dtype[0]]))
        ofile.write('   private: std::map<{}, data>* mNewLoadedData = 0;\n'.format(tcimpl[dtype[0]]))
        ofile.write('};\n')

    ofile.write('class cfg_mgr_impl : public cfg_mgr{\n')
    ofile.write('   public: static cfg_mgr_impl& instance(){static cfg_mgr_impl ins;return ins;}\n')
    for fn,fv in files:
        ofile.write('   public: virtual cfg_{}& get_cfg_{}(){{\n'.format(fn, fn))
        ofile.write('       return cfg_{}_impl::instance();\n'.format(fn))
        ofile.write('   }\n')

    ofile.write('   public: void trychangecfg(){\n')
    for fn,fv in files:
        ofile.write('   cfg_{}_impl::instance().tryChangeCfg();\n'.format(fn))
    ofile.write('   }\n')
    ofile.write('};\n')
    ofile.write('#endif\n')

def exportLoader(data, targetdir):
        if not os.path.exists(targetdir):
            os.makedirs(targetdir)
        ofilename = '{}/cfg_loader.h'.format(targetdir)
        print('out put c# loader {}'.format(ofilename))
        ofile = open(ofilename, 'w')
        ofile.write('#ifndef _CFG_LOADER_\n')
        ofile.write('#define _CFG_LOADER_\n')
        ofile.write('#include <string>\n')
        ofile.write('#include <vector>\n')
        ofile.write('#include "cfg_data_impl.h"\n')
        ofile.write('class cfg_loader{\n')

        ofile.write('public: static bool reload(std::string tab, std::vector<std::vector<std::string>> data){\n')
        for tab,v in data:
            ofile.write('   if(tab == "{}"){{\n'.format(tab))
            ofile.write('       return cfg_{}_impl::instance().doLoad(data);\n'.format(tab))
            ofile.write('   }\n')
        ofile.write('   return true;\n')
        ofile.write('   }\n')
        ofile.write('};\n')
        ofile.write('#endif\n')

class ExportCpp:
    @staticmethod
    def export(files, targetdir):
        if not os.path.exists(targetdir):
            os.makedirs(targetdir)

        exportInterface(files, targetdir)
        exportImpl(files, targetdir)
        exportLoader(files, targetdir)
        return
