#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include "validaciones.h"

#define TAM_LINEA 64

/* ---------- Funciones auxiliares (privadas del modulo) ---------- */

static int leerLinea(char *buffer, int tam)
{
    int c;
    int valida = 1;

    if (fgets(buffer, tam, stdin) == NULL) {
        printf("\nEntrada cerrada. Finalizando programa.\n");
        exit(EXIT_FAILURE);
    }
    if (strchr(buffer, '\n') == NULL) {           /* la linea no entro en el buffer */
        while ((c = getchar()) != '\n' && c != EOF) { }
        valida = 0;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
    if (buffer[0] == '\0') {
        valida = 0;
    }
    return valida;
}

static void comaAPunto(char *texto)
{
    char *p = strchr(texto, ',');
    if (p != NULL) {
        *p = '.';
    }
}

static int soloEspacios(const char *p)
{
    while (isspace((unsigned char)*p)) {
        p++;
    }
    return *p == '\0';
}

/* ---------- Funciones publicas ---------- */

int leerEntero(const char *mensaje, int min, int max)
{
    char linea[TAM_LINEA];
    char *fin;
    long valor = 0;
    int ok = 0;

    do {
        printf("%s", mensaje);
        if (!leerLinea(linea, TAM_LINEA)) {
            mostrarError("Entrada vacia o demasiado larga.");
        } else {
            errno = 0;
            valor = strtol(linea, &fin, 10);
            if (fin == linea || !soloEspacios(fin) || errno != 0) {
                mostrarError("Debe ingresar un numero entero (sin letras ni simbolos).");
            } else if (valor < min || valor > max) {
                printf("  [!] El valor debe estar entre %d y %d.\n", min, max);
            } else {
                ok = 1;
            }
        }
    } while (!ok);

    return (int)valor;
}

double leerDouble(const char *mensaje, double min, double max)
{
    char linea[TAM_LINEA];
    char *fin;
    double valor = 0.0;
    int ok = 0;

    do {
        printf("%s", mensaje);
        if (!leerLinea(linea, TAM_LINEA)) {
            mostrarError("Entrada vacia o demasiado larga.");
        } else {
            comaAPunto(linea);
            errno = 0;
            valor = strtod(linea, &fin);
            if (fin == linea || !soloEspacios(fin) || errno != 0 || !isfinite(valor)) {
                mostrarError("Debe ingresar un numero valido (ej: 12.5).");
            } else if (valor < min || valor > max) {
                printf("  [!] El valor debe estar entre %.2f y %.2f.\n", min, max);
            } else {
                ok = 1;
            }
        }
    } while (!ok);

    return valor;
}

int leerSiNo(const char *mensaje)
{
    char linea[TAM_LINEA];
    int respuesta = -1;

    do {
        printf("%s (s/n): ", mensaje);
        if (leerLinea(linea, TAM_LINEA) && linea[1] == '\0') {
            char c = (char)tolower((unsigned char)linea[0]);
            if (c == 's') respuesta = 1;
            else if (c == 'n') respuesta = 0;
        }
        if (respuesta == -1) {
            mostrarError("Responda con 's' o 'n'.");
        }
    } while (respuesta == -1);

    return respuesta;
}

void mostrarTitulo(const char *titulo)
{
    printf("\n==========================================\n");
    printf("  %s\n", titulo);
    printf("==========================================\n");
}

void mostrarError(const char *mensaje)
{
    printf("  [ERROR] %s\n", mensaje);
}

void mostrarAdvertencia(const char *mensaje)
{
    printf("  [AVISO] %s\n", mensaje);
}

void pausar(void)
{
    char linea[TAM_LINEA];
    printf("\nPresione ENTER para continuar...");
    if (fgets(linea, TAM_LINEA, stdin) == NULL) {
        exit(EXIT_FAILURE);
    }
}
