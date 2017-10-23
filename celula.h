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
typedef struct Celula {
    Terreno t;
    short int c;
    short int oc;
} Celula;

Celula *cria_celula(Terreno tr, short int cr, short int oc);
void destroi_celula(Celula *cel);
char *toString_celula(Celula cel);

#endif
