#include <stdio.h>
#include <stdlib.h>
#include "maq.h"
#include "arena.h"

static void Erro(char *msg) {
    fprintf(stderr,"%s\n", msg);
}

static void Fatal(char *msg, int cod) {
    Erro(msg);
    exit(cod);
}

Arena *cria_arena();
void Atualiza();
void InsereExercito();
void RemoveExercito();

OPERANDO Sistema(OPERANDO op) {
    Acao ac = op.val.ac;
    switch (ac.t) {
        OPERANDO cel;
        case MOV:
            break;
        case ATK:
            break;
        case GET:
            return cel;
        case PEG:
            break;
        case DEP:
            break;
    }
    return op;
}

// int main(int argc, char const *argv[]) {
//     /* code */
//     return 0;
// }
