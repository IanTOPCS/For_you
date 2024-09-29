import math
import sys

def cos(x):
    return math.cos(x/180.0*math.pi)

def sin(x):
    return math.sin(x/180.0*math.pi)

def bye():
    exit(0)

for line in sys.stdin:
    line = line.strip()
    if line.find("<-"):
        line = line.replace("<-", "=")
    exec(line, globals(), locals())