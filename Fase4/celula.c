#include <stdio.h>
#include <stdlib.h>
#include "celula.h"

static void Erro(char *msg) {
    fprintf(stderr,"%s\n", msg);
}

static void Fatal(char *msg, int cod) {
    Erro(msg);
    exit(cod);
}

static char *toString_terreno(Terreno t) {
    char* restrict strings[] = {
        "ESTRADA", "GRAMA", "MONTANHA", "RIO", "BASE"};
    return strings[t];
}

Celula *cria_celula(Terreno t, short int c) {
    Celula *cel = (Celula*) malloc(sizeof(Celula));
    cel->t = t;
    cel->c = c;
    cel->r = NULL;
    cel->b = NULL;
    cel->oc = 0;

    return cel;
}

void destroi_celula(Celula *cel) {
    free(cel);
    cel = NULL;
}

char *toString_celula(Celula *cel) {
    int size = 20;
    char *res = (char*)malloc(size);
    if (!res) Fatal("Memória insuficiente para char", 4);
    char *t = toString_terreno(cel->t);
    snprintf(res, size, "{%s, %d, %d}", t, cel->c, cel->oc);
    return res;
}
