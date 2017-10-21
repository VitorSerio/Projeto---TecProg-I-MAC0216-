#include <stdio.h>
#include "maq.h"

INSTR prog[] = {
    {PUSH, {.t = NUM, .val.n = 1}},
    {DUP, {.t = NUM, .val.n = 0}},
    {STO, {.t = NUM, .val.n = 0}},
    {STO, {.t = NUM, .val.n = 1}},
    {PUSH, {.t = NUM, .val.n = 10}},
    {STO, {.t = NUM, .val.n = 2}},
    {RCL, {.t = NUM, .val.n = 0}},
    {RCL, {.t = NUM, .val.n = 1}},
    {DUP, {.t = NUM, .val.n = 0}},
    {STO, {.t = NUM, .val.n = 0}},
    {ADD, {.t = NUM, .val.n = 0}},
    {DUP, {.t = NUM, .val.n = 0}},
    {STO, {.t = NUM, .val.n = 1}},
    {PRN, {.t = NUM, .val.n = 0}},
    {RCL, {.t = NUM, .val.n = 2}},
    {PUSH, {.t = NUM, .val.n = 1}},
    {SUB, {.t = NUM, .val.n = 0}},
    {DUP, {.t = NUM, .val.n = 0}},
    {STO, {.t = NUM, .val.n = 2}},
    {PUSH, {.t = NUM, .val.n = 0}},
    {EQ, {.t = NUM, .val.n = 0}},
    {JIF, {.t = NUM, .val.n = 6}},
    {SYS, {.t = ACAO, .val.ac = {.t = 0, .d = 1}}},
    {END, {.t = NUM, .val.n = 0}},
};

int main() {
    Maquina *maq = cria_maquina(prog);
    exec_maquina(maq, 50);
    puts("----------");
    exec_maquina(maq, 100);
    puts("----------");
    exec_maquina(maq, 200);
    destroi_maquina(maq);
    return 0;
}
