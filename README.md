## MAC0216 - Técnicas de Programação I
# Batalha de Robôs - Projeto

Data: 19/10/2017

*Autores*:

    - Rafael Augusto Brandão        (7700827)
    - Vitor Barbosa Sério           (7627627)
    - Vivian do Amaral Daud Horing  (8125014)


### FASE 2
Data: 19/10/2017

MODIFICAÇÕES:

- Todos os arquivos **.h** receberam *inclusion guards*, para usar dependência
circular.
- Criados os arquivos **acao.h**, **celula.h**, **operando.h** e **operando.c**:
    - **acao.h**:
        - Define as `enum` `Direcao` e `TipoAc`:
            - `Direcao`:
                - Representa a direção e o sentido de uma ação.
                - Assume os valores *A1*, *A1_*, *A2*, *A2_*, *A3* e *A3_*:
                    - *A1*:
                        - Vetor: (1, 0)
                        - Valor: 1
                    - *A1_*:
                        - Vetor: (-1, 0)
                        - Valor: -1
                    - *A2*:
                        - Vetor: (0, 1)
                        - Valor: 2
                    - *A2_*:
                        - Vetor: (0, -1)
                        - Valor: -2
                    - *A3*:
                        - Vetor: (1, -1)
                        - Valor: 3
                    - *A3_*:
                        - Vetor: (-1, 1)
                        - Valor: -3
            - `TipoAc`:
                - Representa o tipo de ação executada pelo robô.
                - Assume os valores *MOV*, *ATK*, *GET*, *PEG* e *DEP*:
                    - *MOV*:
                        - Movimentação do robô.
                        - Valor: 0
                    - *ATK*:
                        - Ataca outro robô.
                        - Valor: 1
                    - *GET*:
                        - Pede os dados de uma célula adjacente.
                        - Valor: 2
                    - *PEG*:
                        - Pega um cristal.
                        - Valor: 3
                    - *DEP*:
                        - Deposita um cristal.
                        - Valor: 4
        - Define a `struct` `Acao`:
            - Representa uma ação executada por um robô.
            - Sempre necessita de chamadas ao sistema.
            - Contém os valores `t` e `d`:
                - `t`:
                    - Tipo: `TipoAc`
                    - Representa o tipo da ação.
                - `d`:
                    - Tipo: `Direcao`
                    - Representa a direção da ação.
                    
    - **celula.h**:
        - Define a `enum` `Terreno`:
            - `Terreno`:
                - Representa o tipo de terreno em uma célula.
                - Assume os valores *ESTRADA*, *GRAMA*, *MONTANHA*, *RIO* e
                *BASE*:
                    - *ESTRADA*:
                        - Custo de locomoção 1.
                        - Valor: 0
                    - *GRAMA*:
                        - Custo de locomoção 2.
                        - Valor: 1
                    - *MONTANHA*:
                        - Custo de locomoção 4.
                        - Valor: 2
                    - *RIO*:
                        - Custo de locomoção 4.
                        - Valor: 3
                    - *BASE*:
                        - Impede locomoção.
                        - Valor: 4
        - Define a `struct` `Celula`:
            - Representa os dados de uma célula do mapa.
            - Contém os valores `terreno`, `cristais`, `ocupado`:
                - `terreno`:
                    - Tipo: `Terreno`
                    - Representa qual o tipo de terreno da célula.
                - `cristais`:
                    - Tipo: `short int`
                    - Representa a quantidade de cristais presentes na célula.
                - `ocupado`:
                    - Tipo: `short int`
                    - Representa se a célula já está ocupada por um robô.
                    - Vale 0, se não estiver ocupada e 1, se estiver.

    - **operando.h**:
        - Define a `enum` `Tipo`:
            - `Tipo`:
                - Representa o tipo de um `OPERANDO`.
                - Assume os valores *NUM*, *ACAO* e *CELULA*:
                    - *NUM*:
                        - Literais numéricos.
                        - Valor: 0
                    - *ACAO*:
                        - Ação executada por um robô.
                        - Valor: 1
                    - *CELULA*:
                        - Dados de uma célula.
                        - Valor: 2
        - `OPERANDO` é agora uma `struct` com os valores `t` e `val`:
            - `t`:
                - Tipo: `Tipo`
                - Representa o tipo do operando.
            - `val`:
                - É uma `union`.
                - Representa o valor do operando.
                - Pode ter os valores `n`, `ac` ou `cel`:
                    - `n`:
                        - Tipo: `int`
                        - Referente a inteiros literais (`t = NUM`).
                    - `ac`:
                        - Tipo: `Acao`
                        - Referente a ações (`t = ACAO`).
                    - `cel`:
                        - Tipo: `Celula`
                        - Referente a células (`t = CELULA`).
        - Declara a função `char *toString(OPERANDO op)`, que converte um
        `OPERANDO` para um `char*`.

    - **operando.c**:
        - Implementa a função `char *toString(OPERANDO op)`.
        - Implementa uma função `main()` para testes.
        - As outras funções são puramente auxiliares de `toString`.

