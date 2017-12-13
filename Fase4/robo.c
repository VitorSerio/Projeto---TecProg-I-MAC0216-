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

Robo *cria_robo(INSTR *p, Vetor pos) {

    Robo *r = (Robo*) malloc(sizeof(Robo));
    if (!r) Fatal("Erro: Memória insuficiente para Robo.", 4);

    m = cria_maquina(p);
    m->r = r;

    rpos.x = pos.x;
    rpos.y = pos.y;

    r->hp = R_MAX_HP;

    c = 0;

    return r;
}

void destroi_robo(Robo *r) {
    free(r);
    r = NULL;
}

void troca_prog(Robo *r, INSTR *p) {
    m = cria_maquina(p);
    m->r = r;
}

void roda_robo(Robo *r, int n) {
    exec_maquina(m, n);
}
