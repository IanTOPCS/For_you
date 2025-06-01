    ORG 0000H
    LJMP MAIN

    ORG 000BH
    LJMP T0_ISR

    ORG 001BH
    LJMP T1_ISR

ALT:
    RETI

; play target tone
T0_ISR:
    DJNZ R4, ALT
    MOV DPTR, #Note
    MOV A, R7
    DEC A
    MOV A, @A+DPTR
    MOV DPTR, #TONES
    MOV A, @A+DPTR
    MOV R4, A
    CPL P1.0
    RETI

; change target tone
T1_ISR:
    MOV TH1, HIGH(-50000)
    MOV TL1, LOW(-50000)
    DJNZ R6, ALT
    MOV R6, #0X0A
    DJNZ R3, ALT
    DJNZ R4, chPlayTime
    ; reset
    MOV R7, #42 ; length of note, time
    MOV R6, #0X0A ; for expand delay, loop 10 time
    MOV DPTR, #Note
    MOV A, R7
    DEC A
    MOV A, @A+DPTR
    MOV R5, A ; Note of target tone index
    MOV DPTR, #TONES
    MOV A, R5
    MOV A, @A+DPTR
    MOV R4, A ; Target tone to play (value)
    MOV DPTR, #Time
    MOV A, R7
    DEC A
    MOV A, @A+DPTR
    MOV R3, A ; target tone play how many time?
    RETI

; chang target tone play time
chPlayTime:
    MOV DPTR, #Time
    MOV A, R7
    MOV A, @A+DPTR
    MOV R3, A
    RETI

MAIN:
    MOV TMOD, #12
    MOV TH0, HIGH(-30)
    MOV TH1, HIGH(-50000)
    MOV TL1, LOW(-50000)
    MOV R7, #42 ; length of note, time
    MOV R6, #0X0A ; for expand delay, loop 10 time
    MOV DPTR, #Note
    MOV A, R7
    DEC A
    MOV A, @A+DPTR
    MOV R5, A ; Note of target tone index
    MOV DPTR, #TONES
    MOV A, R5
    MOV A, @A+DPTR
    MOV R4, A ; Target tone to play (value)
    MOV DPTR, #Time
    MOV A, R7
    DEC A
    MOV A, @A+DPTR
    MOV R3, A ; target tone play how many time?
    SETB TR0
    SETB TR1
    MOV IE, #0X8A
    SJMP $

TONES:
	DB 0, 64, 57, 51, 48, 43, 38, 34, 32

; remember tones of music (inverse version, cause code is implement with "DJNZ")
Note:
	DB	1,2,2,3,3,4,4,5,6,6,5,5,1,1	
	DB	2,3,3,4,4,5,5,2,3,3,4,4,5,5
	DB	1,2,2,3,3,4,4,5,6,6,5,5,1,1

; remember each syllable of tones (inverse version)
Time:
	DB	2,1,1,1,1,1,1,2,1,1,1,1,1,1
	DB	2,1,1,1,1,1,1,2,1,1,1,1,1,1
	DB	2,1,1,1,1,1,1,2,1,1,1,1,1,1