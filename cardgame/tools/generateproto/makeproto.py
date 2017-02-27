# coding:utf-8

import os
import re
import shutil
import subprocess


def makeCsProto(protoFile):
    filename, fileext = os.path.splitext(protoFile)
    cmdcsharp = "protogen -i:{}.proto -o:{}.cs -p:detectMissing".format(filename, filename)
    print(cmdcsharp)
    p = subprocess.Popen(cmdcsharp, shell=True, \
                         stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = p.communicate()

    if stdout:
        print(stdout)
    if stderr:
        print(stderr)


def makeCppProto(protoFile):
    protocmd = "protoc -I=./ --cpp_out=./ " + protoFile;
    print(protocmd)
    p = subprocess.Popen(protocmd, shell=True, \
                         stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = p.communicate()
    if stdout:
        print(stdout)
    if stderr:
        print(stderr)


def makeCppMsgId(protoFile):
    dirname = os.path.dirname(protoFile)
    bname = os.path.basename(protoFile)
    fname = os.path.splitext(bname)[0]
    fext = os.path.splitext(bname)[1]
    pfile = open(protoFile, 'r')
    wordpattern = re.compile('[ ;\t\r\n]')
    words = []
    for line in pfile:
        words += [x for x in wordpattern.split(line) if x != '']
    step = 0
    msgids = makeIds(protoFile)

    pmsgfile = open(os.path.join(dirname, fname + '.h'), 'w')
    pmsgfile.write('#ifndef _us_' + fname + '_ids_\n')
    pmsgfile.write('#define _us_' + fname + '_ids_\n\n')
    pmsgfile.write('#include "' + fname + '.pb.h"\n\n')

    pmsgfile.write('enum {0}_ids{{\n'.format(fname))
    for key, value in msgids.items():
        pmsgfile.write('\t{0}_id = {1},\n'.format(key, value))
    pmsgfile.write('};\n\n')

    pmsgfile.write('struct {0}_group;\n\n'.format(fname))

    pmsgfile.write('template<typename GROUP, typename ST>\n')
    pmsgfile.write('struct msg_st2id;\n\n')
    for key, value in msgids.items():
        pmsgfile.write('template<>\n')
        pmsgfile.write('struct msg_st2id<{0}_group, {1}>{{enum{{ID={1}_id}};}};\n' \
                       .format(fname, key))

    pmsgfile.write('\n\ntemplate<typename GROUP, int ID>\n')
    pmsgfile.write('struct msg_id2st;\n\n')
    for key, value in msgids.items():
        pmsgfile.write('template<>\n')
        pmsgfile.write('struct msg_id2st<{0}_group, {1}_id>{{typedef {1} ST;}};\n' \
                       .format(fname, key))

    pmsgfile.write('\n\n#endif\n')
    pmsgfile.close()


def makeIds(protoFile):
    dirname = os.path.dirname(protoFile)
    bname = os.path.basename(protoFile)
    fname = os.path.splitext(bname)[0]

    pfile = open(protoFile, 'r')
    wordpattern = re.compile('[ ;\t\r\n]')
    words = []
    for line in pfile:
        words += [x for x in wordpattern.split(line) if x != '']
    step = 0
    msgids = {}
    thisword = ''
    thisid = ''
    for word in words:
        if word == fname:
            step = 1
            continue
        if step == 1 and word == '{':
            step = 2
            continue
        if step == 2 and word == '}':
            step = 3
            continue
        if step == 2 and word != 'optional':
            thisword = word
            step = 4
            continue
        if step == 4 and word == '=':
            step = 5
            continue
        if step == 5:
            thisid = word
            step = 2
            msgids[thisword] = thisid
            continue

    return msgids


def makeCsMsgId(protoFile):
    dirname = os.path.dirname(protoFile)
    bname = os.path.basename(protoFile)
    fname = os.path.splitext(bname)[0]

    msgids = makeIds(protoFile)

    pmsgfile = open(fname + '_ids.cs', 'w')
    pmsgfile.write('\nusing System.Collections.Generic;\n')
    pmsgfile.write('public class {}_ids{{\n'.format(fname))
    pmsgfile.write('    private static Dictionary<string, int> mName2Id = new Dictionary<string, int>();\n')
    pmsgfile.write('    private static Dictionary<int, string> mId2Name = new Dictionary<int, string>();\n')

    pmsgfile.write('    static {}_ids(){{\n'.format(fname))
    for key, value in msgids.items():
        pmsgfile.write('        mName2Id["{}"] = {};\n'.format(key, value))
        pmsgfile.write('        mId2Name[{}] = "{}";\n'.format(value, key))

    pmsgfile.write('    }\n')

    pmsgfile.write('    public static string getName(int id){return mId2Name[id];}\n')
    pmsgfile.write('    public static int getId(string name){return mName2Id[name];}\n')

    pmsgfile.write('}\n')
    pmsgfile.close()


def rmfile(fname):
    try:
        os.remove(fname)
    except:
        pass


class MakeProto:
    @staticmethod
    def run(protoExe, protoFile, cppDir, csDir, cids):
        # 先转换成全路径
        protoExe = os.path.abspath(protoExe)
        protoFile = os.path.abspath(protoFile)
        cppDir = os.path.abspath(cppDir)
        csDir = os.path.abspath(csDir)

        # 进入exe目录，删除遗留文件，生成文件，移动文件到目标路径，恢复工作目录
        curpwd = os.getcwd()
        workPath, _ = os.path.split(protoExe)
        os.chdir(workPath)
        protoPath, protoFile = os.path.split(protoFile)
        rmfile(protoFile)
        shutil.copy(os.path.join(protoPath, protoFile), os.path.join(workPath, protoFile))

        fileName, fileExt = os.path.splitext(protoFile)

        # 生成cpp文件
        makeCppProto(protoFile)
        rmfile(os.path.join(cppDir, fileName + ".pb.h"))
        os.rename(os.path.join(workPath, fileName + ".pb.h"), os.path.join(cppDir, fileName + ".pb.h"))
        rmfile(os.path.join(cppDir, fileName + ".pb.cc"))
        os.rename(os.path.join(workPath, fileName + ".pb.cc"), os.path.join(cppDir, fileName + ".pb.cc"))
        # 生成cs文件
        makeCsProto(protoFile)
        rmfile(os.path.join(csDir, fileName + ".cs"))
        os.rename(os.path.join(workPath, fileName + ".cs"), os.path.join(csDir, fileName + ".cs"))

        # 生成id和消息对应
        if cids:
            makeCppMsgId(protoFile)
            rmfile(os.path.join(cppDir, fileName + ".h"))
            os.rename(os.path.join(workPath, fileName + ".h"), os.path.join(cppDir, fileName + ".h"))

            makeCsMsgId(protoFile)
            rmfile(os.path.join(csDir, fileName + "_ids.cs"))
            os.rename(os.path.join(workPath, fileName + "_ids.cs"), os.path.join(csDir, fileName + "_ids.cs"))

        rmfile(protoFile)
        os.chdir(curpwd)
