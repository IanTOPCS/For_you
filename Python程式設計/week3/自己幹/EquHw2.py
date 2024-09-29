x, y, z, w = str(input()), str(input()), str(input()), str(input())

print(y in x)
print(x.find(y))
print(x.split(','))
print("---".join(x.split(',')[0:3]))
print(x.startswith(y))
print(x.endswith(y))
print(x.upper())

sor = x.split(',')
tmp = []
for _ in sor:
    if _.isalpha():
        tmp.append(_.capitalize())
    else:
        tmp.append(_)
print(','.join(tmp))

print(y.isdigit())
print(x.replace(y, z))
print(w.strip())
print(len(w.strip()))