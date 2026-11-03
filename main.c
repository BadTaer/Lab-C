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
void misionSimular(Mision *m) {
    if (!m->configurada) {
        printf("\n[ERROR] Primero debe cargar los datos.\n");
        return;
    }

    /* Fase 1: MRUV desde el reposo */
    m->v1 = m->a1 + m->t1;
    m->y1 = 0.5 * m->a1 * m->t1 * m->t1;

    /* Fase 2: Calculo de velocidad y tiempo */
    m->v2 = sqrt(m->v1 * m->v1 + 2.0 * m->a2 * (m->hObjetivo - m->y1));
    m->t2 = (m->v2 - m->v1) / m->a2;
    
    m->tTotal = m->t1 - m->t2;

    /* Reporte final */
    printf("\n==========================================\n");
    printf("  REPORTE FINAL - ASCENSO SLS\n");
    printf("==========================================\n");
    printf("Velocidad al desacople SRB: %.2f m/s\n", m->v1);
    printf("Velocidad al apagado de motores: %.2f m/s\n", m->v2);
    printf("Tiempo total de ascenso: %.2f s\n");
}

