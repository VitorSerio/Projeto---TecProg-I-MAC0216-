## MAC0216 - Técnicas de Programação I
# Batalha de Robôs - Projeto

Data: 22/10/2017

**Autores**:

    Rafael Augusto Brandão        (7700827)
    Vitor Barbosa Sério           (7627627)
    Vivian do Amaral Daud Horing  (8125014)


### FASE 4

**NOVIDADES**:

- Dos arquivos fornecidos, **instr.h**, **pilha.h** e **pilha.c** foram total-
mente substituídos pelos que nós criamos nas fases anteriores.
- **maq.c** e **maq.h** foram ligeiramente adaptados para a nossa implementação.
- Os outros arquivos **.h** e **.c** criados nas fases anteriores foram
adicionados.

- **compila.l**:
    - Adicionados novos tokens:
        - `AC`:
            - Quando é lida a palavra `acao`.
            - Reconhece quando uma ação será executada.
        - `PONTO`:
            - Quando é lido um caractere `.`.
            - Serve somente para poder acessar atributos de variáveis.

- **compila.y**:
    - Adição dos tokens `PONTO` e `AC`.
    - Regras novas em:
        - `Expr`:
            - `SUBt NUMt`:
                - Reconhece inteiros negativos e os diferencia de subtração.
            - `AC OPEN Expr SEP Expr CLOSE`:
                - Reconhece uma ação. Dessa forma, para o robô executar uma ação
                basta usar `acao(t, d)`, onde `t` e `d` são inteiros represen-
                tando, respectivamente, o tipo da ação e a sua direção. Os
                valores de `t` e `d` seguem os valores para `TipoAc` e `Direcao`
                definidos na Fase 2.
            - `ID PONTO NUMt`:
                - Foi descomentada, na verdade.
                - Serve para obter atributos de uma variável (geralmente
                operandos do tipo `CELULA`).


********************************************************************************
********************************************************************************

### FASE 2
Data: 22/10/2017

**NOVIDADES**:

- Todos os arquivos **.h** receberam *inclusion guards*, para usar dependência
circular.
- Todos os arquivos **.c** receberam implementações das funções `Erro` e `Fatal`
para gerenciamento de erros.
- Todas as funções que liberam espaço alocado para alguma `struct` agora também
ajustam os valores apontados por seus ponteiros como `NULL`.

