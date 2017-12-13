#ifndef CELULA_H
#define CELULA_H

#define MAX_CRYSTAL 10

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
    struct Robo *r;
    struct Base *b;
    short int oc;
} Celula;

Celula *cria_celula(Terreno t, short int c);
void destroi_celula(Celula *cel);
char *toString_celula(Celula *cel);

#endif
