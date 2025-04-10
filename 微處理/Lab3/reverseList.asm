  ORG 0x00
  jmp INIT
LENGTH EQU 0x40
ARRAY EQU 0x41
  ORG 0x30

INIT:
  mov 0x40, #7
  mov 0x41, #'K'
  mov 0x42, #'e'
  mov 0x43, #'i'
  mov 0x44, #'l'
  mov 0x45, #'A'
  mov 0x46, #'5'
  mov 0x47, #'1'

MAIN:
  ;求交換次數，存到R3
  mov A, LENGTH
  RRC A
  CLR C ;避免(奇數時)進位C被ADDC吃到
  mov R3, A

  ;R0存陣列開始位置
  mov R0, #ARRAY
  
  ;R1存陣列結束位置
  mov A, #ARRAY
  ADDC A, LENGTH
  DEC A
  mov R1, A

LOOP:
  ;交換
  ;@R1->R2
  mov A, @R1
  mov R2, A

  ;@R0->@R1
  mov A, @R0
  mov @R1, A

  ;R2->@R0
  mov A, R2
  mov @R0, A

  ;R0遞增、R1遞減、交換次數遞減
  INC R0
  DEC R1
  DEC R3
  CJNE R3, #0x00, LOOP
  jmp $
