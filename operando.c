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
