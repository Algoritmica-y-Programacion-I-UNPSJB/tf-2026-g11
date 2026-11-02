#ifndef APUESTAS_H
#define APUESTAS_H

#include <stddef.h>
#include "puntaje.h"
#include "ruleta.h"

// Tipos de apuestas permitidas en el juego
typedef enum {
    APUESTA_PLENO,    // Un número exacto (0 a 36)
    APUESTA_COLOR,    // Rojo (1) o Negro (2)
    APUESTA_PARIDAD   // Par (1) o Impar (2)
} TipoApuesta;

// Estructura que almacena una apuesta de la jugada actual
typedef struct {
    TipoApuesta tipo;
    int valor_elegido; // El número, color o paridad que eligió el usuario
    int monto;         // Dinero que arriesga en esta jugada
} Apuesta;

// Reúne todas las apuestas antes de que el llamador realice un único giro.
// El llamador debe liberar *apuestas con free() cuando termine de usarlas.
int realizar_apuestas(Jugador *jugador, Apuesta **apuestas, size_t *cantidad);
int evaluar_ganancia(Apuesta apuesta, const CasillaRuleta *casilla_ganadora);

#endif