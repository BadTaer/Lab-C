#include <stdio.h>
#include <math.h>

#define G_TIERRA 9.80
#define A1_ENUNCIADO 20.0
#define T1_ENUNCIADO 120.0
#define A2_ENUNCIADO 12.5
#define H_ENUNCIADO 160000.0

typedef struct {
    double a1, t1, a2, hObjetivo;
    double v1, y1, v2, t2, tTotal;
    int configurada;
} Mision;

void misionCargarEnunciado(Mision *m) {
    m->a1 = A1_ENUNCIADO;
    m->t1 = T1_ENUNCIADO;
    m->a2 = A2_ENUNCIADO;
    m->hObjetivo = H_ENUNCIADO;
    m->configurada = 1;
    printf("\n[CUIDADO] Datos del enunciado cargados.\n");
}
