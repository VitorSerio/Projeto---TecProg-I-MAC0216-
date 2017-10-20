#ifndef EXERCITO_H
#define EXERCITO_H

#include "robo.h"

#define MAXVM 5

typedef struct {
    Robo robos[MAXVM];
} Exercito;

Exercito *cria_exercito(int t, int x, int y);

#endif
