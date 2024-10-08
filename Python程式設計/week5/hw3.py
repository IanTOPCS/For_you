import itertools

x = int(input())
sor = [i for i in range(1, x+1, 1)]
# for p in itertools.permutations(sor, 3):
#     tmp = []
#     tmp.append(p[0])
#     tmp.append(p[1])
#     tmp.append(p[2])
#     tmp = sorted(tmp)
#     if tuple(tmp) in ans:
#         continue
#     if (tmp[0]*tmp[0] + tmp[1]*tmp[1] == tmp[2]*tmp[2]):
#         ans.append(tuple(tmp))
answer = "list(sorted(set(tuple(sorted(p)) for p in itertools.permutations(sor, 3) if (p[0]**2 + p[1]**2 == p[2]**2))))"

_cmd ='' 
while True:
    try:
        _s = input()
        _cmd += _s+'\n'
    except EOFError:
        break

p = compile(_cmd,'default','exec')
exec(p)
