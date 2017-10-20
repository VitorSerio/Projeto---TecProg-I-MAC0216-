#include <stdio.h>
#include <stdlib.h>
#include "robo.h"

Robo cria_robo(INSTR *p, int x, int y) {
    struct Robo r;
    r.m = cria_maquina(p);
    r.x = x;
    r.y = y;
    r.c = 0;
}
