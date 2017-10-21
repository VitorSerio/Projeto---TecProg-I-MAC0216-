#include <stdio.h>
#include <stdlib.h>
#include "exercito.h"

static void Erro(char *msg) {
    fprintf(stderr,"%s\n", msg);
}

static void Fatal(char *msg, int cod) {
    Erro(msg);
    exit(cod);
}

Exercito *cria_exercito(INSTR *progs[], short int e, int x, int y) {
    Exercito *ex = (Exercito*)malloc(sizeof(Exercito));
    if (!ex) Fatal("Memória insuficiente para Exercito",4);
    ex->e = e;
    ex->b = (Base) {.x = x, .y = y, .e = e};

    int n = sizeof(progs) / sizeof(INSTR*);
    if (n > MAXVM) {
        printf("Aviso: Foram dados mais programas que o limite ");
        Erro("permitido. Apenas os %d primeiros serão usados.", MAXVM);
        n = MAXVM;
    }
    for (int i = 0; i < n; i++)
        ex->robos[i] = cria_robo(progs[i], e, x, y);

    return ex;
}

void destroi_exercito(Exercito *e) {
    free(e);
}
