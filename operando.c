#include <stdio.h>
#include <stdlib.h>
#include "operando.h"

static void Erro(char *msg) {
    fprintf(stderr,"%s\n", msg);
}

static void Fatal(char *msg, int cod) {
    Erro(msg);
    exit(cod);
}

static char *stringFromTerreno(Terreno t) {
    char * restrict strings[] = {
        "ESTRADA", "GRAMA", "MONTANHA", "RIO", "BASE"};
    return strings[t];
}

static char *stringFromTipoAc(TipoAc t) {
    char * restrict strings[] = {
        "MOV", "ATK", "GET", "PEG", "DEP"};
    return strings[t];
}

static char *stringFromDirecao(Direcao d) {
    int t = (int) d;
    char * restrict strings[] = {
        "-A3", "-A2", "-A1", "A1", "A2", "A3"};
    t += (t > 0) ? 2 : 3;
    return strings[t];
}

char *toString(OPERANDO op) {
    int size = 50;
    char *res = (char*)malloc(size);
    if (!res) Fatal("Memória insuficiente para char", 4);

    switch (op.t) {
        case NUM:
            snprintf(res, size, "{NUM, %d}", op.val.n);
            break;
        case ACAO:
            snprintf(res, size, "{ACAO, {%s, %s}}",
                     stringFromTipoAc(op.val.ac.t),
                     stringFromDirecao(op.val.ac.d));
            break;
        case CELULA:
            snprintf(res, size, "{CELULA, {%s, %d, %d}}",
                     stringFromTerreno(op.val.cel.terreno), op.val.cel.cristais,
                     op.val.cel.ocupado);
            break;
    }

    return res;
}

// int main() {
//     OPERANDO op[] = {
//         {.t = NUM, .val.n = 5},
//         {.t = ACAO, .val.ac = {.t = MOV, .d = A1}},
//         {.t = ACAO, .val.ac = {.t = ATK, .d = A2}},
//         {.t = ACAO, .val.ac = {.t = GET, .d = A3}},
//         {.t = ACAO, .val.ac = {.t = PEG, .d = A1_}},
//         {.t = ACAO, .val.ac = {.t = DEP, .d = A2_}},
//         {.t = ACAO, .val.ac = {.t = MOV, .d = A3_}},
//         {.t = CELULA, .val.cel = {.terreno = ESTRADA, .cristais = 0, .ocupado = 0}},
//         {.t = CELULA, .val.cel = {.terreno = GRAMA, .cristais = 3, .ocupado = 1}},
//         {.t = CELULA, .val.cel = {.terreno = MONTANHA, .cristais = 8, .ocupado = 0}},
//         {.t = CELULA, .val.cel = {.terreno = RIO, .cristais = 0, .ocupado = 0}},
//         {.t = CELULA, .val.cel = {.terreno = BASE, .cristais = 5, .ocupado = 1}},
//     };
//
//     int n = sizeof(op) / sizeof(OPERANDO);
//     for (int i = 0; i < n; i++) {
//         char *str = toString(op[i]);
//         printf("%s\n", str);
//         free(str);
//     }
//
//     return 0;
// }