- **instr.h**:
    - Acrescentadas as instruções *ATR* e *SIS* a `OpCode`.
    - `OPERANDO` foi movido para um arquivo próprio (**operando.h**).

- **maq.c**:
    - Todas as instruções foram adaptadas ao novo formato de `OPERANDO`.
    - As instruções *ADD*, *SUB*, *MUL*, *DIV*, *JIT*, *JIF*, *EQ*, *GT*, *GE*,
    *LT*, *LE*, *NE*, *STO* e *RCL* agora gerenciam possíveis erros.
    - Aprimoração das mensagens de erro:
        - Linha com a localização do erro é fornecida.
        - Um label 'Erro' ou 'Aviso' são usados para sinalizar um erro fatal ou
        um erro mais simples, respectivamente.
    - Adicionadas as instruções *ATR* e *SIS* a `*CODES`.
    - Instruções *ATR* e *SIS* foram implementadas:
        - *ATR*:
            - Obtém um atributo de um `OPERANDO` do tipo `CELULA` da pilha de
            dados.
            - O atributo é selecionado através de um inteiro:
                - 1: `terreno`
                - 2: `cristais`
                - 3: `ocupacao`
            - Se o argumento não for um dos inteiros listados acima, causa erro
            fatal.
        - *SIS*:

### FASE 1
Data: 06/10/2017

MODIFICAÇÕES:

- **montador**:
    - Adicionados `print`s para que o programa em C criado possa usar
    **stdio.h** e **maq.h** e, consequentemente, **maq.c**, **pilha.h**,
    **pilha.c** e **instr.h**.
    - Adicionada parte para a função `main()`, permitindo que o programa criado
    execute algo de fato.
    - Ao ler uma linha vazia do programa em Assembly, essa linha é descontada
    da contagem de instruções (`ip`).

- **instr.h**:
    - Acrescentadas as intruções *STL*, *RCE*, *ACL* e *FRE* a `OpCode`.

- **maq.h**:
    - Adicionado inteiro *rbp* ao `struct` `Maquina`, que será usado para
    apontar a base dos frames da pilha de execução.

- **maq.c**:
    - Criação dos macros `rbp` e `rsp`:
        - `rbp`:
            - Equivale a `m->rbp`
            - Referente ao valor do `rbp` da `Maquina m`
            - `rbp` é inicializado valendo 0
        - `rsp`:
            - Equivale a `exec->topo`
            - Referente ao valor do topo da pilha de execução de `m`

    - Acrescentadas as intruções *STL*, *RCE*, *ACL* e *FRE* a `*CODES`.

    - Intruções *STL*, *RCE*, *ACL* e *FRE* foram implementadas:
        - *STL*:
            - Recebe argumento numérico não-negativo.
            - Desempilha da pilha de dados e move valor para posição
            RBP + argumento da pilha de execução.
            - Causa erro fatal se RBP + argumento for um valor fora do frame da
            função.
            - OBS: o argumento inicia em 0, não em 1.
        - *RCE*:
            - Recebe argumento numérico não-negativo.
            - Copia valor da posição RBP + argumento da pilha de execução e o
            empilha na pilha de dados.
            - Causa erro fatal se RBP + argumento for um valor fora do frame da
            função.
            - OBS: o argumento inicia em 0, não em 1.
        - *ACL*:
            - Recebe argumento numérico não-negativo.
            - Aloca um espaço igual a argumento para que uma função possa usar
            variáveis locais.
            - Causa erro fatal se alocação extrapolar tamanho da pilha.
        - *FRE*:
            - Recebe argumento numérico não-negativo.
            - Desaloca um espaço igual a argumento, geralmente para dar return
            em uma função, mas não necessariamente
            - Causa erro fatal se desalocação for maior que o espaço alocado.

    - Alterações nas intruções *CALL* e *RET*:
        - *CALL*:
            - Empilha o valor de RBP na pilha de execução e, em seguida,
            atualiza o valor de RBP para ficar igual a RSP.
            - Nota: essa forma de implementação faz com que que *STL* e *RCE*
            precisem receber argumento 0 para se referir à primeira posição do
            frame da frunção atual.
            - Continua com as funções anteriores.
        - *RET*:
            - Desempilha valor anterior do RBP (empilhado pelo *CALL*).
            - Retorna mensagem de erro, caso haja espaço alocado e faz uma
            desalocação forçada, se necessário.
            - Continua com as funções anteriores.
