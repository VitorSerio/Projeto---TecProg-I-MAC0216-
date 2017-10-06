#include "exercito.h"

typedef struct {
    int mapa[][];
    Exercito exercitos[];
    float tempo;
} Arena;

Arena *cria_arena();
void Atualiza();
void InsereExercito();
void RemoveExercito();
