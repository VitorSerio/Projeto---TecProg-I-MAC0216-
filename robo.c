#include <stdio.h>
#include <stdlib.h>
#include "robo.h"

static void Erro(char *msg) {
    fprintf(stderr,"%s\n", msg);
}

static void Fatal(char *msg, int cod) {
    Erro(msg);
    exit(cod);
}

Robo *cria_robo(INSTR *p, short int e, int x, int y) {
    Robo *r = (Robo*)malloc(sizeof(Robo));
    if (!r) Fatal("Memória insuficiente para Robo",4);
    r->m = cria_maquina(p);
    r->x = x;
    r->y = y;
    r->c = 0;
    r->e = e;
    return r;
}

void troca_prog(Robo *r, INSTR *p) {
    destroi_maquina(r->m);
    r->m = cria_maquina(p);
}

void destroi_robo(Robo *r) {
    free(r);
}
