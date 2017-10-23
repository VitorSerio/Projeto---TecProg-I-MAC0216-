#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arena.h"
#include "maq.h"

////////////////////////////////////////////////////////////////////////////////
// FUNÇÕES AUXILIARES

static INSTR **cria_prog_array(INSTR *p, short int n) {
    INSTR **progs = (INSTR**)malloc(n*sizeof(INSTR*));
    for (int i = 0; i < n; i++)
        progs[i] = p;
    return progs;
}

static void roda_robos(Exercito *e, int vezes, short int n) {
    for (int i = 0; i < n; i++) {
        printf("Rodando robo %d:\n", i+1);
        roda_robo(e->robos[i], vezes);
    }
}

static void adiciona_robos(Exercito *e, INSTR *p, short int n) {
    for (int i = 0; i < n; i++) {
        printf("Adicionando robo %d:\n", i);
        adiciona_robo(e->robos[i], p);
        printf("Tamanho do exército = %d\n", e->size);
    }
}

////////////////////////////////////////////////////////////////////////////////
// TESTA ARENA

static void testa_arena(){
    return;
}

////////////////////////////////////////////////////////////////////////////////
// TESTA EXERCITO

static void testa_exercito() {
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

    int exec = 50;
    int pos = 3;
    short int n = 2;
    INSTR **p = cria_prog_array(&fibo, n);

    printf("Criando exército:\n");
    Exercito *e = cria_exercito(p, n, 0, 0, 0);
    printf("Exercito criado!\n");
    printf("Tamanho do exército = %d\n", e->size);
    printf("Rodando robôs:\n");
    roda_robos(e, exec, n);
    printf("Robôs funcionando!\n");
    if (e->size == n) {
        printf("Exercito *cria_exercito(INSTR *progs[], short int n, short ");
        printf("int e, int x, int y) está OK!\n");
    }
    else {
        printf("Exercito *cria_exercito(INSTR *progs[], short int n, short ");
        printf("int e, int x, int y) está ERRADA!\n");
        return;
    }

    printf("\nRemovendo um robô inexistente:\n");
    remove_robo(e, pos);
    printf("Tamanho do exército = %d\n", e->size);
    if (e->size == n && !e->robos[pos]) {
        printf("Gerenciamento de erro de void remove_robo(Exercito *e, int ");
        printf("pos) está OK!\n");
    }
    else {
        printf("Gerenciamento de erro de void remove_robo(Exercito *e, int ");
        printf("pos) está ERRADO!\n");
        return;
    }

    n = MAXVM - n + 1;
    printf("\nAdicionando mais robôs (com um excedente):\n");
    adiciona_robos(e, &fibo, n);
    printf("Tamanho do exército = %d\n", e->size);
    if (e->size == MAXVM) {
        printf("Gerenciamento de erro de void adiciona_robo(Exercito *e, ");
        printf("INSTR *p) está OK!\n");
    }
    else {
        printf("Gerenciamento de erro de void adiciona_robo(Exercito *e, ");
        printf("INSTR *p) está ERRADO!\n");
        return;
    }

    n = MAXVM;
    printf("\nTestando robôs novos:\n");
    roda_robos(e, exec, n);
    printf("Adições em ordem de void adiciona_robo(Exercito *e, INSTR *p) ");
    printf("está OK!\n");

    printf("\nRemovendo um robô existente:\n");
    remove_robo(e, pos);
    printf("Tamanho do exército = %d\n", e->size);
    if (e->size == MAXVM - 1 && !e->robos[pos])
        printf("void remove_robo(Exercito *e, int pos) está OK!\n");
    else {
        printf("void remove_robo(Exercito *e, int pos) está ERRADA!\n");
        return;
    }

    printf("\nAdicionando um robô no espaço vazio:\n");
    adiciona_robo(e, &fibo);
    printf("Tamanho do exército = %d\n", e->size);
    if (e->size == MAXVM)
        printf("void adiciona_robo(Exercito *e, INSTR *p) está OK!\n");
    else {
        printf("void adiciona_robo(Exercito *e, INSTR *p) está ERRADA!\n");
        return;
    }

    printf("\nDestruindo exército:\n");
    destroi_exercito(e);
    if (!e) printf("void destroi_exercito(Exercito *e) está OK!\n");
    else printf("void destroi_exercito(Exercito *e) está ERRADA!\n");

    n = 7;
    p = cria_prog_array(&fibo, n);

    e = cria_exercito(p, n, 0, 0, 0);
    printf("\n%d\n", e->size);
}

