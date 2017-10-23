#ifndef EXERCITO_H
#define EXERCITO_H

#include "robo.h"
#include "base.h"

#define MAX_ROBO 6

typedef struct Exercito {
    Robo **robos;
    Base b;
    short int size;
    short int id;
    struct Arena *a;
} Exercito;

Exercito *cria_exercito(int x, int y);
void destroi_exercito(Exercito *e);
void adiciona_robo(Exercito *e, INSTR *p);
void remove_robo(Exercito *e, int pos);

#endif
