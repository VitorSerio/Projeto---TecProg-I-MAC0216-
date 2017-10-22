#ifndef ARENA_H
#define ARENA_H

#include "exercito.h"

typedef struct {
	int tamanho;
    Celula mapa[50][50];
    Exercito *exercitos[6];
    float tempo;
} Arena;

Arena *cria_arena();
void Atualiza();
void InsereExercito();
void RemoveExercito();
OPERANDO Sistema(OPERANDO op);

#endif
