#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

#define exCount (a->exercitosCount)
#define atamanho (a->tamanho)
#define execs (a->execucoes)
#define mapa (a->mapa)
#define exercitos (a->exercitos)

static Arena *inicializa_arena(int tam) {

    if (tam > MAX_TAMANHO) {
        Erro("Aviso: Tamanho passado para a arena é maior que o limite.");
        printf("Por favor, entre com outro valor para o tamanho do mapa, que");
        printf("seja menor que %d:\n", MAX_TAMANHO);
        scanf("%d\n", &tam);
    }
    if (!(tam % 2)) {
        Erro("Aviso: Tamanho passado para a arena é par e deveria ser ímpar.");
        printf("Por favor, entre com outro valor para o tamanho do mapa, que");
        printf("seja ímpar:\n");
        scanf("%d\n", &tam);
    }

    Arena *a = (Arena*) malloc(sizeof(Arena));
    if (!a) Fatal("Erro: Memória insuficiente para Arena.", 4);

    exCount = 0;
    atamanho = tam;
    execs = 0;

    exercitos = (Exercito**)malloc(MAX_EXERCITOS * sizeof(Exercito*));
    if (!exercitos) Fatal("Erro: Memória insuficiente para múltiplos Exercito*", 4);
    for (int i = 0; i < MAX_EXERCITOS; i++) exercitos[i] = NULL;

    mapa = (Celula***)malloc(tam * sizeof(Celula**));
    if (!mapa) Fatal("Erro: Memória insuficiente para múltiplas Celula**.", 4);

    return a;
}

Arena *cria_arena(int tam) {

    Arena *a = inicializa_arena(tam);

    for(int i = 0; i < tam; i++) {

        mapa[i] = (Celula**)malloc(tam * sizeof(Celula*));
        if (!mapa[i]) Fatal("Erro: Memória insuficiente para múltiplas Celula*.", 4);

        for(int j = 0; j < tam; j++) {

            int ht = tam / 2;
            int sum = i + j;
            // Deixa algumas células vazias, para simular um grid hexagonal
            if (sum < ht) mapa[i][j] = NULL;
            else if (sum >= tam + ht) mapa[i][j] = NULL;
            else {

                int tr = rand() % 4;
                short int cr = rand() % (MAX_CRYSTAL + 1);
                mapa[i][j] = cria_celula(tr, cr);
            }
        }
    }

    return a;
}

Arena *cria_arena_file(FILE *fp) {

    int tam;
    fscanf(fp, "%d\n", &tam);
    Arena *a = inicializa_arena(tam);

    for(int i = 0; i < atamanho; i++) {

        mapa[i] = (Celula**)malloc(tam * sizeof(Celula*));
        if (!mapa[i]) Fatal("Erro: Memória insuficiente para múltiplas Celula*.", 4);
        for(int j = 0; j < atamanho; j++) {

            int ht = atamanho / 2;
            int sum = i + j;
            // Deixa algumas células vazias, para simular um grid hexagonal
            if (sum < ht) mapa[i][j] = NULL;
            else if (sum >= atamanho + ht) mapa[i][j] = NULL;
            else {
                int t, c;
                fscanf(fp, "%d,%d\n", &t, &c);
                mapa[i][j] = cria_celula(t, c);
            }
        }
    }

    fclose(fp);
}

void destroi_arena(Arena *a) {

    for (int i = 0; i < atamanho; i++) {
        for (int j = 0; j < atamanho; j++)
            if (mapa[i][j]) destroi_celula(mapa[i][j]);
        free(mapa[i]);
        mapa[i] = NULL;
    }
    free(mapa);
    mapa = NULL;

    for (int i = 0; i < MAX_EXERCITOS; i++)
        if (exercitos[i]) destroi_exercito(exercitos[i]);
    free(exercitos);
    exercitos = NULL;

    free(a);
    a = NULL;
}

void Atualiza(Arena *a, int instrucoes) {

    for(int i = 0; i < MAX_EXERCITOS; i++) {

        Exercito *e = exercitos[i];
        if (e)
            for(int j = 0; j < MAX_ROBO; j++) {
                Robo *r = e->robos[j];
                if (r) {
                    roda_robo(r, instrucoes);
                    execs++;
                }
            }
    }
}

