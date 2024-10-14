import hw_mdl
import copy

def create_mdl(tp, default=None) -> list:
    original = copy.deepcopy([default for i in range(tp[len(tp)-1])])
    for i in range(len(tp)-2, -1, -1):
        tmp = [copy.deepcopy(original) for j in range(tp[i])]
        original = copy.deepcopy(tmp)
    return copy.deepcopy(original)

# a = create_mdl((3, 3, 4), default = 2)
# a[1][1][0] = 3
# print(a)

hw_mdl.checker(create_mdl)
