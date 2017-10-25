#include <stdio.h>
#include <stdlib.h>
#include "vetor.h"

Vetor soma_vet(Vetor v1, Vetor v2) {
    Vetor res;
    
    res.x = v1.x + v2.x;
    res.y = v1.y + v2.y;

    return res;
}
