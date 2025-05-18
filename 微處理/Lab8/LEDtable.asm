    org 0H
    jmp main
MAIN:
    mov r3, #0x00 ; index of led
    CALL display
    jmp MAIN
display:
    mov a, r3
    mov dptr, #segment
    movc A, @A+dptr ; display digit with led
    mov p1, A
    INC r3 ; index plus one
    cjne r3, #0x10, display
    RET
segment:
    DB 0xc0, 0xf9, 0xa4, 0xb0, 0x99
    DB 0x92, 0x82, 0xf8, 0x80, 0x98
    DB 0x88, 0x83, 0xc6, 0xa1, 0x86
    DB 0x8e