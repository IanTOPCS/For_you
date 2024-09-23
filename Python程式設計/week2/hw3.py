import sys

odd, even = 0, 0
for line in sys.stdin:
    line = line.strip()  # 去掉行末的換行符
    if line.isdigit():  # 確保行是數字
        number = int(line)  # 將行轉換為整數
        if number % 2:  # 判斷奇數
            odd += number
        else:  # 判斷偶數
            even += number

print('odd:{} even:{}'.format(odd, even))