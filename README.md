## MAC0216 - Técnicas de Programação I
# Batalha de Robôs - Projeto

Data: 22/10/2017

**Autores**:

    Rafael Augusto Brandão        (7700827)
    Vitor Barbosa Sério           (7627627)
    Vivian do Amaral Daud Horing  (8125014)


### FASE 2
Data: 22/10/2017

**NOVIDADES**:

- Todos os arquivos **.h** receberam *inclusion guards*, para usar dependência
circular.

- **Makefile**:
    - Regra *default*:
        - Execução: `make` ou `make testes`.
        - Requer: **main.o**, **arena.o**, **exercito.o**, **robo.o**,
        **maq.o**, **pilha.o** e **operando.o**.
        - Cria o arquivo:
            - **testes**:
                - Tipo: executável
                - Testa as funções implementadas nos arquivos **.c**.
                - Execução:
                    - `./testes` ou `./testes -a`:
                        - Executa testes nas funções em **arena.c**.
                    - `./testes -e`:
                        - Executa testes nas funções em **exercito.c**.
                    - `./testes -r`:
                        - Executa testes nas funções em **robo.c**.
                    - `./testes -o`:
                        - Executa testes nas funções em **operando.c**.
    - Outras regras:
        - `make motor`:
            - Requer: **montador.py**, **prog**, **exercito.o**, **robo.o**,
            **maq.o**, **pilha.o** e **operando.o**.
            - Cria o arquivo:
                - **motor**:
                    - Tipo: Executável.
                    - Testa se o arquivo gerado por **montador** está
                    funcionando.
                    - Acaba testando, por consequência, as instruções definidas
                    em **maq.c**.
                    - Execução: `./motor`
        - `make clean`:
            - Remove todos os arquivos gerados pelas outras regras.

--------------------------------------------------------------------------------

