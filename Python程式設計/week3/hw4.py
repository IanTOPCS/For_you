import math
import sys

def cos(x):
    return math.cos(x/180.0*math.pi)

def sin(x):
    return math.sin(x/180.0*math.pi)

def bye():
    exit(0)

def str2obj(s, local_dict):
    a = dict()
    exec('__ps='+s, None, a)
    return a['__ps']

while(1):
    line = str(input())
    if("<-" in line):
        line = line.replace("<-", '=')
    exec(line, globals(), locals())