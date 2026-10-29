#include <stdio.h>
#include <errno.h>
#include "puntaje.h"

// Guarda la estructura del jugador al final del archivo binario
void guardar_puntaje(const char *nombre_archivo, Jugador j) {
    if (nombre_archivo == NULL) {
        fprintf(stderr, "Error: el nombre del archivo de puntajes es nulo.\n");
        return;
    }

    FILE *archivo = fopen(nombre_archivo, "ab");
    if (archivo == NULL) {
        perror("Error al abrir el archivo de puntajes");
        return;
    }

    if (fwrite(&j, sizeof(Jugador), 1, archivo) != 1) {
        perror("Error al guardar el puntaje");
    }
    if (fclose(archivo) != 0) {
        perror("Error al cerrar el archivo de puntajes");
    }
}

// Lee y muestra todos los registros guardados en el archivo binario
void mostrar_puntajes(const char *nombre_archivo) {
    if (nombre_archivo == NULL) {
        fprintf(stderr, "Error: el nombre del archivo de puntajes es nulo.\n");
        return;
    }

    FILE *archivo = fopen(nombre_archivo, "rb");
    if (archivo == NULL) {
        if (errno == ENOENT) {
            printf("\nAún no hay registros de puntajes anteriores.\n");
        } else {
            perror("Error al abrir el archivo de puntajes");
        }
        return;
    }

    Jugador j;
    printf("\n========================================\n");
    printf("         HISTORIAL DE PUNTAJES          \n");
    printf("========================================\n");
    printf("%-30s | %s\n", "JUGADOR", "PUNTAJE/SALDO");
    printf("----------------------------------------\n");

    while (1) {
        size_t bytes_leidos = fread(&j, 1, sizeof(Jugador), archivo);
        if (bytes_leidos == sizeof(Jugador)) {
            printf("%-30s | %d\n", j.nombre, j.saldo);
        } else if (ferror(archivo)) {
            perror("Error al leer el archivo de puntajes");
            break;
        } else if (bytes_leidos != 0) {
            fprintf(stderr, "Error: registro de puntaje incompleto.\n");
            break;
        } else {
            break;
        }
    }
    printf("========================================\n");

    if (fclose(archivo) != 0) {
        perror("Error al cerrar el archivo de puntajes");
    }
}