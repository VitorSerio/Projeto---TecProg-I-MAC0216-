#include <stdio.h>
#include <stdlib.h>
#include "operando.h"

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

static char *stringFromTipo(Tipo t) {
    char * restrict strings[] = {
        "NUM", "ACAO", "CELULA"};
    return strings[t];
}

static char *stringFromDirecao(Tipo d) {
    int t = (int) d;
    char * restrict strings[] = {
        "-A3", "-A2", "-A1", "A1", "A2", "A3"};
    t += (t > 0) ? 2 : 3;
    return strings[t];
}

char *toString(OPERANDO op) {
    int size = 50;
    char str[size];
    char *res = &str[0];

    switch (op.t) {
        case NUM:
            snprintf(res, size, "{%s, %d}", stringFromTipo(op.t), op.val.n);
            break;
        case ACAO:
            snprintf(res, size, "{%s, {%s, %s}}", stringFromTipo(op.t),
                     stringFromTipoAc(op.val.ac.t),
                     stringFromDirecao(op.val.ac.d));
            break;
        case CELULA:
            snprintf(res, size, "{%s, {%s, %d, %d}}", stringFromTipo(op.t),
                     stringFromTipoAc(op.val.cel.terreno), op.val.cel.cristais,
                     op.val.cel.ocupado);
            break;
    }

    return res;
}

int main() {
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

    int i;
    int n = sizeof(op) / sizeof(OPERANDO);
    for (i = 0; i < n; i++) {
        char *res = toString(op[i]);
        printf("%s\n", res);
    }

    return 0;
}
