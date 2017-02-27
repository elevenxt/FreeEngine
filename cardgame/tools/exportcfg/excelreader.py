#encoding: utf-8

import xlrd

class ExcellReader:
    def __init__(self, excellFileName):
        self.fname = excellFileName
        self.excell = xlrd.open_workbook(excellFileName)
        self.data = {}
        sheetnames = self.excell.sheet_names()
        print(sheetnames)
        for ns in range(self.excell.nsheets):
            sheet = self.excell.sheet_by_index(ns)
            _data = []
            sheetname = sheetnames[ns]
            for row in range(sheet.nrows):
                rdata = []
                for line in range(sheet.ncols):
                    cvalue = u'{}'.format(sheet.cell_value(row, line))
                    rdata.append(cvalue)
                _data.append(rdata)
            self.data[sheetname] = _data

    def getdata(self):
        return self.data