- **Makefile**:
    - Regra *default*:
        - Execução: `make` ou `make testes`.
        - Requer: **main.o**, **arena.o**, **exercito.o**, **robo.o**,
        **maq.o**, **pilha.o**, **operando.o**, **celula.o** e **acao.o**.
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
                    - `./testes -ac`:
                        - Executa testes nas funções em **acao.c**.
                    - `./testes -cel`:
                        - Executa testes nas funções em **celula.c**.
    - Outras regras:
        - `make motor` ou `make motor prog=nome_do_programa_em_Assembly`:
            - Requer: **montador.py**, **motor.c**, **arena.o**, **exercito.o**,
            **robo.o**, **maq.o**, **pilha.o**, **operando.o**, **celula.o** e
            **acao.o**.
            - `prog` é uma variável que assume o nome do programa em Assembly.
            Seu valor padrão é simplesmente 'prog'. Então, para rodar com `make
            motor` é necessário que haja um programa em Assembly
            chamado **prog** no mesmo diretório.
            - Para criar **motor** diversas vezes somente mudando o programa em
            Assembly usado é necessário usar `make clean`, antes de gerar um
            novo **motor**.
            - Cria o arquivo:
                - **motor**:
                    - Tipo: Executável.
                    - Testa se o arquivo gerado por **montador.py** está
                    funcionando.
                    - Acaba testando, por consequência, as instruções definidas
                    em **maq.c**.
                    - Execução: `./motor`
        - `make motor.c`:
            - Regra predominantemente auxiliar de `make motor`.
            - Pode ser usado para verificar o funcionamento de **montador.py**.
            - Cria o arquivo:
                - **motor.c**:
                    - Tipo: Source
                    - Programa em C, gerado por **montador.py**, que simula o
                    funcionamento de uma máquina.
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
                    - *INF*:
                        - Pede os dados de uma célula adjacente.
                        - Valor: 2
                    - *PEG*:
                        - Pega um cristal.
                        - Valor: 3
                    - *DEP*:
                        - Deposita um cristal numa base.
                        - Valor: 4
            - `Acao` e `struct Acao`:
                - Tipo: `struct`
                - Representa uma ação executada por um robô.
                - Sempre necessita de chamadas ao sistema.
                - Contém os valores:
                    - *t*:
                        - Tipo: `TipoAc`
                        - Representa o tipo da ação.
                    - *d*:
                        - Tipo: `Direcao`
                        - Representa a direção da ação.
        - Declara a função:
            - `toString_acao`:
                - Retorna uma string que representa uma `Acao`.
                - Recebe:
                    - `Acao ac`:
                        - `Acao` que será representada.
                - Retorna:
                    - `char*`
                        - String que representa a `Acao`.
    - **acao.c**:
        - Implementa a função `toString_acao`.
            - É importante observar que essa função aloca espaço na memória para
            o ponteiro `char*`, precisando que essa memória seja liberada com a
            função `free` eventualmente.
        - Outras funções são auxiliares.

    - **celula.h**:
        - Define:
            - *MAX_CRYSTAL*:
                - A quantidade máxima de cristais por célula.
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
            - `Celula` e `struct Celula`:
                - Tipo: `struct`
                - Representa os dados de uma célula do mapa.
                - Contém os valores:
                    - *t*:
                        - Tipo: `Terreno`
                        - Representa qual o tipo de terreno da célula.
                    - *c*:
                        - Tipo: `short int`
                        - Representa a quantidade de cristais presente na
                        célula.
                    - *r*:
                        - Tipo: `struct Robo*`
                        - Aponta para o robô que estiver ocupando a célula, se
                        houver.
                    - *b*:
                        - Tipo: `struct Base*`
                        - Aponta para a base que estiver ocupando a célula, se
                        houver.
                    - *oc*:
                        - Tipo: `short int`
                        - Representa se a célula está ocupada por um robô ou uma
                        base.
                        - Vale 0, se não estiver ocupada e 1, se estiver.
        - Declara as funções:
            - `cria_celula`:
                - Função construtora do tipo `Celula`.
                - Recebe:
                    - `Terreno t`:
                        - O terreno da célula criada.
                    - `short int c`:
                        - A quantidade de cristais na célula criada.
                - Retorna:
                    - `Celula*` com os parâmetros dados e considerada como
                    desocupada (`oc = 0`).
            - `destroi_celula`:
                - Libera a memória alocada para uma `Célula*`.
                - Recebe:
                    - `Celula *cel`:
                        - `Celula*` para ser 'desfeita'.
                - Não possui `return`.
            - `toString_celula`:
                - Retorna uma string que representa uma `Celula`.
                - Recebe:
                    - `Celula cel`
                        - `Celula` que será representada.
                - Retorna:
                    - `char*`
                        - String que representa a `Celula`.
    - **celula.c**:
        - Implementa as funções `cria_celula`, `destroi_celula` e
        `toString_celula`.
            - É importante observar que `toString_celula` aloca espaço na
            memória para o ponteiro `char*`, precisando que essa memória seja
            liberada com a função `free` eventualmente.
        - Outras funções são auxiliares.

    - **operando.h**:
        - Define:
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
            - `OPERANDO` e `struct OPERANDO`:
                - Tipo: `struct`
                - Contém os valores:
                    - *t*:
                        - Tipo: `Tipo`
                        - Representa o tipo do operando.
                    - *val*:
                        - Tipo: `union`.
                        - Representa o valor do operando.
                        - Pode ter os valores:
                            - *n*:
                                - Tipo: `int`
                                - Referente a inteiros literais (`t = NUM`).
                            - *ac*:
                                - Tipo: `Acao`
                                - Referente a ações (`t = ACAO`).
                            - *cel*:
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
        - Implementa a função `toString_operando`:
            - É importante observar que essa função aloca espaço na memória para
            o ponteiro `char*`, precisando que essa memória seja liberada com a
            função `free` eventualmente.
        - Outras funções são auxiliares.

    - **vetor.h**:
        - Define:
            - `Vetor`:
                - Representa um vetor bidimensional.
                - Usado para determinar posições de objetos na matriz e direções
                de ações.
                - Tem os valores:
                    - *x*:
                        - Tipo: `int`
                        - Valor da direção horizontal.
                    - *y*:
                        - Tipo: `int`
                        - Valor da direção vertical.
        - Declara a função:
            - `soma_vet`:
                - Soma dois vetores, gerando um terceiro vetor.
                - Recebe:
                    - `Vetor v1`
                    - `Vetor v2`
                - Retorna:
                    - `Vetor`

    - **vetor.c**:
        - Implementa a função:
            - `soma_vet`

    - **robo.h**:
        - Define:
            - *R_MAX_HP*:
                - Representa a vida máxima de um robô.
            - `Robo` e `struct Robo`:
                - Representa um robô de um exército.
                - Contém os valores:
                    - *m*:
                        - Tipo: `Maquina*`
                        - É a máquina virtual do robô, que executará o seu
                        próprio programa.
                    - *pos*:
                        - Tipo: `Vetor`
                        - Representa a posição do robô na matriz quadrada (que
                        representa a hexagonal).
                    - *hp*:
                        - Tipo: `short int`
                        - Representa a vida atual do robô.
                    - *c*:
                        - Tipo: `short int`
                        - Representa a quantidade de cristais que está sendo
                        carregada pelo robô.
                    - *id*:
                        - Tipo: `short int`
                        - Representa a posição do robô, dentro do exército.
                    - *e*:
                        - Tipo: `struct Exercito*`
                        - Representa a qual exército o robô pertence.
        - Declara as funções:
            - `cria_robo`:
                - Função construtora do tipo `Robo`.
                - A máquina do do robô criado tem seu ponteiro *r* ajustado para
                o robô.
                - Recebe:
                    - `INSTR *p`:
                        - Programa a ser executado pelo robô.
                    - `Vetor pos`:
                        - A posição do robô na matriz.
                - Retorna:
                    - `Robo*` com os atributos dados contendo uma `Maquina*` com
                    o programa dado.
            - `destroi_robo`:
                - Libera a memória alocada para um `Robo*` e sua `Maquina*`.
                - Recebe:
                    - `Robo *r`:
                        - `Robo*` a ser 'desfeito'.
                - Não possui `return`.
            - `torca_prog`:
                - Troca o programa a ser executado por um robô.
                - 'Desfaz' a máquina atual e cria uma nova, com o programa
                dado.
                - Recebe:
                    - `INSTR *p`:
                        - O novo programa a ser dado pro robô.
                    - `Robo *r`:
                        - O robô que receberá o novo programa.
                - Não possui `return`.
            - `roda_robo`:
                - Executa uma determinada quantidade de instruções do programa
                de um robô.
                - Recebe:
                    - `Robo *r`:
                        - O robô cujo programa será executado.
                    - `int n`:
                        - Quantidade de instruções para ser executada.
                - Não possui `return`.
    - **robo.c**:
        - Implementa as funções `cria_robo`, `destroi_robo`, `troca_prog` e
        `roda_robo`.

    - **base.h**:
        - Define:
            - *B_MAX_HP*:
                - Define a vida máxima de uma base.
            - `Base` e `struct Base`:
                - Tipo: `struct`
                - Representa a base de um exército.
                - Contém os valores:
                    - *pos*:
                        - Tipo: `Vetor`
                        - Representa a posição da base na matriz quadrada (que
                        representa a hexagonal).
                    - *hp*:
                        - Tipo: `short int`
                        - Representa a vida atual de uma base.
                    - *e*:
                        - Tipo: `short int`
                        - Representa a qual exército a base pertence.

    - **exercito.h**:
        - Define:
            - *MAX_ROBO*:
                - Quantidade máxima de robôs por exército.
            - `Exercito` e `struct Exercito`:
                - Tipo: `struct`
                - Representa um exército (time) do jogo.
                - Contém os seguintes valores:
                    - *robos*:
                        - Tipo: `Robo**`
                        - Representa todos os robôs do exército.
                    - *b*:
                        - Tipo: `Base`
                        - Representa a base do exército.
                    - *tamanho*:
                        - Tipo: `short int`
                        - Representa a quantidade de robôs que o exército pode
                        ter.
                    - *robosCount*:
                        - Tipo: `short int`
                        - Representa a quantidade de robôs ativos no exército.
                    - *id*:
                        - Tipo: `short int`
                        - Identificação do exército em uma arena.
                    - *a*:
                        - Tipo: `struct Arena*`
                        - Representa a arena que contém o `Exercito`.
        - Declara as funções:
            - `cria_exercito`:
                - Função construtora do tipo `Exercito`.
                - Recebe:
                    - `Vetor bpos`:
                        - Posição da base do exército.
                    - `short int tam`:
                        - Tamanho que o exército pode ter.
                - Retorna:
                    - `Exercito*` com os atributos passados e o máximo de
                    `Robo*`s inicializados como `NULL`.
            - `destroi_exercito`:
                - Libera a memória alocada para um `Exercito*` e seus `Robo*`s.
                - Recebe:
                    - `Exercito *e`:
                        - `Exercito` a ser 'desfeito'.
                - Não possui `return`.
            - `adiciona_robo`:
                - Adiciona um robô a um exército, no primeiro espaço vazio
                disponível em *robos*.
                - O robô adicionado tem seu ponteiro *e* ajustado pro
                exército que o está recebendo e seu valor *id* ajustado para
                a posição em que ele está entrando em *robos*.
                - Recebe:
                    - `Exercito *e`:
                        - `Exercito` a ter um robô adicionado.
                    - `short int pos`:
                        - Posição onde o robô será adicionado no exército.
                    - `INSTR *p`:
                        - Programa do robô que será adicionado.
                - Gera aviso se o limite de robôs já tiver sido atingido.
                - Não possui `return`.
            - `remove_robo`:
                - Remove um robô de um exército na posição dada, liberando a
                memmória alocada para o mesmo.
                - Recebe:
                    - `Exercito *e`:
                        - `Exercito` a ser modificado.
                    - `short int pos`:
                        - Posição do robô que será removido.
                - Gera aviso, se a posição dada já estiver vazia.
                - Não possui `return`.
    - **exercito.c**:
        - Implementa as funções `cria_exercito`, `destroi_exercito`,
        `adiciona_robo` e `remove_robo`.

    - **arena.h**:
        - Define:
            - *MAX_TAMANHO*:
                - Tamanho máximo de um lado da matriz quadrada que representa
                o grid hexadonal.
            - *MAX_EXERCITOS*:
                - Quantidade máxima de exércitos por arena.
            - `Arena` e `struct Arena`:
                - Tipo: `struct`
                - Contém os seguintes valores:
                    - *exercitosCount*:
                        - Tipo: `short int`
                        - Quantidade de exércitos ativos na arena.
                    - *tamanho*:
                        - Tipo: `int`
                        - Tamanho da arena (matriz quadrada).
                    - *mapa*:
                        - Tipo: `Celula***`
                        - Representa o mapa da arena.
                    - *exercitos*:
                        - Tipo: `Exercito**`
                        - Exércitos da arena.
                    - *execucoes*:
                        - Quantidade de vezes que robôs executaram seus
                        programas (tempo).
        - Declara as funções:
            - `cria_arena`:
                - Função contrutora do tipo `Arena`.
                - Gera uma arena aleatória com tamanho dado.
                - Recebe:
                    - `int tam`:
                        - Tamanho do *mapa* da arena que será gerada.
                - Retorna:
                    - `Arena*` com o tamanho dado, mapa aleatório, sem exércitos
                    ativos (todos são inicializados como `NULL`).
            - `cria_arena_file`:
                - Função contrutora do tipo `Arena`.
                - Gera uma arena a partir de um arquivo.
                - Recebe:
                    - `FILE *fp`:
                        - Arquivo que será lido.
                - Retorna:
                    - `Arena*` com tamanho e mapa dados pelo arquivo e sem
                    exércitos ativos.
            - `destroi_arena`:
                - Libera a memória alocada para uma `Arena*` e todos os outros
                `struct`s contidos na mesma.
                - Recebe:
                    - `Arena *a`:
                        - `Arena` que será 'desfeita'.
                - Não possui `return`.
            - `Atualiza`:
                - Faz com que cada robô, de cada exército, execute uma mesma
                quantidade de instruções, por vez.
                - Atualiza o valor de *execucoes* para cada robô que executou o
                seu programa.
                - Recebe:
                    - `Arena *arena`:
                        - A arena que contém os exércitos.
                - Não possui `return`.
            - `InsereExercito`:
                - Adiciona um exército à arena, no primeiro espaço vazio de
                *exercitos*.
                - A posição no *mapa* onde ficará a base do exército novo é
                convertida para *BASE* com 0 cristais.
                - O exército adicionado tem seu ponteiro *a* ajustado para a
                arena, seu *id* ajustado para sua posição na arena e o valor
                *e* de sua base também é ajustado.
                - Recebe:
                    - `Arena *arena`:
                        - A arena que irá recebe o novo exército.
                    - `short int pos`:
                        - A posição do exército na arena (a posição no mapa é
                        pré-definida)
                    - `short int tam`:
                        - O tamanho do exército que será criado.
                - Não possui `return`.
            - `RemoveExercito`:
                - Remove um exército da arena, na posição dada.
                - A posição no *mapa* onde fica a base do exército que será
                removido é convertida para *ESTRADA* com o máximo de cristais.
                - Recebe:
                    - `Arena *arena`:
                        - Arena que terá o exército removido.
                    - `short int pos`:
                        - Posição do exército que será removido.
                - Não possui `return`.
            - `RemoveRobo`:
                - Remove um robô de um exército.
                - Recebe:
                    - `Robo *r`:
                        - Robô que será removido.
                - Não possui `return`.
            - `Sistema`:
                - Função responsável pela comunicação entre máquina e arena.
                - Recebe:
                    - `Maquina *m`:
                        - A máquina que está fazendo a solicitação.
                    - `OPERANDO op`:
                        - A instrução que a máquina está passando.
                        - Esse `OPERANDO` deve ser sempre do tipo *ACAO*.
                - Retorna:
                    - `OPERANDO` de acordo com a solicitação feita.
            - `imprime_mapa`:
                - Imprime os valores nas células do *mapa* de uma arena.
                - Recebe:
                    - `Arena *a`:
                        - A arena cujo mapa será impresso.
                - Não possui `return`.
    - **arena.c**:
        - Implementa as funções `cria_arena`, `cria_arena_file`,
        `destroi_arena`, `Atualiza`, `InsereExercito`, `RemoveExercito`,
        `RemoveRobo`, `Sistema` e `imprime_mapa`.