- **_Criados_** os arquivos:
    - **acao.h**:
        - Define:
            - `Direcao`:
                - Tipo: `enum`
                - Representa a direção e o sentido de uma ação.
                - Assume os valores:
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
                - Tipo: `enum`
                - Representa o tipo de ação executada pelo robô.
                - Assume os valores:
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
            - `Acao`:
                - Tipo: `struct`
                - Representa uma ação executada por um robô.
                - Sempre necessita de chamadas ao sistema.
                - Contém os valores:
                    - `t`:
                        - Tipo: `TipoAc`
                        - Representa o tipo da ação.
                    - `d`:
                        - Tipo: `Direcao`
                        - Representa a direção da ação.

    - **celula.h**:
        - Define:
            - `Terreno`:
                - Tipo: `enum`
                - Representa o tipo de terreno em uma célula.
                - Assume os valores:
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
            - `Celula`:
                - Tipo: `struct`
                - Representa os dados de uma célula do mapa.
                - Contém os valores:
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
        - Define a:
            - `Tipo`:
                - Tipo: `enum`
                - Representa o tipo de um `OPERANDO`.
                - Assume os valores:
                    - *NUM*:
                        - Literais numéricos.
                        - Valor: 0
                    - *ACAO*:
                        - Ação executada por um robô.
                        - Valor: 1
                    - *CELULA*:
                        - Dados de uma célula.
                        - Valor: 2
            - `OPERANDO`:
                - Tipo: `struct`
                - Contém os valores:
                    - `t`:
                        - Tipo: `Tipo`
                        - Representa o tipo do operando.
                    - `val`:
                        - Tipo: `union`.
                        - Representa o valor do operando.
                        - Pode ter os valores:
                            - `n`:
                                - Tipo: `int`
                                - Referente a inteiros literais (`t = NUM`).
                            - `ac`:
                                - Tipo: `Acao`
                                - Referente a ações (`t = ACAO`).
                            - `cel`:
                                - Tipo: `Celula`
                                - Referente a células (`t = CELULA`).
        - Declara a função:
            - `toString`:
                - Retorna uma string que representa um `OPERANDO`.
                - Recebe:
                    - `OPERANDO op`
                - Retorna:
                    - `char*`

    - **operando.c**:
        - Implementa a função `toString`:
            - É importante observar que essa função aloca espaço na memória para
            o ponteiro `char*`, precisando que essa memória seja liberada com a
            função `free` eventualmente.
        - As outras funções são puramente auxiliares de `toString`.

    - **robo.h**:
        - Define a `struct` `Robo`:
            - `Robo`:
                - Representa um robô de um exército.
                - Contém os valores:
                    - *m*:
                        - Tipo: `Maquina*`
                        - É a máquina virtual do robô, que executará o seu
                        próprio programa.
                    - *x*:
                        - Tipo: `int`
                        - Representa a posição horizontal do robô na matriz
                        quadrada (que representa a hexagonal).
                    - *y*:
                        - Tipo: `int`
                        - Representa a posição vertical do robô na matriz
                        quadrada.
                    - *c*:
                        - Tipo: `short int`
                        - Representa a quantidade de cristais que está sendo
                        carregada pelo robô.
                    - *id*:
                        - Tipo: `short int`
                        - Representa a posição do robô, dentro do exército.
                    - *e*:
                        - Tipo: `Exercito*`
                        - Representa a qual exército o robô pertence.
        - Declara as funções:
            - `cria_robo`:
                - Função construtora do tipo `Robo`.
                - Recebe:
                    - `INSTR *p`:
                        - Programa a ser executado pelo robô.
                    - `int x`:
                        - Atributo *x* do robô.
                    - `int y`:
                        - Atributo *y* do robô.
                - Retorna:
                    - `Robo*` com os atributos dados e uma `Maquina` com o
                    programa dado.
            - `destroi_robo`:
                - Libera a memória alocada para um `Robo` e sua `Maquina`.
                - Recebe:
                    - `Robo *r`:
                        - `Robo` a ser 'desfeito'.
                - Não possui `return`.
            - `torca_prog`:
                - Troca o programa a ser executado por um robô.
                - Recebe:
                    - `INSTR *p`:
                        - O novo programa a ser dado pro robô.
                    - `Robo *r`:
                        - O robô que receberá o novo programa.
                - Não possui `return`.
            - `roda_robo`:
                - Executa o programa de um robô.
                - Recebe:
                    - `Robo *r`:
                        - O robô cujo programa será executado.
                    - `int n`:
                        - Quantidade de instruções para ser executada.
    - **robo.c**:
        - Implementa as funções `cria_robo`, `destroi_robo`, `troca_prog` e
        `roda_robo`.
        - Implementa as funções `Erro` e `Fatal`, para gerenciamento de erros.

    - **base.h**:
        - Define:
            - `Base`:
                - Tipo: `struct`
                - Representa a base de um exército.
                - Contém os valores:
                    - *x*:
                        - Tipo: `int`
                        - Representa a posição horizontal da base na matriz
                        quadrada (que representa a hexagonal).
                    - *y*:
                        - Tipo: `int`
                        - Representa a posição vertical da base na matriz
                        quadrada.
                    - *e*:
                        - Tipo: `short int`
                        - Representa a qual exército a base pertence.

    - **exercito.h**:
        - Define *MAXVM*, que representa a quantidade máxima de robôs por
        exército.
        - Define:
            - `Exercito`:
                - Tipo: `struct`
                - Representa um exército (time) do jogo.
                - Contém os seguintes valores:
                    - *robos*:
                        - Tipo: `Robo**`
                        - Representa todos os robôs do exército.
                    - *b*:
                        - Tipo: `Base`
                        - Representa a base do exército.
                    - *size*:
                        - Tipo: `short int`
                        - Representa a quantidade de robôs ativos no exército.
                    - *e*:
                        - Tipo: `short int`
                        - Identificação do exército.
                    - *a*:
                        - Tipo: `Arena*`
                        - Representa a arena que contém o `Exercito`.
        - Declara as funções:
            - `cria_exercito`:
                - Função construtora do tipo `Exercito`.
                - Recebe:
                    - `INSTR **progs`:
                        - Ponteiro com os programas de cada robô do exército.
                        - O número de programas não deve exceder *MAXVM*.
                    - `short int n`:
                        - A quantidade de programas presentes em *progs*.
                    - `short int e`:
                        - Identificador do exército.
                    - `int x`:
                        - Posição horizontal da base do exército.
                    - `int y`:
                        - Posição vertical da base do exército.
                - Gera aviso se forem dados mais programas que o limite.
                - Retorna:
                    - `Exercito*` com os atributos passados, `Robo*`s com os
                    programas em `progs` e uma `Base`.
            - `destroi_exercito`:
                - Libera a memória alocada para um `Exercito` e seus `Robo`s.
                - Recebe:
                    - `Exercito *e`:
                        - `Exercito` a ser 'desfeito'.
                - Não possui `return`.
            - `adiciona_robo`:
                - Adiciona um robô ao `Exercito`, no primeiro espaço vazio
                disponível de *robos*.
                - Recebe:
                    - `Exercito *e`:
                        - `Exercito` a ser modificado.
                    - `INSTR *p`:
                        - Programa do robô que será adicionado.
                - Gera aviso se o limite de robôs já tiver sido atingido.
                - Não possui `return`.
            - `remove_robo`:
                - Remove um robô de um exército na posição dada.
                - Recebe:
                    - `Exercito *e`:
                        - `Exercito` a ser modificado.
                    - `int pos`:
                        - Posição do robô que será removido.
                - Gera aviso, se a posição dada já estiver vazia.
                - Não possui `return`.
    - **exercito.c**:
        - Implementa as funções `cria_exercito`, `destroi_exercito`,
        `adiciona_robo` e `remove_robo`.
        - Implementa as funções `Erro` e `Fatal`, para gerenciamento de erros.

    - **arena.h**:
        - Define *MAX_ARENA*, *MAX_CRYSTAL* e *MAX_EXERCITOS*.
        - Define:
            - `Arena`:
                - Tipo: `struct`
                - Contém os seguintes valores:
                    - *exercitosCount*:
                        - Tipo: `int`
                        - Quantidade de exércitos ativos na arena.
                    - *tamanho*:
                        - Tipo: `int`
                        - Tamanho da arena (matriz quadrada).
                    - *mapa*:
                        - Tipo: `array` 2D de `Celula*`
                        - Representa o mapa da arena.
                    - *exercitos*:
                        - Tipo: `Exercito**`
                        - Exércitos da arena.
                    - *execucoes*:
                        - Quantidade de vezes que robôs executaram seus
                        programas (tempo).
        - Declara as funções:
            - `cria_arena`:
                - Função contrutora do tipo arena.
                - Gera uma arena aleatória com tamanho dado.
                - Recebe:
                    - `int tamanho`:
                        - Tamanho da arena gerada.
                - Retorna:
                    - `Arena*` com o tamanho dado, mapa aleatório e sem
                    exércitos ativos.
            - `cria_arena_file`:
                - Função contrutora do tipo arena.
                - Gera uma arena a partir de um arquivo.
                - Recebe:
                    - `FILE *fp`:
                        - Arquivo que será lido.
                - Retorna:
                    - `Arena*` com tamanho e mapa dados pelo arquivo e sem
                    exércitos ativos.
            - `Atualiza`:
                - Faz com que cada robô, de cada exército, execute uma mesma
                quantidade de instruções, por vez.
                - Atualiza o valor de `execucoes` para cada robô que executou o
                seu programa.
                - Recebe:
                    - `Arena *arena`:
                        - A arena que contém os exércitos.
                - Não possui `return`.
            - `InsereExercito`:
                - Adiciona um exército à arena, no primeiro espaço vazio de
                *exercitos*.
                - Recebe:
                    - `Arena *arena`:
                        - A arena que irá recebe o novo exército.
                    - `INSTR **progs`:
                        - Os programas dos robôs do novo exército.
                    - `int n`:
                        - A quantidade de programas contidos em `progs`.
                    - `int x`:
                        - A posição horizontal da base do exército novo.
                    - `int y`:
                        - A posição vertical da base do exército novo.
                - Não possui `return`.
            - `RemoveExercito`:
                - Remove um exército da arena, na posição dada.
                - Recebe:
                    - `Arena *arena`:
                        - Arena que terá o exército removido.
                    - `int pos`:
                        - Posição do exército que será removido.
                - Não possui `return`.
            - `Sistema`:
                - Função responsável pela comunicação entre `Maquina` e `Arena`.
                - Recebe:
                    - `Maquina *m`:
                        - A máquina que está fazendo a slicitação.
                    - `OPERANDO op`:
                        - A instrução que a máquina está passando.
                        - Lembrando que esse `OPERANDO` deve ser sempre do tipo
                        `ACAO`.
                - Retorna:
                    - `OPERANDO` de acordo com a solicitação feita.
    - **arena.c**:
        - Implementa as funções `cria_arena`, `cria_arena_file`, `Atualiza`,
        `InsereExercito`, `RemoveExercito` e `Sistema`.
        - Implementa as funções `Erro` e `Fatal`, para gerenciamento de erros.

