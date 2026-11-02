#ifndef UTILIDADES_H
#define UTILIDADES_H

#include "puntaje.h" // Necesita conocer la estructura Jugador

void limpiar_buffer_entrada(void);
int pedir_verificar_nombre(Jugador *jugador);
int obtener_opcion_valida(void);

#endif