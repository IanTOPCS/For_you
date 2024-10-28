class myChain:
  def __init__(self, *args):
    self.data =args
  def __iter__(self):
    for sub in self.data:
      for i in sub:
        yield i
        
# a = myChain([1, 2, 3], [4, 5, 6], [6, 7, 8])
a = myChain([])
for i in a:
    print(i, end=',')