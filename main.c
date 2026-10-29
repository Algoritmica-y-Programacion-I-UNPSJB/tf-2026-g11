#include <stdio.h>
#include <string.h>
#include "puntaje.h"
#include "main.h"

int main() {
    Jugador jugador;
    int opcion;
    const char *archivo_bin = "puntaje.dat";
    jugador.saldo = 1000; 

    printf("=========================================\n");
    printf("   ¡BIENVENIDO A LA RULETA DE CASINO!    \n");
    printf("=========================================\n");

    printf("Ingrese su nombre de usuario (maximo %d caracteres): ", MAX_NOMBRE - 1);
    if (fgets(jugador.nombre, MAX_NOMBRE, stdin) == NULL) {
        printf("\nNo se pudo leer el nombre.\n");
        return 1;
    }

    size_t largo_nombre = strcspn(jugador.nombre, "\n");
    // Verifica si el nombre ingresado es demasiado largo
    if (jugador.nombre[largo_nombre] == '\n') {
        jugador.nombre[largo_nombre] = '\0';
    } else {
        int caracter_siguiente = getchar();
        if (caracter_siguiente != '\n' && caracter_siguiente != EOF) {
            while (caracter_siguiente != '\n' && caracter_siguiente != EOF) {
                caracter_siguiente = getchar();
            }
            printf("El nombre supera el maximo de %d caracteres.\n", MAX_NOMBRE - 1);
            return 1;
        }
    }

    printf("¡Hola, %s! Bienvenido a nuestra ruleta.\n", jugador.nombre);
    // REGLAS
    printf("\n--- REGLAS DEL JUEGO ---\n");
    printf("1. Comienzas con un saldo inicial de $%d.\n", jugador.saldo);
    printf("2. Puedes realizar apuestas a números plenos, color (rojo/negro/verde), par/impar, etc.\n");
    printf("3. Si tu saldo llega a 0, la partida termina.\n");
    printf("4. Puedes retirarte en cualquier momento guardando tu puntaje.\n");
    printf("------------------------\n\n");

    // MENU
    do {
        printf("\n--- MENU PRINCIPAL (%s | Saldo: %d) ---\n", jugador.nombre, jugador.saldo);
        printf("1. Salir\n");
        printf("2. Girar\n");
        printf("3. Limpiar paño\n");
        printf("4. Repetir apuesta\n");
        printf("Seleccione una opcion: ");
        
        if (scanf("%d", &opcion) != 1) { //VERIFICAR 
            printf("Entrada invalida. Por favor, ingrese un numero.\n");
            int caracter;
            while ((caracter = getchar()) != '\n' && caracter != EOF) {
            }
            if (caracter == EOF) {
                break;
            }
            continue;
        }

        switch (opcion) {
            case 1:
                printf("\nSaliendo del programa...\n");
                guardar_puntaje(archivo_bin, jugador); //WIP
                mostrar_puntajes(archivo_bin); //WIP
                break;
            case 2:
                girar(&jugador); //WIP
                break;
            case 3:
                limpiar_pano(); //WIPZ
                break;
            case 4:
                repetir_apuesta();//WIP
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 1);

    return 0;
}

// IMPLEMENTACIONES:

void girar(Jugador *j) {
    printf("*gira*");
}

void limpiar_pano() {
    printf("*limpia paño*");
}

void repetir_apuesta() {
    printf("*repite apuesta*");
}