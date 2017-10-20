#ifndef CELULA_H
#define CELULA_H

/* Tipo de terreno */
typedef enum {
    ESTRADA,
    GRAMA,
    MONTANHA,
    RIO,
    BASE
} Terreno;

/* Célula */
typedef struct {
    Terreno terreno;
    short int cristais;
    short int ocupado;
} Celula;

#endif
