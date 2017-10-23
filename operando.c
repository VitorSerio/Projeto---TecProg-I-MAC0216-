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

char *toString_operando(OPERANDO op) {
    int size = 30;
    char *res = (char*)malloc(size);
    if (!res) Fatal("Memória insuficiente para char", 4);

    switch (op.t) {
        char *str;
        case NUM:
            snprintf(res, size, "{NUM, %d}", op.val.n);
            break;
        case ACAO:
            str = toString_acao(op.val.ac);
            snprintf(res, size, "{ACAO, %s}", str);
            free(str);
            break;
        case CELULA:
            str = toString_celula(op.val.cel);
            snprintf(res, size, "{CELULA, %s}", str);
            free(str);
            break;
    }

    return res;
}
