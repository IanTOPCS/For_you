init:
    li x2, 5
    li x3, 0x0fbd0063
    sw x3, 0(x2)
    li x3, 0x6e055ff5
    sw x3, 4(x2)
    li x3, 0x00004df7
    sw x3, 8(x2)
    call findMax
    nop

findMax:
    lb x3, 0(x2)    # init x3, the tempAns of max
    addi x2, x2, 1  # shift index of list, x2
    addi x5, x0, 14 # index of list, end of loop
loop:
    lb x4, 0(x2)    # new source of list, compare to x3
    blt x3, x4, change
continueCmp:
    addi x2, x2, 1  # shift index of list, x2
    bne x2, x5, loop
    addi x6, x0, 1  # use shift ans into x31 (?*1 = ?)
    mul x31, x3, x6 # move answer into x31
    ret
change:
    lb x3, 0(x2)    # change max, shift x4 => x3
    j continueCmp