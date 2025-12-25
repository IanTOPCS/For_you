#立即值定址
    addi x1, x0, 1
    slti x2, x0, 10
    sltiu x3, x0, 15
    xori x4, x1, 0xF
    ori x5, x2, 0x7
    andi x6, x3, 0x3
    slli x7, x4, 2
    srli x8, x5, 1
    srai x9, x4, 1

#暫存器定址
    add x12, x1, x2
    sub x13, x3, x4
    slt x14, x10, x11
    sltu x15, x8, x7
    and x16, x11, x4
    or  x17, x11, x12
    xor x18, x13, x14
    sll x19, x15, x1
    srl x20, x16, x2
    sra x21, x17, x3

#分支預測
        beq x1, x2, test_beq
        addi x22, x0, 0
    test_beq:
        addi x22, x0, 1
        bne x3, x4, test_bne
        addi x23, x0, 0
    test_bne:
        addi x23, x0, 1
        blt x5, x6, test_blt
        addi x24, x0, 0
    test_blt:
        addi x24, x0, 1
        bge x7, x8, test_bge
        addi x25, x0, 0
    test_bge:
        addi x25, x0, 1
        bltu x9, x10, test_bltu
        addi x26, x0, 0
    test_bltu:
        addi x26, x0, 1
        bgeu x11, x12, test_bgeu
        addi x27, x0, 0
    test_bgeu:
        addi x27, x0, 1

#無條件跳躍
    jal x28, jump
    add x29, x6, x7
    lui x10, 0x12345
    auipc x11, 0x20000

#記憶體存取
	sb x13, 0(x0)
	sh x13, 1(x0)
	sw x13, 2(x0)
    lw x1, 0(x0)
	lw x2, 2(x0)
	lh x3, 1(x0)
	lhu x4, 1(x0)
    lhu x5, 2(x0)
    lb x6, 3(x0)
	lbu x7, 3(x0)
    lbu x8, 5(x0)

    j end
jump:
	addi x4, x0, 1
    jalr x4, x28, 0
end:
    nop
