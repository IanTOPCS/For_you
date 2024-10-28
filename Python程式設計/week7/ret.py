class Rectangle:
    def __init__ (self, x0, y0, width, height):
        self.x0 = x0
        self.y0 = y0
        self.width = width
        self.height = height
    
    @property
    def x1(self):
        return self.x0 + self.width

    @property
    def y1(self):
        return self.y0 + self.height
    
    @property
    def area(self):
        return self.width * self.height
    
    def __or__(self, other):
        x0 = min(self.x0, other.x0)
        y0 = min(self.y0, other.y0)
        x1 = max(self.x1, other.x1)
        y1 = max(self.y1, other.y1)
        return Rectangle(x0, y0, x1-x0, y1-y0)
    
    def __and__(self, other):
        x0 = max(self.x0, other.x0)
        y0 = max(self.y0, other.y0)
        x1 = min(self.x1, other.x1)
        y1 = min(self.y1, other.y1)
        if x1 > x0 or y1 > y0:
            return Rectangle(x0, y0, x1-x0, y1-y0)
        else:
            return Rectangle(x0, y0, 0, 0)
        
    def __str__(self):
        return f"Rectangle:({self.x0},{self.y0})-({self.x1},{self.y1})"
    
    def __repr__(self):
        return f"Rectangle({self.x0},{self.y0},{self.width},{self.height})"
    
    def __eq__(self, other):
        return ((self.x0 == other.x0)and(self.y0 == other.y0)and(self.width == other.width)and(self.height == other.height))

# #1
# rect1 = Rectangle(0,0,10,10)
# rect2 = Rectangle(10,10,10,10)

# #2
# print(rect1.area)

# #3
# rect3 = rect1 | rect2
# print(rect3)

# #4
# rect4 = rect1 & rect2
# print(rect4)

# #5
# print(rect1)

# #6
# print(rect1==eval(repr(rect1)))