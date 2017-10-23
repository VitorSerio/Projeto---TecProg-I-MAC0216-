#ifndef ARENA_H
#define ARENA_H

#include "exercito.h"

#define MAX_ARENA 39 // hexagonal de lado 20
#define MAX_CRYSTAL 10
#define MAX_EXERCITOS 6

typedef struct {
	int exercitosCount;
	int tamanho;
    Celula *mapa[MAX_ARENA][MAX_ARENA];
    Exercito **exercitos;
    int execucoes;
} Arena;

Arena *cria_arena(int tamanho);
Arena *cria_arena_file(FILE *fp);
void Atualiza(Arena *arena);
void InsereExercito(Arena *arena, INSTR **progs, int n, int x, int y);
void RemoveExercito(Arena *arena, int pos);
OPERANDO Sistema(Maquina *m, OPERANDO op);

#endif
