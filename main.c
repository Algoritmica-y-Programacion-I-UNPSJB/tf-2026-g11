#include <stdio.h>

int main() {
    // Variables definidas para el juego
    char nombre_jugador[50]; 
    int saldo_inicial = 1000; 

    // Mensaje de bienvenida para el jugador (y solicitud de su nombre)
    printf("=========================================\n");
    printf("   ¡BIENVENIDO A LA RULETA DE CASINO!    \n");
    printf("=========================================\n");
    printf("Por favor, ingresa tu nombre: ");
    scanf("%49s", nombre_jugador);
    
    printf("¡Hola, %s! Bienvenido a nuestra ruleta.\n", nombre_jugador);

    printf("\n--- REGLAS DEL JUEGO ---\n");
    printf("1. Comienzas con un saldo inicial de $%d.\n", saldo_inicial);
    printf("2. Puedes realizar apuestas a números plenos, color(rojo/negro/verde), par/impar, etc.\n");
    printf("3. Si tu saldo llega a 0, la partida termina.\n");
    printf("4. Puedes retirarte en cualquier momento guardando tu puntaje.\n");
    printf("------------------------\n\n");

    return 0;
}