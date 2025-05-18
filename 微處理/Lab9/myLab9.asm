		ORG	0H          	;�t�ζ}���������}��0
		JMP	INIT
D_ARRAY		EQU	40H		;display information
		
		ORG	30H          	;�ϥΪ̵{���_�l��}

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
		MOV	R5, #2		;start position
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
    LOOP:
        CALL DELAY
        MOV DPTR, #POSITION
        MOV A, R5
        MOVC A, @A+DPTR
        INC R5
        MOV P1, A
        SETB P2.3
        CLR P2.3

        MOV DPTR, #D_ARRAY
        MOV A, R6
        MOVC A, @A+DPTR
        MOV P1, A
        DEC R6
        SETB P2.2
        CLR P2.2

        DJNZ R6, LOOP
        RET

SEGMENT:
		DB	03FH, 06H, 05BH, 04FH
		DB	066H, 06DH, 07DH, 07H
		DB	07FH, 06FH
POSITION:
		DB	0FEH, 0FDH, 0FBH, 0F7H
		DB	0EFH, 0DFH, 0BFH, 07FH
		END