    ORG 0000H
    LJMP MAIN

    ORG 000BH
    LJMP T0ISR

    ORG 0013H
    LJMP EX1ISR

    ORG 0040H
MAIN:
    MOV R7, #10 ; loop time of 30*R7
    MOV R6, AR7 ; cnt R7 when loop
    MOV TMOD, #02H ; timer 0 mode 2
    MOV TH0, #-30
    SETB TR0 ; start timer 0
    CLR P0.2 ; detect keyboard row 2
    SETB IT1 ; start exteral 1 interupt
    MOV IE, #0X86
    SJMP $

FLASH_YELLOW:
    CPL P1.1
    RET

T0ISR:
    DJNZ R6, EXIT_T0ISR ; loop R6 time till let light change style
    CALL FLASH_YELLOW
    MOV R6, AR7 ; reset R6
EXIT_T0ISR:
    RETI

EX1ISR:
KEY4:
    JB P0.6, KEY5 ;  if key4 is pressed, P0.6 is 0, else check key5
    CLR C
    MOV A, R7
    SUBB A, #15
    JZ EXIT_EX1ISR ; detect upper bound
    INC R7
    JMP EXIT_EX1ISR
KEY5:
    JB P0.5, KEY6
    CPL TR0 ; let timer 0 enable\disable to light or dark forever
    JMP EXIT_EX1ISR
KEY6:
    JB P0.4, EXIT_EX1ISR
    CLR C
    MOV A, R7
    SUBB A, #5
    JZ EXIT_EX1ISR ; detect lowwer bound
    DEC R7
EXIT_EX1ISR:
    RETI