--------------------------------------------------------------------------------

- **_Modificados_** os arquivos:
    - **instr.h**:
        - Acrescentadas as instruções *ATR* e *SIS* a `OpCode`.
        - `OPERANDO` foi movido para um arquivo próprio (**operando.h**).

    - **maq.h**:
        - `Maquina`:
            - Também define `struct Maquina`.
            - Novo valor adicionado:
                - *r*:
                    - Tipo: `Robo*`
                    - Representa o robô ao qual a máquina pertence.
    - **maq.c**:
        - Todas as instruções foram adaptadas ao novo formato de `OPERANDO`.
        - Todas as funções foram adaptadas para o novo formato de `Maquina`.
        - As instruções *ADD*, *SUB*, *MUL*, *DIV*, *JIT*, *JIF*, *EQ*, *GT*,
        *GE*, *LT*, *LE*, *NE*, *STO* e *RCL* agora gerenciam possíveis erros.
        - Aprimoração das mensagens de erro:
            - Um label 'Erro' ou 'Aviso' são usados para sinalizar um erro
            fatal ou um erro mais simples, respectivamente.
        - Adicionadas as instruções *ATR* e *SIS* a `*CODES`.
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
            - *SIS*:
                - Faz solicitações ao sistema.
                - Recebe argumento de `Tipo t = ACAO`
                - A maioria das ações causa mudanças fora da máquina. Apenas
                *INF* é exceção, empilhando os dados de uma célula na pilha de
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
