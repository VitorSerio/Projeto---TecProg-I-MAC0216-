        PUSH    1
        PUSH    1
        STO     0 # x
        STO     1 # y

LOOP:   CALL    FIBO
        PRN
        STO     1
        STO     0
        JMP     LOOP

FIBO:   RCL     1
        DUP
        RCL     0
        ADD
        DUP
        RET

END
