#include <stdio.h>
#include "puntaje.h"
#include <errno.h>

int guardar_puntaje(const char *nombre_archivo, Jugador j) {
    if (nombre_archivo == NULL) {
        fprintf(stderr, "ERROR: El nombre del archivo es nulo.\n");
        return 1;
    }

    FILE *archivo = fopen(nombre_archivo, "ab");
    if (archivo == NULL) {
        printf("ERROR: No se pudo abrir o crear el archivo de puntajes.\n");
        return 1;
    }

    if (fwrite(&j, sizeof(Jugador), 1, archivo) != 1) {
        printf("ERROR: No se pudo guardar el puntaje correctamente en el archivo.\n");
        if (errno == ENOSPC) {
            printf("El disco está lleno.\n");
        }
        fclose(archivo);
        return 1;
    }

    if (fclose(archivo) != 0) {
        printf("ERROR: Hubo un problema al cerrar el archivo de puntajes.\n");
        return 1;
    }

    return 0;
}

int mostrar_puntajes(const char *nombre_archivo) {
    if (nombre_archivo == NULL) {
        fprintf(stderr, "ERROR: El nombre del archivo es nulo.\n");
        return 1; 
    }

    FILE *archivo = fopen(nombre_archivo, "rb");
    if (archivo == NULL) {
        if (errno == ENOENT) { //Archivo no encontrado
            printf("\nAún no hay registros de puntajes anteriores.\n");
            return 0; 
        } else if (errno == EACCES) {
            printf("ERROR: El archivo existe pero no tienes permisos de lectura.\n");
            return 1;
        } else {
            printf("ERROR: Fallo al abrir el archivo de lectura");
            return 1;
        }
    }

    Jugador j;
    printf("\n========================================\n");
    printf("         HISTORIAL DE PUNTAJES          \n");
    printf("========================================\n");
    printf("%-30s | %s\n", "JUGADOR", "PUNTAJE/SALDO");
    printf("----------------------------------------\n");

    while (fread(&j, sizeof(Jugador), 1, archivo) == 1) {
        printf("%-30s | %d\n", j.nombre, j.saldo);
    }
    printf("========================================\n");

    if (ferror(archivo)) {
        printf("ERROR: Ocurrió un fallo físico o corrupción al leer el archivo.\n");
        fclose(archivo);
    return 1;
    }

    if (fclose(archivo) != 0) {
        printf("ERROR: Hubo un problema al cerrar el archivo de lectura.\n");
        return 1;
    }

    return 0; 
}