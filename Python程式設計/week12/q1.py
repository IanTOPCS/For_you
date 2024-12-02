import numpy as np
import matplotlib.pyplot as plt
import tensorflow as tf
import os
import itertools

np.random.seed(100)
a = np.random.rand(100)
X = np.random.rand(1000,10)

exp1 = "np.reshape(a, (-1, 1)) - np.reshape(a, (1, -1))"
r = eval(exp1)

X2=np.sum(X**2,axis = 1,keepdims = True)

exp2 = "np.sqrt(np.maximum(X2 + X2.T - 2 * np.dot(X, X.T), 0))"
D = eval(exp2)

exp3 = "np.sum(np.triu(D < 2, k=1))"
v = eval(exp3)

exp4 = "tuple((np.triu_indices_from(D, k=1)[0][(D[np.triu_indices_from(D, k=1)] < 2)], np.triu_indices_from(D, k=1)[1][(D[np.triu_indices_from(D, k=1)] < 2)]))"
P = eval(exp4)

exp5 = "np.argmin(np.where(np.eye(D.shape[0], dtype=bool), np.inf, D), axis=1)"
N = eval(exp5)


(x_train, y_train), (x_test, y_test) = tf.keras.datasets.mnist.load_data()
# 筛选 0~9 的图像，每类选择 10 张
sel_id = []
for i in range(10):
    p = np.argwhere(y_train==i).ravel()[:10]
    sel_id.extend(p)

sel_img = x_train[sel_id]  # 形状为 (10, 10, 28, 28)

save_dir = './fig'
os.makedirs(save_dir, exist_ok=True)

# 原始数组重塑
reshaped_img = sel_img.reshape((5, 2, 10, 28, 28))
permutations = list(itertools.permutations(range(5)))

# 遍历所有有效排列并保存图片
for perm in permutations:
    i, j, k, y, z = perm
    try:
        # 调整维度并保存图片
        arranged_img = reshaped_img.transpose((i, j, k, y, z)).reshape((-1, 280))
        plt.imsave(os.path.join(save_dir, f'{i}{j}{k}{y}{z}.png'), arranged_img, cmap='gray')
    except ValueError:
        # 捕捉无效排列的错误
        print(f"Invalid permutation: {perm}")