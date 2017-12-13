#ifndef EXERCITO_H
#define EXERCITO_H

#include "robo.h"
#include "base.h"

#define MAX_ROBO 6

typedef struct Exercito {
    Robo **robos;
    Base b;
    short int tamanho;
    short int robosCount;
    short int id;
    struct Arena *a;
} Exercito;

Exercito *cria_exercito(Vetor bpos, short int tam);
void destroi_exercito(Exercito *e);
void adiciona_robo(Exercito *e, short int pos, INSTR *p);
void remove_robo(Exercito *e, short int pos);

#endif
