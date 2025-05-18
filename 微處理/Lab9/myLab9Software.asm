    ORG 0H
    JMP INIT

    D_ARRAY	EQU	40H
    ORG 30H

INIT:
    MOV R0, #D_ARRAY
    MOV @R0, #0X08
    INC R0
    MOV @R0, #0X00
    INC R0
    MOV @R0, #0X05
    INC R0
    MOV @R0, #0X01

MAIN:
    MOV R6, #D_ARRAY; set display value address
    MOV R2, #0X20 ; set delay value
    MOV R4, #0X03 ; index of led position
    MOV R5, #0X04 ; display length
    CALL DISPLAY
    JMP MAIN

; Total delay is (0x20 * 0x20)cycles
; The delay is using instruction. 
; It's not accurate, you never know what program actual do with pipeline, cause delay will implement together with other code
DELAY:
    D1:
        MOV R0, #0X20
        DJNZ R0, $
        DJNZ R2, D1
        RET
DISPLAY:
    LOOP:
        CALL DELAY
        ; set position of led
        MOV A, R4
        DEC R4
        MOV C, ACC.1
        MOV P3.4, C
        MOV C, ACC.0
        MOV P3.3, C

        ; take led digit value
        MOV R0, AR6
        INC R6

        ; correspond digit value to led number table
        MOV DPTR, #SEGMENT
        MOV A, @R0
        MOVC A, @A+DPTR

        ; show result on led
        MOV P1, A

        DJNZ R5, LOOP
        RET

segment:
    DB 0xc0, 0xf9, 0xa4, 0xb0, 0x99
    DB 0x92, 0x82, 0xf8, 0x80, 0x98
    DB 0x88, 0x83, 0xc6, 0xa1, 0x86
    DB 0x8e