#include <stdio.h>
#include <stdlib.h>
#include "acao.h"

static void Erro(char *msg) {
    fprintf(stderr,"%s\n", msg);
}

static void Fatal(char *msg, int cod) {
    Erro(msg);
    exit(cod);
}

static char *toString_tipoAc(TipoAc t) {
    char * restrict strings[] = {"MOV", "ATK", "GET", "PEG", "DEP"};
    return strings[t];
}

static char *toString_direcao(Direcao d) {
    int t = (int) d;
    char * restrict strings[] = {"-A3", "-A2", "-A1", "A1", "A2", "A3"};
    t += (t > 0) ? 2 : 3;
    return strings[t];
}

char *toString_acao(Acao ac) {

    int size = 15;
    char *res = (char*)malloc(size);
    if (!res) Fatal("Memória insuficiente para char", 4);

    char *t = toString_tipoAc(ac.t);
    char *d = toString_direcao(ac.d);

    snprintf(res, size, "{%s, %s}", t, d);
    
    return res;
}
