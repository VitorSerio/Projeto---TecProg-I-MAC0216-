#include <stdio.h>
#include "maq.h"

INSTR prog[] = {
    {PUSH, 1},
    {PUSH, 1},
    {STO, 0},
    {STO, 1},

    {RCL, 1},
    {DUP, 0},
    {RCL, 0},
    {ADD, 0},
    {DUP, 0},
    {PRN, 0},
    {STO, 1},
    {STO, 0},
    {JMP, 5},

    {END, 0},
};

int main(int ac, char **av) {
  Maquina *maq = cria_maquina(prog);
  exec_maquina(maq, 3);
  puts("---");
  exec_maquina(maq, 10);
  puts("---");
  exec_maquina(maq, 20);
  destroi_maquina(maq);
  return 0;
}
