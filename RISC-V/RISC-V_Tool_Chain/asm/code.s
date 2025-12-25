init:
    li x2, 5
    li x3, 0x0fbd0063
    sw x3, 0(x2)
    li x3, 0x6e055ff5
    sw x3, 4(x2)
    li x3, 0x00004df7
    sw x3, 8(x2)
# ----my-assembly----
    call findMax
    nop

findMax:
    lb x3, 0(x2)        # tmp max
    addi x2, x2, 1
    addi x4, x0, 15     # init end of loop
loop:
    lb x5, 0(x2)
    blt x3, x5, chg
con:
    addi x2, x2, 1
    bne x2, x4, loop
    add x31, x0, x3
    ret

chg:
    lb x3, 0(x2)
    j con