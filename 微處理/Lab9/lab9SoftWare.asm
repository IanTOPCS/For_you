; This program is for 8051 assembly language on edisim51, not on board
; To let edisim51 led-ports work, the port has been set to p1, p3.4 p3.3 is used to choose led-port.
; Remember to set update-frequency above 1000, otherwise the delay will be too long.
		ORG	0H          	
		JMP	INIT
		D_ARRAY	EQU	40H		;display information
		
		ORG	30H          	

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
		MOV	R5, #3		;start position (position on edisim51 is 3->2->1->0)
		MOV	R6, #4		;display length
		MOV	R7, #20		;delay parameter
		CALL	DISPLAY
		JMP	CALL_LOOP

DELAY:			;input R7
D1:		
		MOV 	R3,#32
		DJNZ 	R3,$
		DJNZ 	R7,D1
		RET 

DISPLAY:
;BEGIN OF YOUR CODE
	LOOP:
		CALL DELAY
    	CALL DisplayDigit
		DEC R5

		MOV R0, AR4 ;R4 is the address of the display content
		INC R4
		MOV DPTR, #SEGMENT ;numbers display on led
		MOV A, @R0 ;@R0 pick up the number with address
		MOVC A, @A+DPTR
		MOV P1, A ;display the number on led(p1)
		
		DJNZ R6, LOOP
	RET

DisplayDigit:
    MOV A, R5
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