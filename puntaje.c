#include <stdio.h>
#include "puntaje.h"

// Guarda la estructura del jugador al final del archivo binario
void guardar_puntaje(const char *nombre_archivo, Jugador j) {
    FILE *archivo = fopen("puntajes.dat", "ab"); // "ab" crea el archivo si no existe y añade al final
    if (archivo == NULL) {
        printf("Error: No se pudo abrir o crear el archivo de puntajes.\n");
        return;
    }

    fwrite(&j, sizeof(Jugador), 1, archivo);
    fclose(archivo);
}

// Lee y muestra todos los registros guardados en el archivo binario
void mostrar_puntajes(const char *nombre_archivo) {
    FILE *archivo = fopen("puntajes.dat", "rb"); // "rb" solo lectura binaria
    if (archivo == NULL) {
        printf("\nAún no hay registros de puntajes anteriores.\n");
        return;
    }

    Jugador j;
    printf("\n========================================\n");
    printf("         HISTORIAL DE PUNTAJES          \n");
    printf("========================================\n");
    printf("%-30s | %s\n", "JUGADOR", "PUNTAJE/SALDO");
    printf("----------------------------------------\n");

    // Lee struct por struct hasta llegar al final del archivo
    while (fread(&j, sizeof(Jugador), 1, archivo) == 1) {
        printf("%-30s | %d\n", j.nombre, j.saldo);
    }
    printf("========================================\n");

    fclose(archivo);
}