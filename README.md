## MAC0216 - Técnicas de Programação I
# Batalha de Robôs - Projeto

Data: 06/10/2017

*Autores*: Rafael Augusto Brandão        (7700827)
         Vitor Barbosa Sério           (7627627)
         Vivian do Amaral Daud Horing  (8125014)

### FASE 2



### FASE 1

MODIFICAÇÕES:

- montador:
    - Adicionados prints para que o programa em C criado possa usar stdio.h e
    maq.h e, consequentemente, maq.c, pilha.h, pilha.c e instr.h.
    - Adicionada parte para a função main(), permitindo que o programa criado
    execute algo de fato.
    - Ao ler uma linha vazia do programa em Assembly, essa linha é descontada
    da contagem de instruções (ip).

- instr.h:
    - Acrescentadas as intruções STL, RCE, ACL e FRE a OpCode.

- maq.h:
    - Adicionado inteiro rbp ao struct Maquina, que será usado para apontar a
    base dos frames da pilha de execução.

- maq.c:
    - Criação dos macros rbp e rsp:
        - rbp:
            - Equivale a m->rbp
            - Referente ao valor do rbp da Maquina m
            - rbp é inicializado valendo 0
        - rsp:
            - Equivale a exec->topo
            - Referente ao valor do topo da pilha de execução de m

    - Acrescentadas as intruções STL, RCE, ACL e FRE a *CODES.

    - Intruções STL, RCE, ACL e FRE foram implementadas:
        - STL:
            - Recebe argumento numérico não-negativo.
            - Desempilha da pilha de dados e move valor para posição
            RBP + argumento da pilha de execução.
            - Causa erro fatal se RBP + argumento for um valor fora do frame da
            função.
            - OBS: o argumento inicia em 0, não em 1.
        - RCE:
            - Recebe argumento numérico não-negativo.
            - Copia valor da posição RBP + argumento da pilha de execução e o
            empilha na pilha de dados.
            - Causa erro fatal se RBP + argumento for um valor fora do frame da
            função.
            - OBS: o argumento inicia em 0, não em 1.
        - ACL:
            - Recebe argumento numérico não-negativo.
            - Aloca um espaço igual a argumento para que uma função possa usar
            variáveis locais.
            - Causa erro fatal se alocação extrapolar tamanho da pilha.
        - FRE:
            - Recebe argumento numérico não-negativo.
            - Desaloca um espaço igual a argumento, geralmente para dar return
            em uma função, mas não necessariamente
            - Causa erro fatal se desalocação for maior que o espaço alocado.

    - Alterações nas intruções CALL e RET:
        - CALL:
            - Empilha o valor de RBP na pilha de execução e, em seguida,
            atualiza o valor de RBP para ficar igual a RSP.
            - Nota: essa forma de implementação faz com que que STL e RCE
            precisem receber argumento 0 para se referir à primeira posição do
            frame da frunção atual.
            - Continua com funções anteriores.
        - RET:
            - Desempilha valor anterior do RBP (empilhado pelo CALL).
            - Retorna mensagem de erro, caso haja espeço alocado e faz uma
            desalocação forçada, se necessário.
            - Continua com as funções anteriores.