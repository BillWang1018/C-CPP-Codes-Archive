. INSTRUCTION .
            LDA         FIVE
            ADD         THREE
            STA         ALPHA
            LDA         FIVE
            MUL         THREE
            STA         BETA
            SUB         ALPHA
            STA         GAMMA
.
            LDA         ALPHA
            COMP        GAMMA
            JLT         LESS
            JGT         GREAT
LESS        LDCH        CHARL
            STCH        RESULT
            JLT         ENDPROG
GREAT       LDCH        CHARG
            STCH        RESULT
ENDPROG     LDA         ZERO
.
. CONSTANT .
ZERO        WORD        0
THREE       WORD        3
FIVE        WORD        5
CHARG       BYTE        C'G'
CHARL       BYTE        C'L'
. VARIABLE .
ALPHA       RESW        1
BETA        RESW        1
GAMMA       RESW        1
RESULT      RESB        1