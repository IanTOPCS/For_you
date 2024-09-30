s, t = str(input()), str(input())

print(len(s))
print(len(set(s)))

list_s = list(s)
print(''.join(list_s))

print("".join(sorted(set(s)&set(t))))

print(len(set(s)|set(t)))

print(len(set(s)-set(t)))

maxCh = ''
maxNum = 0
sor_un = list(s+t)
for _ in sor_un:
    freq = sor_un.count(_)
    if freq > maxNum:
        maxNum = freq
        maxCh = _
print(f"{maxCh}:{maxNum}")



'''
蘋果一顆通常約為180-200克，熱量約92大卡，熱量相較其他水果不高，膳食纖維去皮的蘋果約2.3-3.4克，為中高膳食纖維水果，另也含鉀、維生素A、Beta胡蘿蔔素等營養。青蘋果的維生素A又多比紅蘋果來得更高。
整體而言，蘋果的各類營養多為「中高階」，但從綜合營養來看卻相當多元，且果皮植化素優異，對身體的幫助相當廣泛，這也是為什麼常聽到「一天一蘋果，醫生遠離我」。

'''