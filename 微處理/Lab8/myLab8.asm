; The program's result is as same as other programs in Lab8 directory
; The led table "segment" source copy from "LEDtable"
; When you press sw button from 0~7, the digit will display on led in edisim51
; Without any pressed sw, led will display default value "F"
    org 0H
    JMP MAIN
MAIN:
    MOV R0, #0X00 ; index of led table to show value on led
    CALL DETECT
    JMP MAIN

DETECT:
    JNB P2.0, L0
    JNB P2.1, L1
    JNB P2.2, L2
    JNB P2.3, L3
    JNB P2.4, L4
    JNB P2.5, L5
    JNB P2.6, L6
    JNB P2.7, L7
    JMP LDEFAULT
    RET
    
LDEFAULT:
    MOV R0, #0X0F
    CALL display
    RET
L0:
    MOV R0, #0X00
    CALL display
    RET
L1:
    MOV R0, #0X01
    CALL display
    RET
L2:
    MOV R0, #0X02
    CALL display
    RET
L3:
    MOV R0, #0X03
    CALL display
    RET
L4:
    MOV R0, #0X04
    CALL display
    RET
L5:
    MOV R0, #0X05
    CALL display
    RET
L6:
    MOV R0, #0X06
    CALL display
    RET
L7:
    MOV R0, #0X07
    CALL display
    RET

display:
    MOV DPTR, #segment
    MOV A, R0
    MOVC A, @A+DPTR
    MOV P1, A
    RET
segment:
    DB 0xc0, 0xf9, 0xa4, 0xb0, 0x99
    DB 0x92, 0x82, 0xf8, 0x80, 0x98
    DB 0x88, 0x83, 0xc6, 0xa1, 0x86
    DB 0x8e