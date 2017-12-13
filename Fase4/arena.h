#ifndef ARENA_H
#define ARENA_H

#include <stdio.h>
#include <stdlib.h>
#include "exercito.h"

#define MAX_TAMANHO 39 // hexagonal de lado 20
#define MAX_EXERCITOS 6

typedef struct Arena {
	short int exercitosCount;
	int tamanho;
    Celula ***mapa;
    Exercito **exercitos;
    int execucoes;
} Arena;

Arena *cria_arena(int tamanho);
Arena *cria_arena_file(FILE *fp);
void destroi_arena(Arena *a);
void Atualiza(Arena *a, int instrucoes);
void InsereExercito(Arena *a, short int pos, short int tam);
void RemoveExercito(Arena *a, short int pos);
void RemoveRobo(Robo *r);
OPERANDO Sistema(Maquina *m, OPERANDO op);
void imprime_mapa(Arena *a);

#endif
