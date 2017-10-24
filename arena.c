#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maq.h"
#include "robo.h"
#include "exercito.h"
#include "arena.h"

static void Erro(char *msg) {
    fprintf(stderr,"%s\n", msg);
}

static void Fatal(char *msg, int cod) {
    Erro(msg);
    exit(cod);
}

Arena *cria_arena(int tam) {
    if (tam > MAX_TAMANHO) {
        Erro("Aviso: Tamanho passado para a arena é maior que o limite.");
        Erro("Arena criada terá o tamanho limite.");
        tam = MAX_TAMANHO;
    }
    else if (!(tam % 2)) {
        Erro("Aviso: Tamanho passado para a arena é par e deveria ser ímpar.");
        Erro("Arena criada terá tamanho igual ao tamanho dado - 1.");
        tam--;
    }

    Arena *a = (Arena*)malloc(sizeof(Arena));
    if (!a) Fatal("Memória insuficiente para Arena", 4);

    a->exercitosCount = 0;
    a->tamanho = tam;
    a->execucoes = 0;

    a->exercitos = (Exercito**)malloc(MAX_EXERCITOS * sizeof(Exercito*));
    if (!a->exercitos) Fatal("Erro: Memória insuficiente para múltiplos Exercito*", 4);
    for (int i = 0; i < MAX_EXERCITOS; i++)
        a->exercitos[i] = NULL;

    a->mapa = (Celula***)malloc(tam * sizeof(Celula**));
    if (!a->mapa) Fatal("Erro: Memória insuficiente para múltiplas Celula**.", 4);

    for(int i = 0; i < tam; i++) {
        a->mapa[i] = (Celula**)malloc(tam * sizeof(Celula*));
        if (!a->mapa[i]) Fatal("Erro: Memória insuficiente para  múltiplas Celula*.", 4);
        for(int j = 0; j < tam; j++) {
            int ht = tam / 2;
            int sum = i + j;
            // Deixa algumas células vazias, para simular um grid hexagonal
            if (sum < ht) a->mapa[i][j] = NULL;
            else if (sum >= tam + ht) a->mapa[i][j] = NULL;
            else {
                int tr = rand() % 4;
                short int cr = rand() % (MAX_CRYSTAL + 1);
                a->mapa[i][j] = cria_celula(tr, cr);
            }
        }
    }

    return a;
}

Arena *cria_arena_file(FILE *fp) {
    int tam;
    fscanf(fp, "%d\n", &tam);
    if (tam > MAX_TAMANHO) {
        Erro("Aviso: Tamanho passado para a arena é maior que o limite.");
        Erro("Arena criada terá o tamanho limite.");
        tam = MAX_TAMANHO;
    }
    else if (!(tam % 2)) {
        Erro("Aviso: Tamanho passado para a arena é par e deveria ser ímpar.");
        Erro("Arena criada terá tamanho igual ao tamanho dado - 1.");
        tam--;
    }


    Arena *a = (Arena*)malloc(sizeof(Arena));


    a->tamanho = tam;
    a->execucoes = 0;
    a->exercitosCount = 0;

    a->exercitos = (Exercito**)malloc(MAX_EXERCITOS * sizeof(Exercito*));
    if (!a->exercitos) Fatal("Erro: Memória insuficiente para exércitos.", 4);
    for (int i = 0; i < MAX_EXERCITOS; i++)
        a->exercitos[i] = NULL;

    a->mapa = (Celula***)malloc(tam * sizeof(Celula**));
    if (!a->mapa) Fatal("Erro: Memória insuficiente para mapa.", 4);

    for(int i = 0; i < a->tamanho; i++) {
        a->mapa[i] = (Celula**)malloc(tam * sizeof(Celula*));
        if (!a->mapa[i]) Fatal("Erro: Memória insuficiente para linha do mapa.", 4);
        for(int j = 0; j < a->tamanho; j++) {
            int ht = tam / 2;
            int sum = i + j;
            // Deixa algumas células vazias, para simular um grid hexagonal
            if (sum < ht) a->mapa[i][j] = NULL;
            else if (sum >= tam + ht) a->mapa[i][j] = NULL;
            else {
                int t, c;
                fscanf(fp, "%d,%d\n", &t, &c);
                a->mapa[i][j] = cria_celula(t, c);
            }
        }
    }

    fclose(fp);
}

