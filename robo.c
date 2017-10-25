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

#define m (r->m)
#define rpos (r->pos)
#define c (r->c)
#define rid (r->id)

Robo *cria_robo(INSTR *p, Vetor pos, short int id) {

    Robo *r = (Robo*)malloc(sizeof(Robo));
    if (!r) Fatal("Memória insuficiente para Robo",4);

    m = cria_maquina(p);
    m->r = r;

    rpos.x = pos.x;
    rpos.y = pos.y;

    rid = id;

    c = 0;

    return r;
}

void destroi_robo(Robo *r) {
    destroi_maquina(m);
    free(r);
    r = NULL;
}

void troca_prog(Robo *r, INSTR *p) {
    destroi_maquina(m);
    m = cria_maquina(p);
    m->r = r;
}

void roda_robo(Robo *r, int n) {
    exec_maquina(m, n);
}
