#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arena.h"

////////////////////////////////////////////////////////////////////////////////
// FUNÇÕES AUXILIARES

static void roda_robos(Exercito *e, int vezes, short int n) {
    for (int i = 0; i < n; i++) {
        printf("Rodando robo %d:\n", i+1);
        roda_robo(e->robos[i], vezes);
    }
}

static void adiciona_robos(Exercito *e, INSTR *p, short int n) {
    for (int i = 0; i < n; i++) {
        printf("Adicionando robo %d:\n", i+1);
        adiciona_robo(e, p);
        printf("Tamanho do exército = %d\n", e->size);
    }
}

////////////////////////////////////////////////////////////////////////////////
// TESTA ARENA

static void testa_arena(){
    // Testando erro tam > MAX_TAMANHO em cria_arena
    printf("Criando arena:\n");
    Arena *a = cria_arena(53);
    printf("Arena criada!\n");
    if (a->tamanho == MAX_TAMANHO) {
        printf("O gerenciamento de erro do tipo tamanho > MAX_TAMANHO em ");
        printf("Arena *a = cria_arena(int tam) está OK!\n");
    }
    else {
        printf("O gerenciamento de erro do tipo tamanho > MAX_TAMANHO em ");
        printf("Arena *a = cria_arena(int tam) está ERRADO!\n");
    }

    // Testando destroi_arena
    printf("\nDestruindo arena:\n");
    destroi_arena(a);
    printf("void destroi_exercito(Exercito *e) está OK!\n");

    // Testando erro tam par em cria_arena
    printf("Criando arena:\n");
    a = cria_arena(20);
    printf("Arena criada!\n");
    if (a->tamanho % 2) {
        printf("O gerenciamento de erro do tipo tamanho par em ");
        printf("Arena *a = cria_arena(int tam) está OK!\n");
    }
    else {
        printf("O gerenciamento de erro do tipo tamanho par em ");
        printf("Arena *a = cria_arena(int tam) está ERRADO!\n");
    }

    // Testando mapa de cria_arena
    printf("\nDestruindo arena:\n");
    destroi_arena(a);
    printf("Arena destruída!\n");
    printf("Criando nova arena e imprimindo mapa resultante:\n");
    a = cria_arena(9);
    imprime_mapa(a);
    printf("Arena *a = cria_arena(int tam) está OK!\n");
    printf("void imprime_mapa(Arena *a) está OK!\n");
}

////////////////////////////////////////////////////////////////////////////////
// TESTA EXERCITO

static void testa_exercito() {
    // Variáveis auxiliares
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
    short int n = 2;
    int pos = n+1;

    // Testando cria_exercito
    printf("Criando exército:\n");
    Exercito *e = cria_exercito(0, 0);
    printf("Exercito criado!\n");
    printf("Tamanho do exército = %d\n", e->size);
    printf("Exercito *cria_exercito(INSTR *progs[], short int n, short ");
    printf("int e, int x, int y) está OK!\n");

    // Testando adiciona_robo
    printf("\nAdicionando %d robôs:\n", n);
    adiciona_robos(e, fibo, n);
    printf("Rodando robôs:\n");
    roda_robos(e, exec, n);
    printf("Robôs funcionando!\n");
    if (e->size == n) {
        printf("Adições em ordem de void adiciona_robo(Exercito *e, INSTR *p)");
        printf(" está OK!\n");
    }
    else {
        printf("Adições em ordem de void adiciona_robo(Exercito *e, INSTR *p)");
        printf(" está ERRADA!\n");
        return;
    }

    // Testando erros em remove_robo
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

    // Testando adiciona_robos, com já havendo alguns robôs e erros
    n = MAX_ROBO - n + 1;
    printf("\nAdicionando mais robôs (com um excedente):\n");
    adiciona_robos(e, fibo, n);
    if (e->size == MAX_ROBO) {
        printf("Gerenciamento de erro de void adiciona_robo(Exercito *e, ");
        printf("INSTR *p) está OK!\n");
    }
    else {
        printf("Gerenciamento de erro de void adiciona_robo(Exercito *e, ");
        printf("INSTR *p) está ERRADO!\n");
        return;
    }

    // Testando se a adição funcionou de fato
    n = MAX_ROBO;
    printf("\nTestando robôs novos:\n");
    roda_robos(e, exec, n);
    printf("Adições em ordem de void adiciona_robo(Exercito *e, INSTR *p) ");
    printf("está OK!\n");

    // Testando remove_robo
    printf("\nRemovendo um robô existente:\n");
    remove_robo(e, pos);
    printf("Tamanho do exército = %d\n", e->size);
    if (e->size == MAX_ROBO - 1 && !e->robos[pos])
        printf("void remove_robo(Exercito *e, int pos) está OK!\n");
    else {
        printf("void remove_robo(Exercito *e, int pos) está ERRADA!\n");
        return;
    }

    // Testando adiciona_robo com um espaço vazio no meio
    printf("\nAdicionando um robô no espaço vazio:\n");
    adiciona_robo(e, fibo);
    printf("Tamanho do exército = %d\n", e->size);
    printf("\nTestando robô novo:\n");
    roda_robo(e->robos[pos], exec);
    if (e->size == MAX_ROBO)
        printf("void adiciona_robo(Exercito *e, INSTR *p) está OK!\n");
    else {
        printf("void adiciona_robo(Exercito *e, INSTR *p) está ERRADA!\n");
        return;
    }

    // Testando destroi_exercito
    printf("\nDestruindo exército:\n");
    destroi_exercito(e);
    printf("void destroi_exercito(Exercito *e) está OK!\n");
}

