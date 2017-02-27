
import os

class ExportData:
    @staticmethod
    def export(efile, data):
        strv = ''
        for i in range(3, len(data)):
            r = data[i]
            val = '#'.join(r)
            if '$' in val:
                print('excell can not contain character "#"')
                assert False
            strv += val + '$'

        return strv