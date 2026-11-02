#include <stdio.h>
#include <string.h>
#include "puntaje.h"
#include "utilidades.h" // Aquí mudamos las funciones de validación

int main() {
    Jugador jugador;
    const char *archivo_bin = "puntaje.dat";
    int opcion; 

    printf("=========================================\n");
    printf("   ¡BIENVENIDO A LA RULETA DE CASINO!    \n");
    printf("=========================================\n");

    // Bucle para pedir y verificar el nombre hasta que sea válido
    do {
        // La función ahora vive en utilidades.c
    } while (pedir_verificar_nombre(&jugador) == 1);

    printf("¡Hola, %s! Bienvenido a nuestra ruleta.\n", jugador.nombre);
    jugador.saldo = 1000; 
    imprimir_reglas(&jugador);

    // Menú principal del juego
    do {
        mostrar_menu(&jugador);
        opcion = obtener_opcion_valida(); // También vive en utilidades.c

        switch (opcion) {
            case 1:
                printf("\nSaliendo del programa...\n");
                if (guardar_puntaje(archivo_bin, jugador) != 0) {
                    printf("ADVERTENCIA: No se pudo respaldar tu puntaje actual.\n");
                }
                mostrar_puntajes(archivo_bin);
                break;
            case 2:
                // girar(&jugador); // Aquí conectarán las apuestas y la ruleta
                break;
            case 3:
                // limpiar_pano(); 
                break;
            case 4:
                // repetir_apuesta();
                break;
            default:
                printf("ERROR: Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 1);

    return 0;
}

// Funciones visuales rápidas que pueden quedarse acá o ir a utilidades:
void imprimir_reglas(Jugador *jugador) {
    printf("\n--- REGLAS DEL JUEGO ---\n");
    printf("1. Comienzas con un saldo inicial de $%d.\n", jugador->saldo);
    printf("2. Puedes realizar apuestas a números plenos, color, par/impar, etc.\n");
    printf("3. Si tu saldo llega a 0, la partida termina.\n");
    printf("4. Puedes retirarte en cualquier momento guardando tu puntaje.\n");
    printf("------------------------\n\n");
}

void mostrar_menu(Jugador *jugador) {
    printf("\n--- MENU PRINCIPAL (%s | Saldo: %d) ---\n", jugador->nombre, jugador->saldo);
    printf("1. Salir\n");
    printf("2. Girar\n");
    printf("3. Limpiar pano\n");
    printf("4. Repetir apuesta\n");
}