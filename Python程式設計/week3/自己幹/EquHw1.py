sor = str(input())
n = int(input())
w = int(input())
p = str(input())

print(f"{sor:>{w}}")
print(f"{n:<{w}}")
print(f"{sor:{p}^{w}}")
print(f"{n:{p}^{w},d}")