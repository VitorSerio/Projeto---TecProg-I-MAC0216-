#ifndef INSTR_H
#define INSTR_H

#include "operando.h"

/* Códigos das instruções */
typedef enum {
    PUSH,
    POP,
    DUP,
    ADD,
    SUB,
    MUL,
    DIV,
    JMP,
    JIT,
    JIF,
    CALL,
    RET,
    STS,
    RCS,
    EQ,
    GT,
    GE,
    LT,
    LE,
    NE,
    STO,
    RCL,
    END,
    PRN,
    ATR,
    SIS,
    ENTRY,
    LEAVE
} OpCode;

/* Instrução */
typedef struct INSTR {
    OpCode instr;
    OPERANDO op;
} INSTR;

#endif
