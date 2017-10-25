#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

#define b (e->b)
#define size (e->size)
#define robos (e->robos)
#define eid (e->id)

Exercito *cria_exercito(Vetor bpos, short int id) {

    Exercito *e = (Exercito*)malloc(sizeof(Exercito));
    if (!e) Fatal("Erro: Memória insuficiente para Exercito", 4);

    b.pos.x = bpos.x;
    b.pos.y = bpos.y;

    eid = id;

    robos = (Robo**)malloc(MAX_ROBO * sizeof(Robo*));
    if (!robos) Fatal("Erro: Memória insuficiente para múltiplos Robo*", 4);
    for (int i = 0; i < MAX_ROBO; i++) robos[i] = NULL;

    return e;
}

void destroi_exercito(Exercito *e) {
    for (int i = 0; i < MAX_ROBO; i++) {
        if (!robos[i])
            continue;
        destroi_robo(robos[i]);
        size--;
    }
    free(robos);
    robos = NULL;
    free(e);
    e = NULL;
}

void adiciona_robo(Exercito *e, short int pos, INSTR *p) {

    if (robos[pos]) {

        Erro("Aviso: Já existe um robô na posição dada.");
        char res[2];
        printf("Deseja substituir o robô ativo na posição %d? (S/N)\n",
                pos);
        scanf("%s", res);

        if (strcmp(res, "S")) {

            printf("Deseja tentar criar um robô em outra posição? (S/N)\n");
            scanf("%s", res);

            if (strcmp(res, "S")) return;

            printf("Qual posição? (de 0 a %d)\n", MAX_ROBO-1);
            scanf("%hd", &pos);

            adiciona_robo(e, pos, p);
            return;
        }
        remove_robo(e, pos);
    }

    Vetor dpos[] = {{1, 0}, {0, 1}, {1, -1}, {-1, 0}, {0, -1}, {-1, 1}};

    robos[pos] = cria_robo(p, soma_vet(b.pos, dpos[pos]), pos);
    robos[pos]->e = e;
    robos[pos]->id = pos;
    size++;
}

void remove_robo(Exercito *e, short int pos) {
    if (!robos[pos]) {

        Erro("Aviso: Não há robô na posição dada.");
        printf("Deseja tentar remover outro robô? (S/N)\n");
        char res[2];
        scanf("%s", res);

        if (strcmp(res, "S")) return;

        printf("Qual robô deverá ser removido? (de 0 a %d)\n", MAX_ROBO-1);
        scanf("%hd", &pos);

        remove_robo(e, pos);
        return;
    }
    destroi_robo(robos[pos]);
    robos[pos] = NULL;
    size--;
}
