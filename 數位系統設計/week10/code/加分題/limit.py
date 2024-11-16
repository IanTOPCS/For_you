if __name__  == "__main__":
    ans = 1
    for i in range(1, 16):
        ans = ans*i
        YN = "Y" if(ans < int(2147483647)) else"N"
        print(f"{i:<2} : {ans:<13}, len : {len(str(ans)):<2},  bits len : {ans.bit_length():<2}, display : {YN}")
