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

static Celula *createCell(Terreno tr, short int cr, short int oc) {
    Celula *cel = (Celula*)malloc(sizeof(Celula));
    cel->terreno = tr;
    cel->cristais = cr;
    cel->ocupado = oc;
    return cel;
}

Arena *cria_arena(int tamanho) {
    Arena *arena = (Arena*)malloc(sizeof(Arena));

    arena->exercitosCount = 0;
    arena->tamanho = tamanho;
    arena->execucoes = 0;
    arena->exercitos = (Exercito**)malloc(MAX_EXERCITOS * sizeof(Exercito));

    for (int i = 0; i < MAX_EXERCITOS; i++)
        arena->exercitos[i] = NULL;

    for(int i = 0; i < tamanho; i++) {
        for(int j = 0; j < tamanho; j++) {
            int ht = tamanho / 2;
            int sum = i + j;
            // Deixa algumas células vazias, para simular um grid hexagonal
            if (sum < ht) arena->mapa[i][j] = NULL;
            else if (sum >= tamanho + ht) arena->mapa[i][j] = NULL;
            else {
                int tr = rand() % 4;
                short int cr = rand() % (MAX_CRYSTAL + 1);
                arena->mapa[i][j] = createCell(tr, cr, 0);
            }
        }
    }

    return arena;
}

Arena *cria_arena_file(FILE *fp) {
    Arena *arena = (Arena*)malloc(sizeof(Arena));

    fscanf(fp, "%d\n", &arena->tamanho);
    arena->execucoes = 0;
    arena->exercitosCount = 0;
    arena->exercitos = (Exercito**)malloc(MAX_EXERCITOS * sizeof(Exercito*));

    for (int i = 0; i < MAX_EXERCITOS; i++)
        arena->exercitos[i] = NULL;

    for(int i = 0; i < arena->tamanho; i++){
        for(int j = 0; j < arena->tamanho; j++){
            int cr, oc, tr;
            fscanf(fp, "%d,%d,%d\n", &cr, &oc, &tr);
            arena->mapa[i][j] = createCell(tr, cr, oc);
        }
    }

    fclose(fp);
}

void Atualiza(Arena *arena) {
    for(int i = 0; i < MAX_EXERCITOS; i++) {
        Exercito *e = arena->exercitos[i];
        if (e)
            for(int j = 0; j < MAXVM; j++) {
                Robo *r = e->robos[j];
                if (r) roda_robo(r, 50);
                arena->execucoes++;
            }
    }
}

void InsereExercito(Arena *arena, INSTR **progs, int n, int x, int y) {
    if (arena->exercitosCount + 1 > MAXVM) {
        Erro("Aviso: Não é possível adicionar mais exércitos à arena.");
        return;
    }
    int i = 0;
    while (i < MAX_EXERCITOS) {
        if (!arena->exercitos[i]) break;
        i++;
    }
    arena->exercitos[i] = cria_exercito(progs, n, i, x, y);
    arena->exercitos[i]->a = arena;
    arena->exercitosCount++;
}

void RemoveExercito(Arena *arena, int pos){
    if (!arena->exercitos[pos]) {
        Erro("Aviso: Não há robôs na posição dada.");
        return;
    }
    destroi_exercito(arena->exercitos[pos]);
    arena->exercitos[pos] = NULL;
    arena->exercitosCount--;
}

OPERANDO Sistema(Maquina *m, OPERANDO op) {
    Acao ac = op.val.ac;
    Robo *r = m->r;
    //Arena *a = m->r->e->a;
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
            //cel = *a->mapa[r->x + dx][r->y + dy];
            //return (OPERANDO) {.t = CELULA, .val.cel = cel};
            break;
        case PEG:
            //a->mapa[r->x + dx][r->y + dy]->cristais--;
            //r->c++;
            break;
        case DEP:
            //a->mapa[r->x + dx][r->y + dy]->cristais++;
            //r->c--;
            break;
    }
    return op;
}
