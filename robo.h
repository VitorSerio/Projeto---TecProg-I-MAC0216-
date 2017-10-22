#ifndef ROBO_H
#define ROBO_H

#include "maq.h"

typedef struct {
    Maquina *m;
    int x;
    int y;
    short int c;
    short int e;
} Robo;

Robo *cria_robo(INSTR *p, short int e, int x, int y);
void destroi_robo(Robo *r);
void roda_robo(Robo *r, int n);
void troca_prog(Robo *r, INSTR *p);

#endif
