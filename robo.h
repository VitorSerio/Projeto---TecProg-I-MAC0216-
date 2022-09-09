#ifndef ROBO_H
#define ROBO_H

#include "maq.h"

typedef struct Robo {
    Maquina *m;
    int x;
    int y;
    short int c;			//Quantidade de cristais que ele está carregando
    short int id;
    struct Exercito *e;
    int s;					//Perncetual de avaria
    int o;					//Nível de ocupação do Robo
} Robo;

Robo *cria_robo(INSTR *p, int x, int y);
void destroi_robo(Robo *r);
void roda_robo(Robo *r, int n);
void troca_prog(Robo *r, INSTR *p);
void diminui_saude(Robo *r, int quant);
void altera_ocupacao(Robo *r, int quant);
void decrementa_ocupacao(Robo *r);

#endif
