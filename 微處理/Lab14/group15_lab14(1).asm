        ORG 0000H
        LJMP MAIN          ; Jump to main program

        ORG 000BH          ; Timer0 interrupt vector
        LJMP T0_ISR       

        ORG 001BH          
        LJMP T1_ISR

; play target tone by R6
T0_ISR:
		DJNZ R6, ALT
		MOV DPTR, #Note
		MOV A, R7
		MOVC A, @A+DPTR
		MOV DPTR, #TONES
		MOVC A, @A+DPTR		
		MOV R6, A
		CPL P1.0
		
		RETI
ALT:
		RETI
T1_ISR:
		MOV TH1, HIGH(-50000)
		MOV TL1, LOW(-50000)
		DJNZ R5, ALT
		MOV R5, #10
		DJNZ R4, ALT ; how many time play target tone (Time table)
		DJNZ R7, R7ALT ; change the tone
		; reset
		MOV R7, #42
		MOV DPTR, #Time
		MOV A, R7
		DEC A
		MOVC A, @A+DPTR
		MOV R4, A
		RETI

; get how many time the target tone play with R4
R7ALT:
		MOV DPTR, #Time
		MOV A, R7
		MOVC A, @A+DPTR
		MOV R4, A
		RETI
MAIN:
		MOV DPTR, #TONES
		MOV TMOD, #12H
		MOV TH0, #-30
		MOV TH1, HIGH(-50000)
		MOV TL1, LOW(-50000)
		MOV R6, #0x00
		MOV R7, #42 ; length of tones in music
		MOV R5, #10 ; expand delay to 500 000ms by 10 loop
		MOV R4, #1 ; The last of Time-table
		SETB TR0;
		SETB TR1;
		MOV IE, #8AH
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
