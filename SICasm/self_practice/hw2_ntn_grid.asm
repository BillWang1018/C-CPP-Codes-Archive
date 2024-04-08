BEGIN       START       0

. MAIN FUNCTION -------------------

TDOUT       TD          OUTDEV      . TEST OUTDEV
            JEQ         TDOUT    

            CLEAR       S
            CLEAR       T           . S AND T FOR COUNTING

TESTT       RMO         T,A         . IF T<10
            COMP        #10
            JLT         TESTS       . GOTO TESTS
            LDA         #1          . S++, T=0
            ADDR        A,S         
            CLEAR       T
            LDCH        NEWLINE     . PRINT A NEWLINE
            WD          OUTDEV          

TESTS       RMO         S,A         . IF S>9
            COMP        #9
            JGT         ENDPROG     . END PROGRAM

            RMO         T,A         . IF T>0
            COMP        #0
            JGT         PRTPRD      . GOTO PRINT PRODUCT
            RMO         S,A         . (IF T=0) PRINT HEADING, IF S>0
            COMP        #0
            JGT         PRTS        . GOTO PRINT S, OR PRINT SPACE
            JSUB        PRTSP       
            J           LOOPT       . END LOOP, T++
PRTS        RMO         S,A
            JSUB        PRTNUM
            J           LOOPT

PRTPRD      RMO         S,A         . PRINT S*A, WIDTH=2
            COMP        #0          . IF S>0
            JGT         TIMET       . GOTO TIMES T (DO CALC)
            ADD         #1          . (IF S=0) SAME AS S=1
TIMET       MULR        T,A         . A = S*T

            COMP        #9          . IF A>9 (HAVE 2 CHAR)
            JGT         PTWODIG     . GOTO "PRINT TWO DIGIT"
            JSUB        PRTNUM      . PRINT A NUMBER + A SPACE
            JSUB        PRTSP       
            J           LOOPT       . READY TO THIS LOOP

PTWODIG     STA         ALPHA       . SAVE S*T
            DIV         #10         . A/=10
            JSUB        PRTNUM      . PRINT TENS
            MUL         #10         . A -= A'S_TENS
            STA         TENS
            LDA         ALPHA
            SUB         TENS
            JSUB        PRTNUM      . PRINT ONES

LOOPT       LDA         #1          . END OF LOOP, T++
            ADDR        A,T
            J           TESTT

. SUB-ROUTINES --------------------

PRTSP       LDCH        SPACE       . PRINT A SPACE
            WD          OUTDEV
            RSUB

PRTNUM      ADD         CZERO       . PRINT A NUMBER FROM R(A) (CHANGED TO ASCII)
            WD          OUTDEV
            SUB         CZERO
            RSUB

. VARIABLES -----------------------

OUTDEV      BYTE        X'F2'
SPACE       BYTE        X'20'
NEWLINE     BYTE        X'0A'
CZERO       WORD        X'000030'
ALPHA       WORD        0
TENS        WORD        0

. END -----------------------------

ENDPROG     CLEAR       A           . END OF PROGRAM
            END         TDOUT