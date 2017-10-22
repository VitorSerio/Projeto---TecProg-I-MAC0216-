#ifndef ARENA_H
#define ARENA_H

#include "exercito.h"

#define MAX_CRYSTAL 10
#define MAX_EXERCITOS 6
#define COMANDOS_EXECUTADOS 10

typedef struct {
	int exercitosCount;
	int tamanho;
    Celula mapa[50][50];
    Exercito *exercitos[MAX_EXERCITOS];
    float tempo;
} Arena;

Arena *cria_arena();
void Atualiza();
void InsereExercito();
void RemoveExercito();
OPERANDO Sistema(OPERANDO op);

#endif
