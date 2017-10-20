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
    STL,
    RCE,
    ALC,
    FRE,
    ATR,
    SIS
} OpCode;

/* Instrução */
typedef struct {
    OpCode instr;
    OPERANDO op;
} INSTR;

#endif
