import math
def manhattan_distance(state: str) -> int:
    goal = "012345678"
    rowNum = int(math.sqrt(len(goal)))
    distance = 0
    for i, num in enumerate(state):
        if num != '0':
            goal_index = goal.index(num)
            distance += abs(i // rowNum - (goal_index // rowNum)) + abs(i % rowNum - (goal_index % rowNum))
    return distance

if __name__ == '__main__':
  num = int(input())
  for _ in range(num):
    sor = str(input())
    distance = manhattan_distance(sor)
    print(distance)
