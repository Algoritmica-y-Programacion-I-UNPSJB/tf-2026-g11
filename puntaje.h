#ifndef PUNTAJE_H
#define PUNTAJE_H

#define MAX_NOMBRE 50

// Estructura datos jugador
typedef struct {
    char nombre[MAX_NOMBRE];
    int saldo; // Saldo restante = puntaje final
} Jugador;

// Prototipos de funciones
void guardar_puntaje(const char *nombre_archivo, Jugador j);
void mostrar_puntajes(const char *nombre_archivo);

#endif