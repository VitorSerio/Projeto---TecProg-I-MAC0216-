#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maq.h"
#include "arena.h"

#define MAX_CRYSTAL 10

static void Erro(char *msg) {
    fprintf(stderr,"%s\n", msg);
}

static void Fatal(char *msg, int cod) {
    Erro(msg);
    exit(cod);
}

Arena *cria_arena(int tamanho){

    Arena arena;

    arena->tamanho = tamanho;
    arena->tempo = 0;

    srand(time(NULL));

    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            int tr = rand() % 4;

            switch (tr){
                case 0:
                    arena->mapa[i][j] = createCell(ESTRADA);
                break;

                case 1:
                    arena->mapa[i][j] = createCell(GRAMA);
                break;

                case 2:
                    arena->mapa[i][j] = createCell(MONTANHA);
                break;

                case 3:
                    arena->mapa[i][j] = createCell(RIO);
                break;

                default:
            }
        }
    }

    return arena;
}

Celula createCell(Terreno terreno){
    return (Celula) {.cristais = rand() % (MAX_CRYSTAL + 1), .ocupado = 0, .terreno = terreno};
}

void Atualiza(){

}

void InsereExercito(){

}

void RemoveExercito(){

}

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
