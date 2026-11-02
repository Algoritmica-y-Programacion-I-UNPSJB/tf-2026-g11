#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "apuestas.h"
#include "utilidades.h"

static const char *nombre_color(ColorRuleta color) {
    switch (color) {
        case VERDE:
            return "Verde";
        case ROJO:
            return "Rojo";
        case NEGRO:
            return "Negro";
        default:
            return "Desconocido";
    }
}

static const char *nombre_paridad(ParidadRuleta paridad) {
    switch (paridad) {
        case NINGUNA_PARIDAD:
            return "Sin paridad";
        case PAR:
            return "Par";
        case IMPAR:
            return "Impar";
        default:
            return "Desconocida";
    }
}

static int mostrar_datos_ruleta(void) {
    printf("\n--- NUMEROS DE LA RULETA ---\n");
    printf("%-8s %-10s %s\n", "Numero", "Color", "Paridad");

    for (int numero = 0; numero < MAX_NUM_RULETA; numero++) {
        const CasillaRuleta *casilla = obtener_propiedad_casilla(numero);
        if (casilla == NULL) {
            return 0;
        }

        printf("%-8d %-10s %s\n",
               casilla->numero,
               nombre_color(casilla->color),
               nombre_paridad(casilla->paridad));
    }

    return 1;
}

static int leer_entero(const char *mensaje, int *valor) {
    printf("%s", mensaje);
    if (scanf("%d", valor) != 1) {
        limpiar_buffer_entrada();
        return 0;
    }
    limpiar_buffer_entrada();
    return 1;
}

int realizar_apuestas(Jugador *jugador, Apuesta **apuestas, size_t *cantidad) {
    Apuesta *lista_apuestas = NULL;
    size_t cantidad_apuestas = 0;
    int saldo_restante;
    int continuar = 1;

    if (jugador == NULL || apuestas == NULL || cantidad == NULL) {
        printf("ERROR: Los datos del jugador o de las apuestas no son válidos.\n");
        return 0;
    }

    *apuestas = NULL;
    *cantidad = 0;

    printf("\n--- SECCION DE APUESTAS ---\n");
    printf("Tu saldo actual es: $%d\n", jugador->saldo);

    if (jugador->saldo <= 0) {
        printf("ERROR: No tienes saldo suficiente para realizar apuestas.\n");
        return 0;
    }

    if (!mostrar_datos_ruleta()) {
        return 0;
    }

    printf("\nCarga todas las apuestas que quieras antes del giro.\n");
    saldo_restante = jugador->saldo;

    while (continuar) {
        Apuesta nueva_apuesta;
        int opcion_tipo;

        printf("\nSaldo disponible para apostar: $%d\n", saldo_restante);
        if (!leer_entero("Ingrese el monto de esta apuesta: ", &nueva_apuesta.monto)) {
            printf("ERROR: Monto inválido.\n");
            free(lista_apuestas);
            return 0;
        }
        if (nueva_apuesta.monto <= 0 || nueva_apuesta.monto > saldo_restante) {
            printf("ERROR: El monto debe ser positivo y no superar el saldo disponible.\n");
            free(lista_apuestas);
            return 0;
        }

        printf("\nSeleccione el tipo de apuesta:\n");
        printf("0. Pleno (un número del 0 al 36)\n");
        printf("1. Color (1: Rojo, 2: Negro)\n");
        printf("2. Paridad (1: Par, 2: Impar)\n");
        if (!leer_entero("Opción: ", &opcion_tipo)) {
            printf("ERROR: Tipo de apuesta inválido.\n");
            free(lista_apuestas);
            return 0;
        }

        switch (opcion_tipo) {
            case 0:
                nueva_apuesta.tipo = APUESTA_PLENO;
                if (!leer_entero("Ingrese el número (0 a 36): ",
                                 &nueva_apuesta.valor_elegido) ||
                    nueva_apuesta.valor_elegido < 0 ||
                    nueva_apuesta.valor_elegido > 36) {
                    printf("ERROR: Número de ruleta inválido; debe estar entre 0 y 36.\n");
                    free(lista_apuestas);
                    return 0;
                }
                break;

            case 1:
                nueva_apuesta.tipo = APUESTA_COLOR;
                if (!leer_entero("Elija color (1: Rojo, 2: Negro): ",
                                 &nueva_apuesta.valor_elegido) ||
                    (nueva_apuesta.valor_elegido != ROJO &&
                     nueva_apuesta.valor_elegido != NEGRO)) {
                    printf("ERROR: El color debe ser 1 (rojo) o 2 (negro).\n");
                    free(lista_apuestas);
                    return 0;
                }
                break;

            case 2:
                nueva_apuesta.tipo = APUESTA_PARIDAD;
                if (!leer_entero("Elija paridad (1: Par, 2: Impar): ",
                                 &nueva_apuesta.valor_elegido) ||
                    (nueva_apuesta.valor_elegido != PAR &&
                     nueva_apuesta.valor_elegido != IMPAR)) {
                    printf("ERROR: La paridad debe ser 1 (par) o 2 (impar).\n");
                    free(lista_apuestas);
                    return 0;
                }
                break;

            default:
                printf("ERROR: Tipo de apuesta desconocido.\n");
                free(lista_apuestas);
                return 0;
        }

        int multiplicador = nueva_apuesta.tipo == APUESTA_PLENO ? 36 : 2;
        if (nueva_apuesta.monto > INT_MAX / multiplicador) {
            printf("ERROR: El monto es demasiado alto para calcular el premio.\n");
            free(lista_apuestas);
            return 0;
        }

        if (cantidad_apuestas >= (size_t)-1 / sizeof(*lista_apuestas)) {
            fprintf(stderr, "ERROR: Se alcanzó el límite de apuestas.\n");
            free(lista_apuestas);
            return 0;
        }

        Apuesta *nueva_lista = realloc(
            lista_apuestas, (cantidad_apuestas + 1) * sizeof(*lista_apuestas));
        if (nueva_lista == NULL) {
            fprintf(stderr, "ERROR: No hay memoria para guardar otra apuesta.\n");
            free(lista_apuestas);
            return 0;
        }
        lista_apuestas = nueva_lista;
        lista_apuestas[cantidad_apuestas++] = nueva_apuesta;
        saldo_restante -= nueva_apuesta.monto;

        if (saldo_restante == 0) {
            printf("Ya no quedan fichas disponibles para agregar apuestas.\n");
            break;
        }

        do {
            if (!leer_entero("¿Queres agregar otra apuesta antes del giro? (1: Sí, 0: No): ",
                             &continuar)) {
                printf("ERROR: Respuesta inválida.\n");
                free(lista_apuestas);
                return 0;
            }
            if (continuar != 0 && continuar != 1) {
                printf("Ingresa 1 para agregar otra apuesta o 0 para terminar.\n");
            }
        } while (continuar != 0 && continuar != 1);
    }

    jugador->saldo = saldo_restante;
    *apuestas = lista_apuestas;
    *cantidad = cantidad_apuestas;
    printf("\nSe cargaron %lu apuesta(s). Ahora se puede realizar un único giro.\n",
           (unsigned long)cantidad_apuestas);
    return 1;
}