void destroi_arena(Arena *a) {
    for (int i = 0; i < a->tamanho; i++) {
        for (int j = 0; j < a->tamanho; j++)
            destroi_celula(a->mapa[i][j]);
        free(a->mapa[i]);
        a->mapa[i] = NULL;
    }
    free(a->mapa);
    a->mapa = NULL;

    for (int i = 0; i < MAX_EXERCITOS; i++)
        destroi_exercito(a->exercitos[i]);
    free(a->exercitos);
    a->exercitos = NULL;

    free(a);
    a = NULL;
}

void Atualiza(Arena *a) {
    for(int i = 0; i < MAX_EXERCITOS; i++) {
        Exercito *e = a->exercitos[i];
        if (e)
            for(int j = 0; j < MAX_ROBO; j++) {
                Robo *r = e->robos[j];
                if (r) {
                    roda_robo(r, 50);
                    a->execucoes++;
                }
            }
    }
}

void InsereExercito(Arena *a, int x, int y) {
    if (a->exercitosCount + 1 > MAX_ROBO) {
        Erro("Aviso: Não é possível adicionar mais exércitos à arena.");
        return;
    }
    int i = 0;
    while (i < MAX_EXERCITOS) {
        if (!a->exercitos[i]) break;
        i++;
    }
    a->exercitos[i] = cria_exercito(x, y);
    a->exercitos[i]->id = i;
    a->exercitos[i]->b.e = i;
    a->exercitos[i]->a = a;
    a->exercitosCount++;

    a->mapa[x][y] = cria_celula(BASE, 0);
}

void RemoveExercito(Arena *a, int pos){
    Exercito *e = a->exercitos[pos];
    if (!e) {
        Erro("Aviso: Não há robôs na posição dada.");
        return;
    }
    int x = e->b.x;
    int y = e->b.y;
    a->mapa[x][y] = cria_celula(ESTRADA, MAX_CRYSTAL);

    destroi_exercito(e);
    e = NULL;
    a->exercitosCount--;
}

OPERANDO Sistema(Maquina *m, OPERANDO op) {
    Acao ac = op.val.ac;
    Robo *r = m->r;
    Arena *a = m->r->e->a;
    switch (ac.t) {
        Celula cel;
        int dx;
        int dy;
        switch (ac.d) {
            case A1:
                dx = 1;
                dy = 0;
                break;
            case A2:
                dx = 0;
                dy = 1;
                break;
            case A3:
                dx = 1;
                dy = -1;
                break;
            case A1_:
                dx = -1;
                dy = 0;
                break;
            case A2_:
                dx = 0;
                dy = -1;
                break;
            case A3_:
                dx = -1;
                dy = 1;
                break;
        }
        case MOV:
            r->x += dx;
            r->y += dy;
            break;
        case ATK:
            break;
        case GET:
            cel = *a->mapa[r->x + dx][r->y + dy];
            return (OPERANDO) {.t = CELULA, .val.cel = cel};
            break;
        case PEG:
            a->mapa[r->x + dx][r->y + dy]->c--;
            r->c++;
            break;
        case DEP:
            a->mapa[r->x + dx][r->y + dy]->c++;
            r->c--;
            break;
    }
    return op;
}

void imprime_mapa(Arena *a) {
    int n = a->tamanho;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!a->mapa[i][j]) printf("NULL  ");
            else printf("%d,%d,%d ", a->mapa[i][j]->t, a->mapa[i][j]->c,
                        a->mapa[i][j]->oc);
        }
        printf("\n");
    }
}
