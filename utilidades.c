#include <stdio.h>
#include <string.h>
#include "utilidades.h"

void limpiar_buffer_entrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int pedir_verificar_nombre(Jugador *jugador) {
    printf("Ingrese su nombre de usuario (maximo %d caracteres): ", MAX_NOMBRE - 1);

    if (fgets(jugador->nombre, MAX_NOMBRE, stdin) == NULL) {
        printf("\n ERROR: No se pudo leer el nombre.\n");
        return 1;
    }

    int largo_nombre = strcspn(jugador->nombre, "\n");
    
    if (jugador->nombre[largo_nombre] == '\n') {  
        jugador->nombre[largo_nombre] = '\0';
    } else {
        int caracter = getchar();
        if (caracter != '\n' && caracter != EOF) {
            while (caracter != '\n' && caracter != EOF) {
                caracter = getchar();
            }
            printf("ERROR: El nombre supera el maximo de %d caracteres.\n", MAX_NOMBRE - 1);
            return 1;
        }
    }

    largo_nombre = strlen(jugador->nombre) - 1; 
    while (largo_nombre >= 0 && jugador->nombre[largo_nombre] == ' ') {
        jugador->nombre[largo_nombre] = '\0';
        largo_nombre--;
    }

    int inicio = 0; 
    while (jugador->nombre[inicio] == ' ') {
        inicio++;
    }
    if (inicio > 0) {
        int k = 0;
        while (jugador->nombre[inicio] != '\0') {
            jugador->nombre[k++] = jugador->nombre[inicio++];
        }
        jugador->nombre[k] = '\0';
    }

    if (jugador->nombre[0] == '\0') { 
        printf("ERROR: El nombre no puede estar vacio ni contener solo espacios.\n");
        return 1;
    }

    return 0;
}

int obtener_opcion_valida(void) {
    int opcion;
    int resultado;
    printf("Seleccione una opcion: ");
    do {
        resultado = scanf("%d", &opcion); 

        if (resultado != 1) {
            printf("\nERROR: Entrada invalida. Por favor, ingrese un numero.\n");

            int caracter;
            while ((caracter = getchar()) != '\n' && caracter != EOF);

            if (caracter == EOF) { 
                return 1; 
            }
            printf("Seleccione una opcion: ");
        }

    } while (resultado != 1);
    return opcion;
}