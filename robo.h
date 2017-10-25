#ifndef ROBO_H
#define ROBO_H

#include "maq.h"
#include "vetor.h"

typedef struct Robo {
    Maquina *m;
    Vetor pos;
    short int c;
    short int id;
    struct Exercito *e;
} Robo;

Robo *cria_robo(INSTR *p, Vetor pos, short int id);
void destroi_robo(Robo *r);
void roda_robo(Robo *r, int n);
void troca_prog(Robo *r, INSTR *p);

#endif
