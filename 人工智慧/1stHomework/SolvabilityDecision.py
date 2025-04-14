import math
def judge(sor):
  sor = list(map(int, sor))
  count = 0
  zeroPosition = sor.index(0)
  sor.pop(sor.index(0))
  for i in range(len(sor)):
    for j in range(len(sor)):
      if((i < j) and (sor[j] > sor[i])):
        count += 1
  if(math.sqrt(len(sor)) % 2):
    if(count % 2):
      return f"NO"
    else:
      return f"YES"
  else:
    if((count + zeroPosition) % 2):
      return f"NO"
    else:
      return f"YES"
    

if __name__ == "__main__":
  number = int(input())
  for i in range(number):
    sor = str(input())
    ans = judge(sor)
    print(ans)