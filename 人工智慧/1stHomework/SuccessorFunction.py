import math
step = {"up":[-1, 0], "down":[1, 0], "left":[0, -1], "right":[0, 1]}
def move(sor, movement):
  rowNum = int(math.sqrt(len(sor)))
  sor = list(map(int, sor))
  # get zero position
  zeroPosition = sor.index(0)
  zeroCol = zeroPosition % rowNum
  zeroRow = zeroPosition // rowNum
  # print(f"zero:({zeroRow}, {zeroCol})") # debug
  # convert string into n*n matrix
  matrix = []
  bg, ed = 0, rowNum
  for _ in range(rowNum):
    matrix.append(sor[bg:ed])
    bg += rowNum
    ed += rowNum
      
  # try to move the step
  moveTar = step[movement]
  newRow = zeroRow + moveTar[0]
  newCol = zeroCol + moveTar[1]
  # print(f"row: {newRow}, col: {newCol}") # debug
    
  # check the movement is ok
  if newRow < 0 or newRow >= rowNum or newCol < 0 or newCol >= rowNum:
      return None
  else:
      matrix[zeroRow][zeroCol], matrix[newRow][newCol] = matrix[newRow][newCol], matrix[zeroRow][zeroCol]
  
  # convert matrix into string
  ans = ""
  for i in range(rowNum):
    for j in range(rowNum):
      ans += str(matrix[i][j])
  return ans

if __name__ == '__main__':
  num = int(input())
  for _ in range(num):
    sor = str(input())
    ans = []
    cnt = 0
    for direction, movement in step.items():
      ansStr = move(sor, direction)
      if(ansStr != None):
        ans.append([f"move 0 to {direction}", ansStr])
        cnt += 1
    # print the output
    print(f"{cnt}")
    for x in ans:
      for i in range(len(x)):
        print(x[i])