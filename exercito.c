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

Exercito *cria_exercito(int x, int y) {
    Exercito *e = (Exercito*)malloc(sizeof(Exercito));
    if (!e) Fatal("Erro: Memória insuficiente para Exercito",4);
    e->b.x = x;
    e->b.y = y;
    
    e->robos = (Robo**)malloc(MAX_ROBO * sizeof(Robo*));
    if (!e->robos) Fatal("Erro: Memória insuficiente para múltiplos Robo*",4);
    for (int i = 0; i < MAX_ROBO; i++) e->robos[i] = NULL;

    return e;
}

void destroi_exercito(Exercito *e) {
    for (int i = 0; i < MAX_ROBO; i++) {
        if (!e->robos[i])
            continue;
        destroi_robo(e->robos[i]);
        e->size--;
    }
    free(e->robos);
    e->robos = NULL;
    free(e);
    e = NULL;
}

void adiciona_robo(Exercito *e, INSTR *p) {
    if (e->size + 1 > MAX_ROBO) {
        Erro("Aviso: Não é possível adicionar mais robôs ao exército.");
        return;
    }
    short int dx[] = {1, 0, 1, -1, 0, -1};
    short int dy[] = {0, 1, -1, 0, -1, 1};

    int i = 0;
    while (i < MAX_ROBO) {
        if (!e->robos[i]) break;
        i++;
    }
    e->robos[i] = cria_robo(p, e->b.x + dx[i], e->b.y + dy[i]);
    e->robos[i]->e = e;
    e->robos[i]->id = i;
    e->size++;
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
