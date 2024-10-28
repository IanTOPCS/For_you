import math


def distance(p1, p2):
    if hasattr(p1,'x') and hasattr(p1, 'y') and hasattr(p2,'x') and hasattr(p2, 'y'):
        return math.sqrt((p1.x - p2.x)**2 + (p1.y - p2.y)**2)
    else:
        raise AttributeError