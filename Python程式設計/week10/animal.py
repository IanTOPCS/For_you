import re
from collections import defaultdict

def count_animals(input_str):
    # 定義正則表達式，匹配兩種可能的描述格式
    pattern = r"(\d+)[隻條頭](羊|狗|雞|豬|牛)|(羊|狗|雞|豬|牛)(\d+)[隻條頭]"
    
    # 計數的字典
    animal_counts = defaultdict(int)
    
    # 查找所有符合條件的數量和動物
    matches = re.findall(pattern, input_str)
    
    for match in matches:
        count = 0
        animal = ""
        
        if match[0]:  # 格式1: 數量在前
            count = int(match[0])
            animal = match[1]
        else:  # 格式2: 動物在前
            count = int(match[3])
            animal = match[2]
        
        animal_counts[animal] += count
    
    # 以指定順序輸出結果
    for animal in ["羊", "狗", "雞", "豬", "牛"]:
        print(f"{animal}:{animal_counts[animal]}")

# 測試輸入
input_str = input()
count_animals(input_str)