int evaluar_ganancia(Apuesta apuesta, const CasillaRuleta *casilla_ganadora) {
    int ganancia = 0;

    if (casilla_ganadora == NULL || apuesta.monto <= 0) {
        fprintf(stderr, "ERROR: Apuesta o casilla ganadora no válida.\n");
        return 0;
    }

    switch (apuesta.tipo) {
        case APUESTA_PLENO:
            if (apuesta.valor_elegido < 0 || apuesta.valor_elegido > 36 ||
                apuesta.monto > INT_MAX / 36) {
                fprintf(stderr, "ERROR: Apuesta a pleno fuera de rango.\n");
                return 0;
            }
            if (casilla_ganadora->numero == apuesta.valor_elegido) {
                ganancia = apuesta.monto * 36; // Pago 35 a 1 + recupera lo apostado
            }
            break;

        case APUESTA_COLOR:
            if ((apuesta.valor_elegido != ROJO && apuesta.valor_elegido != NEGRO) ||
                apuesta.monto > INT_MAX / 2) {
                fprintf(stderr, "ERROR: Color de apuesta no válido.\n");
                return 0;
            }
            // En ruleta.h: VERDE = 0, ROJO = 1, NEGRO = 2
            if ((int)casilla_ganadora->color == apuesta.valor_elegido) {
                ganancia = apuesta.monto * 2; // Pago 1 a 1 + recupera
            }
            break;

        case APUESTA_PARIDAD:
            if ((apuesta.valor_elegido != PAR && apuesta.valor_elegido != IMPAR) ||
                apuesta.monto > INT_MAX / 2) {
                fprintf(stderr, "ERROR: Paridad de apuesta no válida.\n");
                return 0;
            }
            // En ruleta.h: NINGUNA = 0, PAR = 1, IMPAR = 2
            if ((int)casilla_ganadora->paridad == apuesta.valor_elegido) {
                ganancia = apuesta.monto * 2; // Pago 1 a 1 + recupera
            }
            break;

        default:
            fprintf(stderr, "ERROR: Tipo de apuesta desconocido.\n");
            return 0;
    }

    return ganancia;
}