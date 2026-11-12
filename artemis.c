#include <stdio.h>
#include <math.h>
#include "artemis.h"
#include "validaciones.h"

/* ================= Funciones privadas ================= */

static int datosCoherentes(const Mision *m)
{
    double y1 = 0.5 * m->a1 * m->t1 * m->t1;
    return y1 < m->hObjetivo;
}

static void calcularFase1(Mision *m)
{
    m->v1 = m->a1 * m->t1;
    m->y1 = 0.5 * m->a1 * m->t1 * m->t1;
}

static void calcularFase2(Mision *m)
{
    m->v2 = sqrt(m->v1 * m->v1 + 2.0 * m->a2 * (m->hObjetivo - m->y1));
    m->t2 = (m->v2 - m->v1) / m->a2;
    m->tTotal = m->t1 + m->t2;
}

static void calcularCaidaLibre(Mision *m)
{
    m->hMax = m->hObjetivo + (m->v2 * m->v2) / (2.0 * G_TIERRA);
}

static void calcularAceleracionMaxima(Mision *m)
{
    double aMax = (m->a1 > m->a2) ? m->a1 : m->a2;
    m->aMaxG = aMax / G_TIERRA;
}

/* Estado de la nave en el instante t (resultado por puntero) */
static void estadoEnTiempo(const Mision *m, double t, Telemetria *out)
{
    out->tiempo = t;
    if (t <= m->t1) {
        out->aceleracion = m->a1;
        out->velocidad   = m->a1 * t;
        out->altitud     = 0.5 * m->a1 * t * t;
    } else {
        double dt = t - m->t1;
        out->aceleracion = m->a2;
        out->velocidad   = m->v1 + m->a2 * dt;
        out->altitud     = m->y1 + m->v1 * dt + 0.5 * m->a2 * dt * dt;
    }
}

static void registrarTelemetria(Mision *m, double t)
{
    if (m->cantRegistros < MAX_REGISTROS) {
        estadoEnTiempo(m, t, &m->registro[m->cantRegistros]);
        m->cantRegistros++;
    }
}
