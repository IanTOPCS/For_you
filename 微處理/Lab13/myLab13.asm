; This program is play DO->Re->mi->fa->so...on 8051-machine board
    ORG 0000H
    LJMP MAIN

    ORG 000BH
    LJMP T0_ISR

    ORG 001BH
    LJMP T1_ISR

ALT:
    RETI

; play the target tone
T0_ISR:
    DJNZ R5, ALT
    MOV DPTR, #TONES
    MOV A, R6 ; now tone (length)
    MOVC A, @A+DPTR
    MOV R5, A
    CPL P1.0 ; change high-low (frequence)
    RETI

; change the target tone
T1_ISR:
    MOV TH1, HIGH(-50000)
    MOV TL1, LOW(-50000)
    DJNZ R7, ALT
    ; reset
    MOV R7, #0X0A
    DJNZ R6, ALT
    MOV R6, #0X08
    RETI

MAIN:
    MOV TMOD, #12
    MOV TH0, HIGH(-30)
    MOV TH1, HIGH(-50000)
    MOV TL1, LOW(-50000)
    MOV R7, #0X0A ; loop 10 times
    MOV R6, #0X08 ; length of tones
    MOV DPTR, #TONES
    MOVC A, @A+DPTR
    MOV R5, A ; R5 is target tone now to play
    SETB TR0
    SETB TR1
    MOV IE, #0X8A
    SJMP $

; the tones is reverse version, the last one is "DO"
TONES:
	DB 0, 32, 34, 38, 43, 48, 51, 57, 64