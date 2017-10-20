#ifndef ROBO_H
#define ROBO_H

#include "maq.h"

typedef struct {
    Maquina m;
    int x;
    int y;
    short int cristais;
    short int exercito;
} Robo;

Robo *cria_robo(INSTR *p, int x, int y);
void troca_prog(Robo *r, INSTR *p);

#endif
