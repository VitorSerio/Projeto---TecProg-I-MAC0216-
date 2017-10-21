#ifndef OPERANDO_H
#define OPERANDO_H

#include "acao.h"
#include "celula.h"

/* Tipos dos operandos */
typedef enum {
    NUM,
    ACAO,
    CELULA
} Tipo;

/* Operando */
typedef struct {
    Tipo t;
    union {
        int n;
        Acao ac;
        Celula cel;
    } val;
} OPERANDO;

char *toString(OPERANDO op);

#endif
