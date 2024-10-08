list1 = list(map(int,input().split(',')))
ans=[]
for i, number in enumerate(list1):
    ans.append(f"{i}:{number}")
print(','.join(ans))

list2 = []
# for number in list1:
#     if number<0:
#         list2.append(number)
#         list1.remove(number)

for number in range(len(list1)-1, -1, -1):
    if list1[number] < 0:
        list2.insert(0, list1[number])
        list1.pop(number)

ans2=[]
for u, z in zip(list1, list2):
    ans2.append(f"{u}:{z}")
print(','.join(ans2))
    










'''
1,-1,2,-2,3,4,5,-6,7,-4,9,-20
'''