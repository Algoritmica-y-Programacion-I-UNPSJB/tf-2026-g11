#include <stdio.h>
#include "ruleta.h"

static const CasillaRuleta TABLA_RULETA[MAX_NUM_RULETA] = { //num, color, paridad, decena, columna
    { 0,   VERDE,         NINGUNA_PARIDAD,  0,      0 },
    { 1,   ROJO,          IMPAR,            1,      1 },
    { 2,   NEGRO,         PAR,              1,      2 },
    { 3,   ROJO,          IMPAR,            1,      3 },
    { 4,   NEGRO,         PAR,              1,      1 },
    { 5,   ROJO,          IMPAR,            1,      2 },
    { 6,   NEGRO,         PAR,              1,      3 },
    { 7,   ROJO,          IMPAR,            1,      1 },
    { 8,   NEGRO,         PAR,              1,      2 },
    { 9,   ROJO,          IMPAR,            1,      3 },
    { 10,  NEGRO,         PAR,              1,      1 },
    { 11,  NEGRO,         IMPAR,            1,      2 },
    { 12,  ROJO,          PAR,              1,      3 },
    { 13,  NEGRO,         IMPAR,            2,      1 },
    { 14,  ROJO,          PAR,              2,      2 },
    { 15,  NEGRO,         IMPAR,            2,      3 },
    { 16,  ROJO,          PAR,              2,      1 },
    { 17,  NEGRO,         IMPAR,            2,      2 },
    { 18,  ROJO,          PAR,              2,      3 },
    { 19,  ROJO,          IMPAR,            2,      1 },
    { 20,  NEGRO,         PAR,              2,      2 },
    { 21,  ROJO,          IMPAR,            2,      3 },
    { 22,  NEGRO,         PAR,              2,      1 },
    { 23,  ROJO,          IMPAR,            2,      2 },
    { 24,  NEGRO,         PAR,              2,      3 },
    { 25,  ROJO,          IMPAR,            3,      1 },
    { 26,  NEGRO,         PAR,              3,      2 },
    { 27,  ROJO,          IMPAR,            3,      3 },
    { 28,  NEGRO,         PAR,              3,      1 },
    { 29,  NEGRO,         IMPAR,            3,      2 },
    { 30,  ROJO,          PAR,              3,      3 },
    { 31,  NEGRO,         IMPAR,            3,      1 },
    { 32,  ROJO,          PAR,              3,      2 },
    { 33,  ROJO,          IMPAR,            3,      3 },
    { 34,  NEGRO,         PAR,              3,      1 },
    { 35,  ROJO,          IMPAR,            3,      2 },
    { 36,  NEGRO,         PAR,              3,      3 }
};

const CasillaRuleta* obtener_propiedad_casilla(int numero) { //WIP
    if (numero < 0 || numero > 36) {
        fprintf(stderr, "ERROR: Número fuera del rango de la ruleta (0-36).\n");
        return NULL;
    }

    return &TABLA_RULETA[numero]; //WIP
}