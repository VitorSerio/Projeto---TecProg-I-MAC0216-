#ifndef ROBO_H
#define ROBO_H

#include "maq.h"
#include "vetor.h"

#define R_MAX_HP 5

typedef struct Robo {
    Maquina *m;
    Vetor pos;
    short int hp;
    short int c;
    short int id;
    struct Exercito *e;
} Robo;

Robo *cria_robo(INSTR *p, Vetor pos);
void destroi_robo(Robo *r);
void roda_robo(Robo *r, int n);
void troca_prog(Robo *r, INSTR *p);

#endif
