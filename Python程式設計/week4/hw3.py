sor = input()
# exec(f"sor = {sor}")
sor = sor

sorKey = list(sor)
print(len(sorKey))
x = int(input())
print(x in sorKey)
y=input()
if y in sor:
    if sor[y]==0:
        print("True")
    else:
        print("False")
else:
    print("Notexisting")

tup = input()
# exec(f"tup = {tup}")
tup = tup
sor[tup[0]] = tup[1]
for key in sorted(sor.keys()):
    print(key)
for values in sorted(sor.values()):
    print(values)
for key in sorted(sor.keys()):
    print(f"({key}, {sor[key]})")

'''
{1:5, 3:7, 8:9, 0:10}
7
4
(10, 11)
'''