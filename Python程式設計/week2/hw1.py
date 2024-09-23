x = str(input())
y = str(input())
z = str(input())
w = str(input())

print(y in x)

print(x.find(y))

print(x.split(','))

print("---".join(x.split(',')[:3]))

print(x.startswith(y))

print(x.endswith(y))

print(x.upper())

sor = x.split(',')
tmp=[]
for word in sor:
    if(word.isalpha()):
      tmp.append(word.capitalize())
    else:
        tmp.append(word)
print(','.join(tmp))

print(y.isdigit())

print(x.replace(y, z))

print(w.strip())

print(len(w.strip()))