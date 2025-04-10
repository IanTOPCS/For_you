ORG 0x00
LENGTH EQU 0x0B

main:
  mov DPTR, #data
  mov R0, #0x00
  call NEXT

NEXT:
  jmp LOOP
  ret

LOOP:
  mov A, R0
  MOVC A, @A+DPTR
  mov p1, A
  JNB p2.0, R0DEC
  jmp R0INC

R0DEC:
  CJNE R0, #0x00, de0
  mov R0, #LENGTH
  jmp LOOP

de0:
  DEC R0
  jmp LOOP

R0INC:
  CJNE R0, #LENGTH, upbound
  mov R0, #0x00
  jmp LOOP

upbound:
  INC R0
  jmp LOOP

data:
  DB 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xD8, 0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E