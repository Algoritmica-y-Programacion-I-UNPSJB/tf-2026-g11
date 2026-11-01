#ifndef MAIN_H
#define MAIN_H
#include "puntaje.h"

// Prototipos de las acciones del juego (las desarrollarás tú más adelante)
int pedir_verificar_nombre(Jugador *j);
void imprimir_reglas(Jugador *j);
void mostrar_menu(Jugador *j);
int obtener_opcion_valida(void);
void girar(Jugador *j);
void limpiar_pano(void);
void repetir_apuesta(void);

#endif
