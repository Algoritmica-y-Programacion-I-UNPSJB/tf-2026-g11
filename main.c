#include <stdio.h>
#include <string.h>
#include "puntaje.h"
#include "main.h"

int main() {
    Jugador jugador;
    const char *archivo_bin = "puntaje.dat";

    printf("=========================================\n");
    printf("   ¡BIENVENIDO A LA RULETA DE CASINO!    \n");
    printf("=========================================\n");

    do {
    } while (pedir_verificar_nombre(&jugador) == 1);
    printf("¡Hola, %s! Bienvenido a nuestra ruleta.\n", jugador.nombre);
    jugador.saldo = 1000; 
    imprimir_reglas(&jugador);

    int opcion; // MENU
    do {
        mostrar_menu(&jugador);
        opcion = obtener_opcion_valida();

        switch (opcion) {
           case 1:
                printf("\nSaliendo del programa...\n");
                if (guardar_puntaje(archivo_bin, jugador) != 0) {
                    printf("ADVERTENCIA: No se pudo respaldar tu puntaje actual.\n");
                }
                mostrar_puntajes(archivo_bin);
                break;
            case 2:
                girar(&jugador); //WIP
                break;
            case 3:
                limpiar_pano(); //WIP
                break;
            case 4:
                repetir_apuesta();//WIP
                break;
            default:
                printf("ERROR: Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 1);

    return 0;
}

// IMPLEMENTACIONES:

int pedir_verificar_nombre(Jugador *jugador){
    printf("Ingrese su nombre de usuario (maximo %d caracteres): ", MAX_NOMBRE - 1);

    if (fgets(jugador->nombre, MAX_NOMBRE, stdin) == NULL) {
        printf("\n ERROR: No se pudo leer el nombre.\n");
        return 1;
    }

    int largo_nombre = strcspn(jugador->nombre, "\n");
    
    if (jugador->nombre[largo_nombre] == '\n') {  //Verificar longitud cadena.
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

    largo_nombre = strlen(jugador->nombre) - 1; //Borra los espacios del final
    while (largo_nombre >= 0 && jugador->nombre[largo_nombre] == ' ') {
        jugador->nombre[largo_nombre] = '\0';
        largo_nombre--;
    }

    int inicio = 0; //Borra los espacios del principio y desplaza
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

    if (jugador->nombre[0] == '\0') { //Verificar cadena vacia
        printf("ERROR: El nombre no puede estar vacio ni contener solo espacios.\n");
        return 1;
    }

    return 0;

}

void imprimir_reglas(Jugador *jugador){
    printf("\n--- REGLAS DEL JUEGO ---\n");
    printf("1. Comienzas con un saldo inicial de $%d.\n", jugador->saldo);
    printf("2. Puedes realizar apuestas a números plenos, color (rojo/negro/verde), par/impar, etc.\n");
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

int obtener_opcion_valida(void) {
    int opcion;
    int resultado;
    printf("Seleccione una opcion: ");
    do {
        resultado = scanf("%d", &opcion); //scanf = 1 si recibió el formato correcto.

        if (resultado != 1) {
            printf("\nERROR: Entrada invalida. Por favor, ingrese un numero.\n");

            int caracter;
            while ((caracter = getchar()) != '\n' && caracter != EOF);

            if (caracter == EOF) { //Salida Ctrl + Z
                return 1; 
            }
            printf("Seleccione una opcion: ");
        }

    } while (resultado != 1);
    return opcion;
}

void girar(Jugador *j) {
    printf("*gira*");
}

void limpiar_pano() {
    printf("*limpia paño*");
}

void repetir_apuesta() {
    printf("*repite apuesta*");
}