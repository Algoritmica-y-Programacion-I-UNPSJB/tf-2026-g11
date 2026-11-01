#ifndef RULETA_H
#define RULETA_H
#define MAX_NUM_RULETA 37

typedef enum {
    VERDE,
    ROJO,
    NEGRO
} ColorRuleta;

typedef enum {
    NINGUNA_PARIDAD,
    PAR,
    IMPAR
} ParidadRuleta;

typedef struct {
    int numero;
    ColorRuleta color;
    ParidadRuleta paridad;
    int docena; 
    int columna;
} CasillaRuleta;

//PROTOTIPOS 
const CasillaRuleta* obtener_propiedad_casilla(int numero);

#endif