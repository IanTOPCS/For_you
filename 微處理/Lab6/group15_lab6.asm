	ORG	0h
	JMP INIT

INIT:
	MOV	20H, #1		;wņINęy
	MOV	21H, #3		; 
	MOV	22H, #6		
	MOV	23H, #9		
	MOV	24H, #13		
	MOV	25H, #15		
	MOV	26H, #18		;
	MOV	27H, #22
	MOV	28H, #25
	MOV	29H, #28

MAIN:               	;gpŌåöŪ
	MOV	R0, #20H		;wņINęy
	MOV	R1, #10	;wņI·x
	MOV 0X30, R0
	MOV 0X31, R1
	CALL	QUARTILE
	JMP	$   		;ĩņĐČCģĀį, Ýû?Ao
QUARTILE:
	CALL MEDIAN		;ÝUüöŪ
	MOV AR2, R6
	MOV AR3, R7

	MOV A, 0X31
	RRC A
	MOV R1, A
	
	MOV A, 0X30
	MOV R0, A

	

	CALL MEDIAN
	MOV AR4, R6
	MOV AR5, R7

	MOV A, 0X31
	CLR C
	RRC A
	MOV R1, A
	
	MOV A, 0X30
	ADD A, 0X31
	
	SUBB A, R1
	MOV R0, A

	CALL MEDIAN
	RET
MEDIAN:
	CLR C
	MOV A, R1
	RRC A
	JC ODD  
	JMP EVEN
	ODD:
		ADD A, R0
		MOV R0, A
		MOV AR6, @R0
		MOV R7, #0H
		RET
	EVEN:
		ADD A, R0
		MOV R0, A
		DEC R0
		MOV A, @R0
		INC R0
		ADD A, @R0
		RRC A
		MOV R6, A
		JC EBIN
		MOV R7, #0
		RET
	EBIN:
		MOV R7, #1
		RET
		
	