#include <stdio.h>
#include <stdlib.h>
#include "exercito.h"
#include "robo.h"
#include "exercito.h"

static void Erro(char *msg) {
    fprintf(stderr,"%s\n", msg);
}

static void Fatal(char *msg, int cod) {
    Erro(msg);
    exit(cod);
}

Exercito *cria_exercito(INSTR **progs, short int n, short int e, int x,
                        int y) {
    Exercito *ex = (Exercito*)malloc(sizeof(Exercito));
    if (!ex) Fatal("Erro: Memória insuficiente para Exercito",4);
    ex->e = e;
    ex->b = (Base) {.x = x, .y = y, .e = e};

    if (n > MAXVM) {
        Erro("Aviso: Foram dados mais programas que o limite permitido. Apenas os primeiros serão usados.");
        n = MAXVM;
    }
    ex->robos = (Robo**)malloc(MAXVM * sizeof(Robo*));

    for (int i = 0; i < MAXVM; i++) ex->robos[i] = NULL;

    for (int i = 0; i < n; i++) adiciona_robo(ex, progs[i]);

    return ex;
}

void destroi_exercito(Exercito *e) {
    for (int i = 0; i < MAXVM; i++) {
        if (!e->robos[i])
            continue;
        destroi_robo(e->robos[i]);
        e->robos[i] = NULL;
        e->size--;
    }
    free(e->robos);
    e->robos = NULL;
    free(e);
    e = NULL;
}

void adiciona_robo(Exercito *e, INSTR *p) {
    if (e->size + 1 > MAXVM) {
        Erro("Aviso: Não é possível adicionar mais robôs ao exército.");
        return;
    }
    short int dx[] = {1, 0, 1, -1, 0, -1};
    short int dy[] = {0, 1, -1, 0, -1, 1};

    int i = 0;
    while (i < MAXVM) {
        if (!e->robos[i]) break;
        printf("loop %d\n", i);
        i++;
    }
    printf("fim loop %d\n", i);
    e->robos[i] = cria_robo(p, e->b.x + dx[i], e->b.y + dy[i]);
    printf("cria\n");
    e->robos[i]->e = e;
    printf("e->\n");
    e->robos[i]->id = i;
    printf("id->\n");
    e->size++;
    printf("size = %d\n", e->size);
}

void remove_robo(Exercito *e, int pos) {
    if (!e->robos[pos]) {
        Erro("Aviso: Não há robôs na posição dada.");
        return;
    }
    destroi_robo(e->robos[pos]);
    e->robos[pos] = NULL;
    e->size--;
}
