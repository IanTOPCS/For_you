class Data:
    def __init__(self, data, batch_size):
        self.data = data
        self.batch_size = batch_size
        self.total_batches = (len(self.data) + self.batch_size - 1)//self.batch_size

    def __len__(self):
        return self.total_batches
    
    def __getitem__(self, idx):
        if isinstance(idx, slice):
            return [self[i] for i in range(*idx.indices(self.total_batches))]

        if idx < 0:
            idx += self.total_batches

        if idx >= self.total_batches:
            raise IndexError("Index out of range")
        
        startps = idx * self.batch_size
        endps = startps + self.batch_size
        return [self.data[i % len(self.data)] for i in range(startps, endps)]
    
a = Data(data=[1, 2, 3, 4, 5], batch_size=3)

# 測試 len()
print(len(a))  # 2

# 測試取出批次資料
print(a[0])  # [1, 2, 3]
print(a[1])  # [4, 5, 1]
print(a[-1]) # [4, 5, 1]
print(a[-2]) # [1, 2, 3]
print(a[::-2]) # [[4, 5, 1], [1, 2, 3]]
print(a[::2])
print(a[:2])
# 測試索引錯誤
try:
    print(a[2])  # 應該會報 IndexError
except IndexError as e:
    print(e)