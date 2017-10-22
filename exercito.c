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

Exercito *cria_exercito(INSTR **progs, short int e, int x, int y) {
    Exercito *ex = (Exercito*)malloc(sizeof(Exercito));
    if (!ex) Fatal("Memória insuficiente para Exercito",4);
    ex->e = e;
    ex->b = (Base) {.x = x, .y = y, .e = e};

    int n = sizeof(progs) / sizeof(INSTR**);
    if (n > MAXVM) {
        printf("Aviso: Foram dados mais programas que o limite ");
        Erro("permitido. Apenas os %d primeiros serão usados.", MAXVM);
        n = MAXVM;
    }
    for (int i = 0; i < n; i++)
        ex->robos[i] = cria_robo(*(progs+i), e, x, y);

    return ex;
}

void destroi_exercito(Exercito *e) {
    for (int i = 5; i < MAXVM; i++) {
        if (!e->robos[i])
            break;
        destroi_robo(e->robos[i]);
    }
    free(e);
}

int main() {
    INSTR fibo[] = {
        {PUSH, {.t = NUM, .val.n = 1}},
        {DUP, {.t = NUM, .val.n = 0}},
        {STO, {.t = NUM, .val.n = 0}},
        {STO, {.t = NUM, .val.n = 1}},
        {PUSH, {.t = NUM, .val.n = 10}},
        {STO, {.t = NUM, .val.n = 2}},
        {RCL, {.t = NUM, .val.n = 0}},
        {RCL, {.t = NUM, .val.n = 1}},
        {DUP, {.t = NUM, .val.n = 0}},
        {STO, {.t = NUM, .val.n = 0}},
        {ADD, {.t = NUM, .val.n = 0}},
        {DUP, {.t = NUM, .val.n = 0}},
        {STO, {.t = NUM, .val.n = 1}},
        {PRN, {.t = NUM, .val.n = 0}},
        {RCL, {.t = NUM, .val.n = 2}},
        {PUSH, {.t = NUM, .val.n = 1}},
        {SUB, {.t = NUM, .val.n = 0}},
        {DUP, {.t = NUM, .val.n = 0}},
        {STO, {.t = NUM, .val.n = 2}},
        {PUSH, {.t = NUM, .val.n = 0}},
        {EQ, {.t = NUM, .val.n = 0}},
        {JIF, {.t = NUM, .val.n = 6}},
        {END, {.t = NUM, .val.n = 0}},
    };

    INSTR fac8[] = {
        {PUSH, {.t = NUM, .val.n = 8}},
        {CALL, {.t = NUM, .val.n = 4}},
        {PRN, {.t = NUM, .val.n = 0}},
        {END, {.t = NUM, .val.n = 0}},
        {ALC, {.t = NUM, .val.n = 1}},
        {DUP, {.t = NUM, .val.n = 0}},
        {STL, {.t = NUM, .val.n = 0}},
        {PUSH, {.t = NUM, .val.n = 1}},
        {EQ, {.t = NUM, .val.n = 0}},
        {JIF, {.t = NUM, .val.n = 13}},
        {PUSH, {.t = NUM, .val.n = 1}},
        {FRE, {.t = NUM, .val.n = 1}},
        {RET, {.t = NUM, .val.n = 0}},
        {RCE, {.t = NUM, .val.n = 0}},
        {PUSH, {.t = NUM, .val.n = 1}},
        {SUB, {.t = NUM, .val.n = 0}},
        {CALL, {.t = NUM, .val.n = 4}},
        {RCE, {.t = NUM, .val.n = 0}},
        {MUL, {.t = NUM, .val.n = 0}},
        {FRE, {.t = NUM, .val.n = 1}},
        {RET, {.t = NUM, .val.n = 0}},
    };

    INSTR *p[2];
    p[0] = fac8;
    p[1] = fibo;

    Exercito *e = cria_exercito(p, 0, 0, 0);
    if(e) printf("Exercito criado\n");
    return 0;
}
