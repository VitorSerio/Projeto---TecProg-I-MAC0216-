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

void adiciona_robo(Exercito *e, INSTR *p) {
    if (e->size + 1 > MAXVM) {
        Erro("Aviso: Não é possível adicionar mais robôs ao exército.");
        return;
    }
    short int dx[] = {1, 0, 1, -1, 0, -1};
    short int dy[] = {0, 1, -1, 0, -1, 1};

    int i = 0;
    while (i < MAXVM) {
        if (e->robos[i] == NULL)
            break;
        i++;
    }

    e->robos[i] = cria_robo(p, e->e, e->b.x + dx[i], e->b.y + dy[i]);
    e->size++;
}

void remove_robo(Exercito *e, int pos) {
    if (e->robos[pos] == NULL) {
        Erro("Aviso: Não há robôs na posição dada.");
        return;
    }
    destroi_robo(e->robos[pos]);
    e->robos[pos] = NULL;
    e->size--;
}

Exercito *cria_exercito(INSTR *progs[], short int n, short int e, int x,
                        int y) {
    Exercito *ex = (Exercito*)malloc(sizeof(Exercito));
    if (!ex) Fatal("Erro: Memória insuficiente para Exercito",4);
    ex->e = e;
    ex->b = (Base) {.x = x, .y = y, .e = e};

    if (n > MAXVM) {
        Erro("Aviso: Foram dados mais programas que o limite permitido. Apenas os primeiros serão usados.");
        n = MAXVM;
    }

    for (int i = 0; i < MAXVM; i++) ex->robos[i] = NULL;

    for (int i = 0; i < n; i++) adiciona_robo(ex, progs[i]);

    return ex;
}

void destroi_exercito(Exercito *e) {
    while (--e->size < 0) {
        short int i = e->size;
        if (!e->robos[i])
            break;
        destroi_robo(e->robos[i]);
    }
    free(e);
}

// int main() {
//     INSTR fibo[] = {
//         {PUSH, {.t = NUM, .val.n = 1}},
//         {DUP, {.t = NUM, .val.n = 0}},
//         {STO, {.t = NUM, .val.n = 0}},
//         {STO, {.t = NUM, .val.n = 1}},
//         {PUSH, {.t = NUM, .val.n = 10}},
//         {STO, {.t = NUM, .val.n = 2}},
//         {RCL, {.t = NUM, .val.n = 0}},
//         {RCL, {.t = NUM, .val.n = 1}},
//         {DUP, {.t = NUM, .val.n = 0}},
//         {STO, {.t = NUM, .val.n = 0}},
//         {ADD, {.t = NUM, .val.n = 0}},
//         {DUP, {.t = NUM, .val.n = 0}},
//         {STO, {.t = NUM, .val.n = 1}},
//         {PRN, {.t = NUM, .val.n = 0}},
//         {RCL, {.t = NUM, .val.n = 2}},
//         {PUSH, {.t = NUM, .val.n = 1}},
//         {SUB, {.t = NUM, .val.n = 0}},
//         {DUP, {.t = NUM, .val.n = 0}},
//         {STO, {.t = NUM, .val.n = 2}},
//         {PUSH, {.t = NUM, .val.n = 0}},
//         {EQ, {.t = NUM, .val.n = 0}},
//         {JIF, {.t = NUM, .val.n = 6}},
//         {END, {.t = NUM, .val.n = 0}},
//     };
//
//     INSTR *p[2];
//
//     p[0] = &fibo;
//     p[1] = &fibo;
//
//     Exercito *e = cria_exercito(p, 2, 0, 0, 0);
//     if(e) printf("Exercito criado\n");
//     printf("Robo1\n");
//     roda_robo(e->robos[0], 50);
//     printf("Robo2\n");
//     roda_robo(e->robos[1], 50);
//
//     remove_robo(e, 3);
//     printf("size = %d\n", e->size);
//
//     adiciona_robo(e, p[0]);
//     printf("Robo3\n");
//     roda_robo(e->robos[2], 50);
//     adiciona_robo(e, p[0]);
//     printf("Robo4\n");
//     roda_robo(e->robos[3], 50);
//     adiciona_robo(e, p[0]);
//     printf("Robo5\n");
//     roda_robo(e->robos[4], 50);
//     adiciona_robo(e, p[0]);
//     printf("Robo6\n");
//     roda_robo(e->robos[5], 50);
//     adiciona_robo(e, p[0]);
//     printf("\nsize = %d\n", e->size);
//
//     remove_robo(e, 3);
//     printf("\nsize = %d\n", e->size);
//     printf("robo[3] == NULL = %d\n", e->robos[3] == NULL);
//     adiciona_robo(e, p[0]);
//     printf("size = %d\n", e->size);
//
//     destroi_exercito(e);
//
//     INSTR *p2[7];
//
//     p2[0] = &fibo;
//     p2[1] = &fibo;
//     p2[2] = &fibo;
//     p2[3] = &fibo;
//     p2[4] = &fibo;
//     p2[5] = &fibo;
//     p2[6] = &fibo;
//
//     e = cria_exercito(p2, 7, 0, 0, 0);
//     printf("\n%d\n", e->size);
//
//     return 0;
// }
