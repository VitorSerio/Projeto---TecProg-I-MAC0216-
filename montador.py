from sys import stdin
import re

def printInstrs(instrs):
    """ Uso: 2D list -> void
    Dada uma lista bidimensional que representa uma série de instruções,
    imprime, na saída padrão, os valores de cada instrução, no formato adequado
    para o programa em C.
    """
    def convertArg(op, arg):
        """ Uso: str, list -> str
        Dadas uma string e uma lista que representam, respectivamente, o opcode
        e o argumento de uma instrução, retorna uma string, que representa o
        argumento da instrução, no formato adequado para o programa em C.
        """
        res = ""
        if op == "SYS":
            res = ".t = ACAO, .val.ac = {.t = %s" % (arg[0])
            res += ", .d = %s}" % (arg[1])
        else:
            res = ".t = NUM, "
            res += ".val.n = %s" % (arg[0])
        return res
    """Fim de convertArg, volta printInstrs"""

    n = len(instrs)
    for i in range(n):
        arg = convertArg(instrs[i][0], instrs[i][1:])
        print("    {%s, {%s}}," % (instrs[i][0], arg))


def getLines():
    """ Uso: void -> 2D list
    Cria uma lista bidimensional de strings que representam todas as instruções
    do programa. Ignora comentários e linhas 'vazias'.
    """
    def fixLabels(instrs, labels):
        """ Uso: 2D list, dict -> 2D list
        Substitui todos os labels contidos na lista dada por suas respectivas
        linhas, de acordo com o dicionário, de forma a permitir o uso de labels
        nos programas.
        """
        n = len(instrs)
        for i in range(n):
            instrs[i][1] = labels.get(instrs[i][1], instrs[i][1])

        return instrs
    """Fim getLabels, Volta getLines"""

    instrs = [] # instruções
    labels = {} # dicionário
    ip = 0      # conagem das linhas de instruções
    line = stdin.readline()
    while line:
        try:
            # Remove comentários
            line = line[:line.index('#')]
        except:
            pass
        # Pula se for uma linha 'vazia'
        if not re.match("^\s+$", line):
            # Separação de label, opcode e argumento
            keys = line.split()
            # Se há label
            if ":" in keys[0]:
                # Atualiza o dicionário e romove o label
                labels[keys[0][:-1]] = ip
                keys.pop(0)
            if len(keys) == 1:
                # Adiciona argumento genérico para instruções sem argumento
                keys.append('0')
            # Adiciona instrução
            instrs.append(keys)
            ip += 1
        line = stdin.readline()

    instrs = fixLabels(instrs, labels)

    return instrs


def main():
    """
    Lê, na entrada padrão, um programa na linguagem de montagem da máquina
    virtual e retorna um programa em C que executa este programa.

    Uso:
        montador < entrada > saida
    """

    # Adicionando dependências
    print("#include <stdio.h>")
    print('#include "maq.h"\n')

    print("INSTR prog[] = {")
    lines = getLines()
    printInstrs(lines)
    print("};\n")

    print("int main() {")
    print("    Maquina *maq = cria_maquina(prog);")
    print("    exec_maquina(maq, %d);"%(50))
    print('    puts("----------");')
    print("    exec_maquina(maq, %d);"%(100))
    print('    puts("----------");')
    print("    exec_maquina(maq, %d);"%(200))
    print("    destroi_maquina(maq);")
    print("    return 0;")
    print("}")

main()
