        . tset error: duplicate start
        .START   1000

        . test error: not valid address "asib41"
COPY    START   1 0 0 0

        . test comment (inline or not)
        RSUB    .jasijfai

FIRST   STL     REtADR
        . test error: lenght != lengthg (label error)
        LDB     #LENGTH

        . test error: comment the line (out of range with pc-relative)
        BASE    LENGTH

CLOOP   +JSUB   RDREC
        
        . test (label + opcode)
SECOND  HIO

        LDA     LENGTH

        . test 2 register (with space and last-coma)
        ADDR    A , x,

        . test "# + 0 ", "# - 0 ", "#" (can calculate positive, negative decimal, space, only ["#" <= error])
        COMP    # - 0

        JEQ     ENDFIL
        
        . test error: base out of range (even sic can't afford)
        +JSUB   WRREC
        J       CLOOP
ENDFIL  LDA     EOF
        STA     BUFFER
        
        . test format-3 range of immediate (-2048~2047)
        LDA     #3

        STA     LENGTH
        +JSUB   WRREC

        . test label with space, case-sensitive, [only "@" <= error]
        J       @ R E t  A D R
        
        . test char with space and case-insensitive (not close with ')
EOF     BYTE    c 'EOF char'

        . test error range of RESW (0~32767)
REtADR  RESW    1

LENGTH  RESW    1
BUFFER  RESB    30000
RDREC   CLEAR   X
        CLEAR   A
        CLEAR   S
        
        . test format-4 range of immediate (-524,288~524,287), and space
        +LDT    # - 4 0 9 6

RLOOP   TD      INPUT
        JEQ     RLOOP
        RD      INPUT
        COMPR   A,S
        JEQ     EXIT

        . test register x with space, case-insensitive
Third   STCH    BUFFER, x

        TIXR    T
        JLT     RLOOP
EXIT    STX     LENGTH
        RSUB

        . test error: hex (invalid hex, and unclose, len=odd)
INPUT   BYTE    X'F1'

        . test register with space, case-insensitive
WRREC   CLEAR   X, a

        LDT     LENGTH
WLOOP   TD      OUTPUT
        JEQ     WLOOP
        LDCH    BUFFER,X
        WD      OUTPUT
        TIXR    T
        JLT     WLOOP
        RSUB
OUTPUT  BYTE    X'05'
        END     FIRST
