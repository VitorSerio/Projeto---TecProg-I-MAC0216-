#ifndef BASE_H
#define BASE_H

#include "vetor.h"

#define B_MAX_HP 15

typedef struct Base {
    Vetor pos;
    short int hp;
    short int e;
} Base;

#endif
