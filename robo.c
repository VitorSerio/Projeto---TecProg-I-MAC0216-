#include <stdio.h>
#include <stdlib.h>
#include "robo.h"

static void Erro(char *msg) {
    fprintf(stderr,"%s\n", msg);
}

static void Fatal(char *msg, int cod) {
    Erro(msg);
    exit(cod);
}

Robo *cria_robo(INSTR *p, short int e, int x, int y) {
    Robo *r = (Robo*)malloc(sizeof(Robo));
    if (!r) Fatal("Memória insuficiente para Robo",4);
    r->m = cria_maquina(p);
    r->x = x;
    r->y = y;
    r->c = 0;
    r->e = e;
    return r;
}

void destroi_robo(Robo *r) {
    destroi_maquina(r->m);
    free(r);
}

void troca_prog(Robo *r, INSTR *p) {
    destroi_maquina(r->m);
    r->m = cria_maquina(p);
    r->m->pil.topo = 0;
    r->m->exec.topo = 0;
}

void roda_robo(Robo *r, int n) {
    exec_maquina(r->m, n);
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
//     INSTR fac8[] = {
//         {PUSH, {.t = NUM, .val.n = 8}},
//         {CALL, {.t = NUM, .val.n = 4}},
//         {PRN, {.t = NUM, .val.n = 0}},
//         {END, {.t = NUM, .val.n = 0}},
//         {ALC, {.t = NUM, .val.n = 1}},
//         {DUP, {.t = NUM, .val.n = 0}},
//         {STL, {.t = NUM, .val.n = 0}},
//         {PUSH, {.t = NUM, .val.n = 1}},
//         {EQ, {.t = NUM, .val.n = 0}},
//         {JIF, {.t = NUM, .val.n = 13}},
//         {PUSH, {.t = NUM, .val.n = 1}},
//         {FRE, {.t = NUM, .val.n = 1}},
//         {RET, {.t = NUM, .val.n = 0}},
//         {RCE, {.t = NUM, .val.n = 0}},
//         {PUSH, {.t = NUM, .val.n = 1}},
//         {SUB, {.t = NUM, .val.n = 0}},
//         {CALL, {.t = NUM, .val.n = 4}},
//         {RCE, {.t = NUM, .val.n = 0}},
//         {MUL, {.t = NUM, .val.n = 0}},
//         {FRE, {.t = NUM, .val.n = 1}},
//         {RET, {.t = NUM, .val.n = 0}},
//     };
//
//     Robo *r = cria_robo(fac8, 0, 0, 0);
//     if (r) printf("Robo criado\n");
//
//     printf("\nFibo:\n");
//     roda_robo(r, 200);
//
//     troca_prog(r, fibo);
//
//     printf("\nFac8:\n");
//     roda_robo(r, 100);
//
//     destroi_robo(r);
//     if (!r) printf("Robo destruído\n");
//
//     return 0;
// }
