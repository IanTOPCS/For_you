sor = str(input())
sor = sor.split(',')
sor_q1 = sorted(sor)
for _ in sor_q1:
    print(_)

sor_q2 = sorted(sor, reverse=True)
for _ in sor_q2:
    print(_)

sor_q3 = list(set(sor))
sor_q3 = sorted(sor_q3, reverse=True)
for _ in sor_q3:
    print(_)

# 1,2,2,3,4,5,6,7,8