#ifndef ACAO_H
#define ACAO_H

/* Direção e sentido de ação */
typedef enum {
    A3_ = -3,
    A2_,
    A1_,
    A1 = 1,
    A2,
    A3
} Direcao;

/* Tipo de ação */
typedef enum {
    MOV,
    ATK,
    GET,
    PEG,
    DEP
} TipoAc;

/* Ação */
typedef struct {
    TipoAc t;
    Direcao d;
} Acao;

#endif