void InsereExercito(Arena *a, short int pos, short int tam) {

    if (exercitos[pos]) {

        Erro("Aviso: Já existe um exército na posição dada.");
        char res[2];
        printf("Deseja substituir o exército ativo na posição %d? (S/N)\n",
                pos);
        scanf("%s", res);

        if (strcmp(res, "S")) {

            printf("Deseja tentar criar um exército em outra posição? (S/N)\n");
            scanf("%s", res);

            if (strcmp(res, "S")) return;

            printf("Qual posição? (de 0 a %d)\n", MAX_EXERCITOS-1);
            scanf("%hd", &pos);

            InsereExercito(a, pos, tam);
            return;
        }
        RemoveExercito(a, pos);
    }

    Vetor bases[] = {
        {1, atamanho / 2}, {1, atamanho - 2},
        {atamanho / 2, 1}, {atamanho / 2, atamanho - 2},
        {atamanho - 2, 1}, {atamanho - 2, atamanho / 2}
    };

    exercitos[pos] = cria_exercito(bases[pos], tam);
    exercitos[pos]->b.e = pos;
    exercitos[pos]->a = a;
    exCount++;

    for (short int i = 0; i < tam; i++) {
        adiciona_robo(exercitos[pos], i, NULL);
        Vetor rpos = exercitos[pos]->robos[i]->pos;
        mapa[rpos.x][rpos.y]->r = exercitos[pos]->robos[i];
    }

    mapa[bases[pos].x][bases[pos].y] = cria_celula(BASE, 0);
    mapa[bases[pos].x][bases[pos].y]->b = &exercitos[pos]->b;

}

void RemoveExercito(Arena *a, short int pos){

    if (!&exercitos[pos]) {

        Erro("Aviso: Não há exército na posição dada.");
        printf("Deseja tentar remover outro exército? (S/N)\n");
        char res[2];
        scanf("%s", res);

        if (strcmp(res, "S")) return;

        printf("Qual exército deverá ser removido? (de 0 a %d)\n",
                MAX_EXERCITOS-1);
        scanf("%hd", &pos);

        RemoveExercito(a, pos);
        return;
    }
    Vetor base = exercitos[pos]->b.pos;

    mapa[base.x][base.x] = cria_celula(ESTRADA, MAX_CRYSTAL);
    mapa[base.x][base.y]->b = NULL;

    short int tam = exercitos[pos]->tamanho;
    for (short int i = 0; i < tam; i++) {
        Vetor rpos = exercitos[pos]->robos[i]->pos;
        mapa[rpos.x][rpos.y]->r = NULL;
    }

    destroi_exercito(exercitos[pos]);
    exCount--;
}

void RemoveRobo(Robo *r) {

    Exercito *e = r->e;
    Arena *a = e->a;

    short int rid = r->id;
    Vetor rpos = r->pos;

    destroi_robo(e->robos[rid]);

    mapa[rpos.x][rpos.y]->r = NULL;
}

OPERANDO Sistema(Maquina *m, OPERANDO op) {

    Acao ac = op.val.ac;
    Robo *r = m->r;
    Arena *a = m->r->e->a;

    Vetor d[] = {{-1, 1}, {0, -1}, {-1, 0}, {1, 0}, {0, 1}, {1, -1}};

    int i = (int) ac.d;
    i += (i > 0) ? 2 : 3;

    Vetor res = soma_vet(r->pos, d[i]);
    Vetor rpos = r->pos;

    switch (ac.t) {
        Celula *cel;
        case MOV:
            if (mapa[res.x][res.y]->r || mapa[res.x][res.y]->b) break;
            mapa[rpos.x][rpos.y]->r = NULL;
            r->pos = res;
            mapa[res.x][res.y]->r = r;
            break;
        case ATK:
            if (!mapa[res.x][res.y]->r) break;
            mapa[res.x][res.y]->r->hp--;
            if (!mapa[res.x][res.y]->r->hp)
                RemoveRobo(mapa[res.x][res.y]->r);
            break;
        case INF:
            cel = mapa[res.x][res.y];
            return (OPERANDO) {.t = CELULA, .val.cel = *cel};
            break;
        case PEG:
            if (!mapa[res.x][res.y]->c) break;
            mapa[res.x][res.y]->c--;
            r->c++;
            break;
        case DEP:
            if (!mapa[res.x][res.y]->b) break;
            mapa[res.x][res.y]->b->hp--;
            if (!mapa[res.x][res.y]->b->hp)
                RemoveExercito(a, mapa[res.x][res.y]->b->e);
            r->c--;
            break;
    }
    return op;
}

void imprime_mapa(Arena *a) {
    for (int i = 0; i < atamanho; i++) {
        for (int j = 0; j < atamanho; j++) {
            if (!&mapa[i][j]) printf("{NULL} ");
            else printf("%s ", toString_celula(mapa[i][j]));
        }
        printf("\n");
    }
}
