import itertools
c = input()
n = ord(c.upper())-ord('A')+1
sor=[]
for i in range(n):
    sor.append(chr(ord('A')+i))

# print(sor)

answer="{frozenset(p):i for i in range(1, n+1, 1) for p in itertools.combinations(sor, i)}"


_cmd ='' 
while True:
    try:
        _s = input()
        _cmd += _s+'\n'
    except EOFError:
        break

p = compile(_cmd,'default','exec')
exec(p,globals())
