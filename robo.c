#include <stdio.h>
#include <stdlib.h>
#include "maq.h"
#include "robo.h"
#include "exercito.h"

static void Erro(char *msg) {
    fprintf(stderr,"%s\n", msg);
}

static void Fatal(char *msg, int cod) {
    Erro(msg);
    exit(cod);
}

Robo *cria_robo(INSTR *p, int x, int y) {
    Robo *r = (Robo*)malloc(sizeof(Robo));
    if (!r) Fatal("Memória insuficiente para Robo",4);
    r->m = cria_maquina(p);
    r->m->r = r;
    r->x = x;
    r->y = y;
    r->c = 0;
    return r;
}

void destroi_robo(Robo *r) {
    destroi_maquina(r->m);
    free(r);
    r = NULL;
}

void troca_prog(Robo *r, INSTR *p) {
    destroi_maquina(r->m);
    r->m = cria_maquina(p);
    r->m->r = r;
    r->m->pil.topo = 0;
    r->m->exec.topo = 0;
}

void roda_robo(Robo *r, int n) {
    exec_maquina(r->m, n);
}
