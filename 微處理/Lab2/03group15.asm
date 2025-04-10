;按下button 0(switch 0)，bit為0
;按下button 0，反向顯示(F~0)
start:
sp0:
	MOV P1, #0xc0	;七段顯示器0
	JNB P2.0, spF ;如果P2(button 0 位置)第零個bit是零，跳到spF的label
	JMP sp1				;無條件跳到sp1的label
sp1:
	MOV P1, #0xf9
	JNB P2.0, sp0
	JMP sp2
sp2:
	MOV P1, #0xa4
	JNB P2.0, sp1
	JMP sp3
sp3:	
	MOV P1, #0xb0
	JNB P2.0, sp2
	JMP sp4
sp4:
	MOV P1, #0x99
	JNB P2.0, sp3
	JMP sp5
sp5:
	MOV P1, #0x92
	JNB P2.0, sp4
	JMP sp6
sp6:
	MOV P1, #0x82
	JNB P2.0, sp5
	JMP sp7
sp7:
	MOV P1, #0xd8
	JNB P2.0, sp6
	JMP sp8
sp8:
	MOV P1, #0x80
	JNB P2.0, sp7
	JMP sp9
sp9:
	MOV P1, #0x90
	JNB P2.0, sp8
	JMP spA
spA:
	MOV P1, #0x88
	JNB P2.0, sp9
	JMP spB
spB:
	MOV P1, #0x83
	JNB P2.0, spA
	JMP spC
spC:
	MOV P1, #0xc6
	JNB P2.0, spB
	JMP spD
spD:
	MOV P1, #0xa1
	JNB P2.0, spC
	JMP spE
spE:
	MOV P1, #0x86
	JNB P2.0, spD
	JMP spF
spF:
	MOV P1, #0x8E
	JNB P2.0, spE
	JMP sp0
