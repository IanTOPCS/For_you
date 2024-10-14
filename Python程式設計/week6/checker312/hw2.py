import hw_lambda
import math
from functools import reduce

a = [1, 2, -3, 4, 5, 6, 7, 8, 9]


expr1='filter(lambda x : (x%3 == 0) and (x >= 0), a if a else [0])'

expr2='map(lambda x : math.exp(-x), a if a else [0])'

expr3='reduce(lambda x, y : abs(x) + abs(y), a if a else [0])'

# b = eval(expr1)
# print(b)

# b = eval(expr2)
# print(b)

# b = eval(expr3)
# print(b)

hw_lambda.checker(expr1, expr2, expr3)