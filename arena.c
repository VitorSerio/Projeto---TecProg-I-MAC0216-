#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maq.h"
#include "arena.h"

static void Erro(char *msg) {
    fprintf(stderr,"%s\n", msg);
}

static void Fatal(char *msg, int cod) {
    Erro(msg);
    exit(cod);
}

Arena *cria_arena(int tamanho){

    Arena arena;

    arena.exercitosCount = 0;
    arena.tamanho = tamanho;
    arena.tempo = 0;

    srand(time(NULL));

    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            int tr = rand() % 4;

            switch (tr){
                case 0:
                    arena.mapa[i][j] = createCell(ESTRADA);
                break;

                case 1:
                    arena.mapa[i][j] = createCell(GRAMA);
                break;

                case 2:
                    arena.mapa[i][j] = createCell(MONTANHA);
                break;

                case 3:
                    arena.mapa[i][j] = createCell(RIO);
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

void Atualiza(Arena arena){

    for(int i = 0; i < arena.exercitosCount; i++){

        int qntRobos = arena.exercitos[i].qntRobos;

        for(int j = 0; j < qntRobos; j++){
            Robo *r = arena.exercitos[i].robos[j];

            roda_robo(r, COMANDOS_EXECUTADOS);
        }
    }

    arena.tempo++;

}

void InsereExercito(Arena arena, INSTR **progs, short int e, int x, int y){
    arena.exercitos[arena.exercitosCount] = *cria_exercito(INSTR **progs, short int e, int x, int y);

    arena.exercitosCount++;
}

void RemoveExercito(Arena arena, Exercito *e){

    int index;

    for(int i = 0; i < arena.exercitosCount; i++){
        Exercito ex = arena.exercitos[i];

        if(ex.e == *e.e){
            index = i;
        }
    }

    for(int i = index; i < arena.exercitosCount - 1; i++){
        arena.exercitos[i] = arena.exercitos[i+1];
    }

    arena.exercitosCount--;
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
