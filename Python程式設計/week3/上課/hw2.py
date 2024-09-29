x = str(input())
n = int(input())
w = int(input())
p = str(input())

print('{:>{wide}s}'.format(x, wide = w))
print('{:<{wide}d}'.format(n, wide = w))
print('{:{pad}^{wide}s}'.format(x, wide = w, pad = p))
print('{:{pad}^{wide},d}'.format(n, wide = w, pad = p))