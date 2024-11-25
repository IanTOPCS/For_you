import numpy as np
import json

# 定義 Point 類別
class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

# 建立 Point 的清單
pt = [Point(np.random.randint(0, 1000) - 500, np.random.randint(0, 1000) - 500) for _ in range(100)]

def point_to_dict(obj):
    if isinstance(obj, Point):
        return {'x':obj.x, 'y':obj.y}
    raise TypeError("Type not serializable")

with open('points.json', 'w') as f:
    json.dump(pt, f, default=point_to_dict)

def custom(obj):
    return Point(obj["x"], obj["y"])

with open('points.json', 'r') as f:
    pt2 = json.load(f, object_hook=custom)

for p in pt2:
    print('x:{} y:{}'.format(p.x,p.y))