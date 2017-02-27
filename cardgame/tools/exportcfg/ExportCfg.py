#encoding: utf-8

import os
import shutil
import codecs

from exportcfg.excelreader import ExcellReader
from exportcfg.exportdata import ExportData
from exportcfg.ExportCsharp import ExportCsharp
from exportcfg.ExportCpp import ExportCpp

class ExportCfg:
    @staticmethod
    def run(cfgDir, dataDir, cppDir, csDir):
        dfile = codecs.open('cfg.txt', 'w', 'utf-8')
        allfile = []
        for parent,dirnames,filenames in os.walk(cfgDir):
            for filename in filenames:
                if '~$' in filename:
                    continue
                fpath = os.path.join(parent,filename)
                excell = ExcellReader(fpath)

                # 输出csv数据
                for k,v in excell.getdata().items():
                    allfile.append((k,v))
                    dfile.write(k)
                    dfile.write('^')
                    dfile.write(ExportData.export(k, v))
                    dfile.write('^')

        dfile.close()
        ExportCpp.export(allfile, cppDir)
        ExportCsharp.export(allfile, csDir)

        for ddir in dataDir:
            shutil.copy('cfg.txt', os.path.join(ddir, 'cfg.txt'))

        try:
            os.remove('cfg.txt')
        except:
            pass


