import numpy as np
import csv
class Point:
    def __init__(self,x,y):
        self.x = x
        self.y = y

pt = [Point(np.random.randint(0,1000)-500,np.random.randint(0,1000)-500) for _ in range(100)]

with open('points.csv', 'w', newline='') as f:
    writer = csv.writer(f)
    writer.writerow(['x', 'y'])
    for p in pt:
        writer.writerow([p.x, p.y])

pt2 = []
with open('points.csv', 'r') as f:
    reader = csv.reader(f)
    next(reader)
    pt2 = [Point(int(row[0]), int(row[0])) for row in reader]
    
for p in pt2:
    print(f"x:{p.x} y:{p.y}")

