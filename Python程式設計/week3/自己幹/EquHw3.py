import sys
even, odd = 0, 0
for line in sys.stdin:
    line = line.strip()
    number = int(line)
    if number % 2:
        odd += number
    else:
        even += number
print(f"odd:{odd} even:{even}")