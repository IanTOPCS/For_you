; This program is for 8051 assembly language on edisim51, not on board
; To let edisim51 led-ports work, the port has been set to p1, p3.4 p3.3 is used to choose led-port.
; Remember to set update-frequency above 10000, otherwise the delay will be too long.
		ORG	0H
		JMP	INIT
D_ARRAY		EQU	40H		;display information
		
		ORG	30H          	;�g�p�Ғ����N�n�ʚ�

INIT:
		MOV	R0, #D_ARRAY	;prepare display content
		MOV 	@R0,#0
		INC	R0
		MOV 	@R0,#5
		INC	R0
		MOV 	@R0,#1
		INC	R0
		MOV 	@R0,#8
MAIN:
CALL_LOOP:
		MOV	R4, #D_ARRAY	;display content
		MOV R2, #3
		MOV	R5, #0		;start position
		MOV	R6, #4		;display length
		MOV	R7, #1	;delay parameter
		CALL	DISPLAY
		JMP	CALL_LOOP

DELAY:			;input R7
		MOV R3, AR7
DE_LOOP:		
		MOV TMOD, #01H
		MOV TH0, HIGH(-921)
		SETB TR0
WAIT: 	
		JNB TF0, WAIT
		CLR TR0
		CLR TF0
		DJNZ R3, DE_LOOP

		RET
DISPLAY:
;BEGIN OF YOUR CODE
		MOV R0, AR4
		MOV R1, AR5
D_LOOP:
		MOV	DPTR, #POSITION
		MOV	A, R1
		MOVC	A, @A+DPTR	;A=position code
		MOV	P0, A


		MOV	DPTR, #SEGMENT
		MOV	A, @R0
		MOVC	A, @A+DPTR	;A=segment code
		MOV	P1, A

		CALL DisplayDigit

		INC	R1
		INC	R0
		DEC R2
 
		CALL	DELAY
		DJNZ	R6, D_LOOP
		RET

DisplayDigit:

    MOV A, R2
    MOV C, ACC.1
    MOV P3.4, C

    MOV C, ACC.0
    MOV P3.3, C
    RET

SEGMENT:
		DB	0xC0, 0xf9, 0xa4, 0xb0
		DB	0x99, 0x92, 0x82, 0xf8
		DB	0x80, 07FH
POSITION:
		DB	0FEH, 0FDH, 0FBH, 0F7H
		DB	0EFH, 0DFH, 0BFH, 07FH
		END
