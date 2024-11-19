import numpy as np

# Making fist 1-D vector v1
v1 = np.array([3, 7])
print("First vector sequence is: ", v1)

# Making second 1-D vector v2
v2 = np.array([1, 2, 5, 7])
print("Second vector sequence is: ", v2)

print("\nprinting linear convolution result between v1 and v2 using default 'full' mode:")
print(np.convolve(v1, v2))                                                                      # 完全模式，全算，包括外邊界
print("\nprinting linear convolution  result between v1 and v2 using 'same' mode:")
print(np.convolve(v1, v2, mode='same'))                                                         # 相同模式，取來源長度最大者，包括外邊界

print("\nprinting linear convolution  result between v1 and v2 using 'valid' mode:")            # 有效模式，排除外邊界
print(np.convolve(v1, v2, mode='valid'))
