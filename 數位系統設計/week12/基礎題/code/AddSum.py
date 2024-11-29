if __name__ == "__main__":
    start = int(10)
    end = int(19)
    sum = 0
    for num in range(start, end+1, 1):
        sum += num
    print(f"The sum of numbers from {start} to {end} is {sum}")