#ifndef EXERCITO_H
#define EXERCITO_H

#include "robo.h"
#include "base.h"

#define MAXVM 5

typedef struct {
    Robo **robos;
    Base b;
    short int size;
    short int e;
} Exercito;

Exercito *cria_exercito(INSTR **progs, short int e, int x, int y);
void destroi_exercito(Exercito *e);

#endif
