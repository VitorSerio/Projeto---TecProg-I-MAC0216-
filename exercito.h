#ifndef EXERCITO_H
#define EXERCITO_H

#include "robo.h"
#include "base.h"

#define MAXVM 6

struct Arena;

typedef struct {
    Robo **robos;
    Base b;
    short int size;
    short int e;
    struct Arena *a;
} Exercito;

Exercito *cria_exercito(INSTR **progs, short int n, short int e, int x, int y);
void destroi_exercito(Exercito *e);
void adiciona_robo(Exercito *e, INSTR *p);
void remove_robo(Exercito *e, int pos);

#endif
