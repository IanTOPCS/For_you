import hw_hanoi
import functools

#define the generator hanoi
def hanoi(n,a,b,c):
    if(n == 1):
        yield (a, c)
    else:
        yield from hanoi(n-1, a, c, b)
        yield (a, c)
        yield from hanoi(n-1, b, a, c)
    
# n = int(input())
# for a, c in hanoi(n, 0, 1, 2):
#     print(f'move a disk from {a} to {c}')
hw_hanoi.checker(hanoi)