#ifndef MAQ_H
#define MAQ_H

#include "pilha.h"

#define MAXMEM 99

struct Robo;

typedef struct {
    Pilha pil;
    Pilha exec;
    OPERANDO Mem[MAXMEM+1];
    INSTR *prog;
    int rbp;
    int ip;
    struct Robo *r;
} Maquina;

Maquina *cria_maquina(INSTR *p);
void destroi_maquina(Maquina *m);
void exec_maquina(Maquina *m, int n);

#endif
