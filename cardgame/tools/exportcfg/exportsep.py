
import os

class ExportSep:
    @staticmethod
    def export(efile, data, targetdir):
        ofilename = '{}/{}.csv'.format(targetdir, efile)
        print 'out put csv file {}'.format(ofilename)
        ofile = open(ofilename, 'w')
        for i in xrange(3, len(data)):
            r = data[i]
            val = '#'.join(r)
            ofile.write(val.encode('utf8'))
            ofile.write('$\n')

        ofile.close()