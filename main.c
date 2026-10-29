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

    // Pedir el nombre al usuario
    printf("Ingrese su nombre de usuario: ");
    if (fgets(jugador.nombre, MAX_NOMBRE, stdin) != NULL) {
    jugador.nombre[strcspn(jugador.nombre, "\n")] = '\0';
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
            // Limpiar buffer de entrada en caso de error
            while (getchar() != '\n');
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