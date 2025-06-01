; interupt will clear timer overflow flag, even you use mode 1.

        ORG 0000H
        LJMP MAIN          ; Jump to main program

        ORG 000BH	; Timer0 interrupt vector
        LJMP T0_ISR       

        ORG 001BH	; Timer0 interrupt vector        
        LJMP T1_ISR

; let tone obey frequence with 30*(target tone)
T0_ISR:
		DJNZ R6, ALT1
		MOV A, R7
		MOVC A, @A+DPTR 
		MOV R6, A
		CPL P1.0 ; change high-low, playing tone by 8051-machine
		
		RETI
ALT1:
		RETI

; change the tone
T1_ISR:
		MOV TH1, HIGH(-50000) ; max 16 bits value is 65536, so set 50000 and expand by loop
		MOV TL1, LOW(-50000)
		DJNZ R5, ALT2
		MOV R5, #10 ; to set 500 000ms delay, let loop ten time (one 8051 machine cycle is 1 ms)
		DJNZ R7, ALT2
		MOV R7, #8 ; set length of 8 tone
		RETI
ALT2:
		RETI
MAIN:
		MOV DPTR, #TONES
		MOV TMOD, #12H ; timer 1 mode 1, timer 0 mode 2
		MOV TH0, #-30 ; set timer-0's high bytes -30, after overflow, auto reload
		MOV TH1, HIGH(-50000)
		MOV TL1, LOW(-50000)
		MOV R6, #0x00
		MOV R7, #8
		MOV R5, #10
		SETB TR0 ; let timer 0 start
		SETB TR1 ; let timer 1 start
		MOV IE, #8AH ; let timer interupt enable
		SJMP $
		
TONES:
		DB 0, 32, 34, 38, 43, 48, 51, 57, 64
