INLOOP      TD          INDEV       .READ INPUT DEVICE
            JEQ         INLOOP

OUTLOOP     TD          OUTDEV      .READ OUTPUT DEVICE
            JEQ         OUTLOOP

RDWRLP      RD          INDEV       .READ AND WRITE TO OUTPUT DEV BYTE BY BYTE
            COMP        DOLLAR      .BREAK IF '$'
            JEQ         END
            STCH        DATA
            JSUB        CVTNUM      .CHANGE NUMBER TO ALPHA
            LDCH        DATA
            WD          OUTDEV
            J           RDWRLP      .LOOP AGAIN

CVTNUM      LDCH        DATA        .SUBROU TO CHANGE NUMBER INTO ALPHA
            COMP        CZERO       .NOT NECESSARY IF NO OTHER SYMBOLS
            JLT         NOCVT
            COMP        CNINE
            JGT         NOCVT       .DON'T CONVERT IF NOT 0-9
            SUB         CZERO       .SUB '0' ASCII CODE FOR DISPLACE
            ADD         ADISP       .ADD 'a' ASCII CODE 
            STCH        DATA
NOCVT       RSUB


DOLLAR      WORD        X'000024' . C'$'
CZERO       WORD        X'000030' . C'0'
CNINE       WORD        X'000039' . C'9'
ADISP       WORD        X'000061' . C'a'
ZERO        BYTE        0
INDEV       BYTE        X'F1'
OUTDEV      BYTE        X'F2'
DATA        RESB        1


END         LDA         ZERO