////////////////////////////////////////////////////////////////////////////////
// TESTA ROBÔ

static void testa_robo() {
    // Variáveis auxilires
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
    printf("Programa inicial funcionando!\n");
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
    printf("void destroi_robo(Robo *r) está OK!\n");
}

////////////////////////////////////////////////////////////////////////////////
// TESTA OPERANDO

static void testa_operando() {
    // Variáveis auxiliares
    OPERANDO op[] = {
        {.t = NUM, .val.n = 5},
        {.t = ACAO, .val.ac = {.t = MOV, .d = A1}},
        {.t = ACAO, .val.ac = {.t = ATK, .d = A2}},
        {.t = ACAO, .val.ac = {.t = GET, .d = A3}},
        {.t = ACAO, .val.ac = {.t = PEG, .d = A1_}},
        {.t = ACAO, .val.ac = {.t = DEP, .d = A2_}},
        {.t = ACAO, .val.ac = {.t = MOV, .d = A3_}},
        {.t = CELULA, .val.cel = {.t = ESTRADA, .c = 0, .oc = 0}},
        {.t = CELULA, .val.cel = {.t = GRAMA, .c = 3, .oc = 1}},
        {.t = CELULA, .val.cel = {.t = MONTANHA, .c = 8, .oc = 0}},
        {.t = CELULA, .val.cel = {.t = RIO, .c = 0, .oc = 0}},
        {.t = CELULA, .val.cel = {.t = BASE, .c = 5, .oc = 1}},
    };

    // Testando toString_operando
    printf("Imprimindo operandos:\n");
    int n = sizeof(op) / sizeof(OPERANDO);
    for (int i = 0; i < n; i++) {
        char *str = toString_operando(op[i]);
        printf("Operando %d: %s\n", i+1, str);
        free(str);
    }
    printf("char *toString(OPERANDO op) está OK!\n");
}

////////////////////////////////////////////////////////////////////////////////
// TESTA ACAO

static void testa_acao() {
    // Variáveis auxiliares
    Acao acoes[] = {
        {.t = MOV, .d = A1},
        {.t = ATK, .d = A2},
        {.t = GET, .d = A3},
        {.t = PEG, .d = A1_},
        {.t = DEP, .d = A2_},
        {.t = MOV, .d = A3_}
    };

    // Testando toString_celula
    printf("Imprimindo ações:\n");
    int n = sizeof(acoes) / sizeof(Acao);
    for (int i = 0; i < n; i++) {
        char *str = toString_acao(acoes[i]);
        printf("Ação %d: %s\n", i+1, str);
        free(str);
    }
    printf("char *toString_acao(Acao ac) está OK!\n");
}

////////////////////////////////////////////////////////////////////////////////
// TESTA CELULA

static void testa_celula() {
    // Variáveis auxiliares
    Celula celulas[] = {
        {.t = ESTRADA, .c = 0, .oc = 0},
        {.t = GRAMA, .c = 3, .oc = 1},
        {.t = MONTANHA, .c = 8, .oc = 0},
        {.t = RIO, .c = 0, .oc = 0},
        {.t = BASE, .c = 5, .oc = 1}
    };

    // Testando cria_celula
    printf("Criando uma célula:\n");
    Celula *cel = cria_celula(celulas[0].t, celulas[0].c);
    printf("Terreno = %d, Cristais = %d, Ocupado = %d\n", cel->t,
           cel->c, cel->oc);
    printf("Célula criada!\n");
    printf("Celula *cria_celula(Terreno tr, short int cr, short int oc) está");
    printf(" OK!\n");

    // Testando toString_celula
    printf("\nImprimindo células:\n");
    int n = sizeof(celulas) / sizeof(Celula);
    for (int i = 0; i < n; i++) {
        char *str = toString_celula(celulas[i]);
        printf("Célula %d: %s\n", i+1, str);
        free(str);
    }
    printf("char *toString_celula(Celula cel) está OK!\n");

    // Testando destroi_celula
    printf("\nDestruindo célula:\n");
    destroi_celula(cel);
    printf("void destroi_celula(Celula *cel) está OK!\n");
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
    else if (!strcmp(argv[1], "-ac")) {
        printf("Testando acao.c:\n\n");
        testa_acao();
        return 0;
    }
    else if (!strcmp(argv[1], "-cel")) {
        printf("Testando celula.c:\n\n");
        testa_celula();
        return 0;
    }
    else {
        printf("%s não é uma opção válida.\n", argv[1]);
        printf("Use uma das opções abaixo:\n");
        printf("Nanhuma ou '-a' para testar as funções em arena.c\n");
        printf("'-e' para testar as funções em exercito.c\n");
        printf("'-r' para testar as funções em robo.c\n");
        printf("'-o' para testar as funções em operando.c\n");
        printf("'-c' para testar as funções em celula.c\n");
    }
    return 0;
}
