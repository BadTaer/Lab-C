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