--------------------------------------------------------------------------------

- **_Modificados_** os arquivos:
    - **instr.h**:
        - Acrescentadas as instruções *ATR* e *SYS* a `OpCode`.
        - `OPERANDO` foi movido para um arquivo próprio (**operando.h**).

    - **maq.c**:
        - Todas as instruções foram adaptadas ao novo formato de `OPERANDO`.
        - As instruções *ADD*, *SUB*, *MUL*, *DIV*, *JIT*, *JIF*, *EQ*, *GT*,
        *GE*, *LT*, *LE*, *NE*, *STO* e *RCL* agora gerenciam possíveis erros.
        - Aprimoração das mensagens de erro:
            - Linha com a localização do erro é fornecida.
            - Um label 'Erro' ou 'Aviso' são usados para sinalizar um erro
            fatal ou um erro mais simples, respectivamente.
        - Adicionadas as instruções *ATR* e *SYS* a `*CODES`.
        - Implementação das instruções:
            - *ATR*:
                - Obtém um atributo de um `OPERANDO` do tipo `CELULA` da pilha
                de dados.
                - O atributo é selecionado através de um inteiro:
                    - 1: `terreno`
                    - 2: `cristais`
                    - 3: `ocupado`
                - Se o argumento não for um dos inteiros listados acima, causa
                erro fatal.
            - *SYS*:
                - Faz solicitações ao sistema.
                - Recebe argumento de `Tipo t = ACAO`
                - A maioria das ações causa mudanças fora da máquina. Apenas
                *GET* é exceção, empilhando os dados de uma célula na pilha de
                dados.

    - **montador**:
        - As tarefas do montador forma modularizadas em funções internas.
        - Agora o montador é capaz de manipular *labels*, de tal forma que
        *jumps* possam ser executados com *labels*.
        - A impressão das instruções foi adapdata para o novo formado de
        `OPERANDO`.

********************************************************************************
********************************************************************************

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
