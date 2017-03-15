# car_objectimpl_checker.py
# encoding: UTF-8
# usages:
#        sudo chmod a+x car_objectimpl_checker.py
#        python car_objectimpl_checker.py scan_path log_filepath

import re
import os
import sys


def read_file(path):
    lines = []
    if(os.path.isfile(path)):
        handle = open(path, 'r')
        for line in handle:
            lines.append(line.strip())
        handle.close()
    return lines

def get_finename(path):
    filename = path
    index = filename.rfind('/');
    if index != -1:
        filename = path[(index + 1):len(path)]

    index = filename.rfind('.');
    if index != -1:
        filename = filename[0:index]
    return filename


def log_fine_info(logFile, firstLog, path):
    if firstLog:
        firstLog = False
        logInfo ='\n\n>> process file: ' + path
        logFile.write(logInfo)
        print logInfo
    return firstLog

def summarize_log(logPath):
    if(os.path.isfile(logPath)):
        errorCount = 0
        warningCount = 0

        # summarize
        logFile = open(logPath, 'r')
        for line in logFile:
            line = line.strip()
            if line.startswith('> error:') == True:
                errorCount = errorCount + 1
            elif line.startswith('= warning:') == True:
                warningCount = warningCount + 1
        logFile.close()

        # log
        logFile = open(logPath, 'a')
        logInfo = '\n\nresults: {0:d} errors, {1:d} warnings.\n'.format(errorCount, warningCount)
        logFile.write(logInfo)
        print logInfo
        logFile.close()


def process_file(path, logFile):
    if path.endswith('.h') == False:
        return

    filename = get_finename(path)
    if filename.startswith("C") == False:
        return

    lines = read_file(path)
    totalNum = len(lines)
    lineNum = 0
    firstLog = True
    isCarClass = False
    isCompleted = False
    while lineNum < totalNum:
        line = lines[lineNum]

        if False == isCarClass and line.startswith("CarClass("):
            isCarClass = True
        elif isCarClass and line.startswith("CAR_OBJECT_DECL"):
            isCompleted = True
            break
        elif isCarClass and line.startswith("CAR_SINGLETON_DECL"):
            isCompleted = True
            break
        lineNum = lineNum + 1

    if isCarClass and False == isCompleted:
        log_fine_info(logFile, firstLog, path)
        logInfo = '\n   > error: Car calss {0} needs CAR_OBJECT_DECL or CAR_SINGLETON_DECL'.format(filename)
        logFile.write(logInfo)
        print logInfo

def process_dir(path, logFile):
    listfile = os.listdir(path)
    fileNum = len(listfile)
    for filename in listfile:
        filepath = path + '/' + filename
        if(os.path.isdir(filepath)):
            # exclude hidden dirs
            if(filename[0] == '.'):
                pass
            elif filename.startswith("bak"):
                pass
            else:
                process_dir(filepath, logFile)
        elif(os.path.isfile(filepath)):
            process_file(filepath, logFile)

def process(path, logPath):
    if(os.path.isfile(logPath)):
        os.remove(logPath)
    logFile = open(logPath, 'a')
    if(os.path.isdir(path)):
        process_dir(path, logFile)
    elif(os.path.isfile(path)):
        process_file(path, logFile)
    else:
        print 'invalid path:', path
    logFile.close()
    summarize_log(logPath)

##########################################################
scan_path = '/home/luozhaohui/Elastos5/Sources/'
log_filepath = 'car_objectimpl_checker.log'

print "python  :", sys.argv[0]
argc = len(sys.argv)
if argc == 3:
    scan_path = sys.argv[1]
    log_filepath = sys.argv[2]

print "process :", scan_path
print "log to  :", log_filepath
process(scan_path, log_filepath)
