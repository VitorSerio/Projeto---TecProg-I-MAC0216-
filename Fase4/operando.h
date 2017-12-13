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
typedef struct OPERANDO {
    Tipo t;
    union {
        int n;
        Acao ac;
        Celula cel;
    } val;
} OPERANDO;

char *toString_operando(OPERANDO op);

#endif