////////////////////////////////////////////////////////////////////////////////
// TESTA ROBÔ

static void testa_robo() {
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

    // Testando cria_robo
    printf("Criando robô:\n");
    Robo *r = cria_robo(fac8, 0, 0);
    printf("Robo criado!\n");
    printf("Robo *cria_robo(INSTR *p, short int e, int x, int y) está OK!\n");

    // Testando roda_robo
    printf("\nRodando programa inicial:\n");
    roda_robo(r, 200);
    printf("void roda_robo(Robo *r, int n) está OK!\n");

    // Testando troca_prog
    printf("\nTrocando os programas:\n");
    troca_prog(r, fibo);
    printf("Programa trocado!\n");
    printf("Rodando programa novo:\n");
    roda_robo(r, 100);
    printf("Programa novo funcionando!\n");
    printf("void troca_prog(Robo *r, INSTR *p) está OK!\n");

    // Testando destroi_robo
    printf("\nDestruindo robô:\n");
    destroi_robo(r);
    if (!r) printf("void destroi_robo(Robo *r) está OK!\n");
    else printf("void destroi_robo(Robo *r) está ERRADA!\n");
}

////////////////////////////////////////////////////////////////////////////////
// TESTA OPERANDO

static void testa_operando() {
    OPERANDO op[] = {
        {.t = NUM, .val.n = 5},
        {.t = ACAO, .val.ac = {.t = MOV, .d = A1}},
        {.t = ACAO, .val.ac = {.t = ATK, .d = A2}},
        {.t = ACAO, .val.ac = {.t = GET, .d = A3}},
        {.t = ACAO, .val.ac = {.t = PEG, .d = A1_}},
        {.t = ACAO, .val.ac = {.t = DEP, .d = A2_}},
        {.t = ACAO, .val.ac = {.t = MOV, .d = A3_}},
        {.t = CELULA, .val.cel = {.terreno = ESTRADA, .cristais = 0, .ocupado = 0}},
        {.t = CELULA, .val.cel = {.terreno = GRAMA, .cristais = 3, .ocupado = 1}},
        {.t = CELULA, .val.cel = {.terreno = MONTANHA, .cristais = 8, .ocupado = 0}},
        {.t = CELULA, .val.cel = {.terreno = RIO, .cristais = 0, .ocupado = 0}},
        {.t = CELULA, .val.cel = {.terreno = BASE, .cristais = 5, .ocupado = 1}},
    };

    int n = sizeof(op) / sizeof(OPERANDO);
    for (int i = 0; i < n; i++) {
        char *str = toString(op[i]);
        printf("Operando %d: %s\n", i+1, str);
        free(str);
    }
    printf("\nchar *toString(OPERANDO op) está OK!\n");
}

////////////////////////////////////////////////////////////////////////////////
// MAIN

int main(int argc, char const *argv[]) {
    if (argc == 1 || !strcmp(argv[1], "-a")) {
        printf("Testando arena.c:\n\n");
        testa_arena();
        return 0;
    }
    else if (!strcmp(argv[1], "-e")) {
        printf("Testando exercito.c:\n\n");
        testa_exercito();
        return 0;
    }
    else if (!strcmp(argv[1], "-r")) {
        printf("Testando robo.c:\n\n");
        testa_robo();
        return 0;
    }
    else if (!strcmp(argv[1], "-o")) {
        printf("Testando operando.c:\n\n");
        testa_operando();
        return 0;
    }
    else {
        printf("%s não é uma opção válida.\n", argv[1]);
        printf("Use uma das opções abaixo:\n");
        printf("Nanhuma ou '-a' para testar as funções em arena.c\n");
        printf("'-e' para testar as funções em exercito.c\n");
        printf("'-r' para testar as funções em robo.c\n");
        printf("'-o' para testar as funções em operando.c\n");
    }
    return 0;
}
