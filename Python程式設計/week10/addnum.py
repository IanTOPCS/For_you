import re

def sum_numbers_in_parentheses(input_str):
    # 定義正則表達式，匹配括號內的數字，並支持千分位格式
    pattern = r"\((\d{1,3}(?:,\d{3})*)\)"
    
    # 使用 re.findall 找出所有符合的數字
    matches = re.findall(pattern, input_str)
    
    # 將千分位格式的數字轉換為整數並計算總和
    total_sum = sum(int(match.replace(",", "")) for match in matches)
    
    return total_sum

# 測試範例
example_str = str(input())
result = sum_numbers_in_parentheses(example_str)
print(f"{result}")