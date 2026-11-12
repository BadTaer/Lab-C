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
/* ================= Funciones publicas ================= */

void misionInicializar(Mision *m)
{
    m->a1 = m->t1 = m->a2 = m->hObjetivo = 0.0;
    m->v1 = m->y1 = m->v2 = m->t2 = m->tTotal = m->hMax = m->aMaxG = 0.0;
    m->configurada = 0;
    m->calculada = 0;
    m->cantRegistros = 0;
}

void misionCargarEnunciado(Mision *m)
{
    m->a1 = A1_ENUNCIADO;
    m->t1 = T1_ENUNCIADO;
    m->a2 = A2_ENUNCIADO;
    m->hObjetivo = H_ENUNCIADO;
    m->configurada = 1;
    m->calculada = 0;
    printf("  Datos del enunciado cargados correctamente.\n");
}

void misionConfigurar(Mision *m)
{
    int coherente = 0;
    double hKm;

    mostrarTitulo("CONFIGURACION DE LA MISION");
    do {
        m->a1 = leerDouble("Aceleracion fase 1 con SRB [m/s^2]: ", A1_MIN, A1_MAX);
        m->t1 = leerDouble("Tiempo de desacople SRB [s]: ", T1_MIN, T1_MAX);
        m->a2 = leerDouble("Aceleracion fase 2 solo nucleo [m/s^2]: ", A2_MIN, A2_MAX);
        hKm   = leerDouble("Altitud de apagado de motores [km]: ", H_MIN_KM, H_MAX_KM);
        m->hObjetivo = hKm * 1000.0;

        coherente = datosCoherentes(m);
        if (!coherente) {
            mostrarError("La nave superaria la altitud objetivo antes del desacople. Ingrese los datos nuevamente.");
        }
    } while (!coherente);

    m->configurada = 1;
    m->calculada = 0;
}

void misionSimular(Mision *m)
{
    double t;
    int i;
    
    calcularFase1(m);
    calcularFase2(m);
    calcularCaidaLibre(m);
    calcularAceleracionMaxima(m);

    m->cantRegistros = 0;
    for (t = 0.0; t < m->tTotal; t += PASO_TELEMETRIA) {
        registrarTelemetria(m, t);
    }
    registrarTelemetria(m, m->tTotal);
    m->calculada = 1;

    mostrarTitulo("TELEMETRIA DEL ASCENSO");
    printf("%10s %14s %14s %12s\n", "t [s]", "Altitud [m]", "Veloc. [m/s]", "a [m/s^2]");
    for (i = 0; i < m->cantRegistros; i++) 
    {
        printf("%10.1f %14.1f %14.1f %12.2f\n",
               m->registro[i].tiempo, m->registro[i].altitud,
               m->registro[i].velocidad, m->registro[i].aceleracion);
    }
}

void misionMostrarReporte(const Mision *m)
{
    mostrarTitulo("REPORTE FINAL - ASCENSO SLS");
    printf("a) Desacople SRB (t = %.1f s):\n", m->t1);
    printf("     v1 = %.2f m/s | y1 = %.2f m\n", m->v1, m->y1);
    printf("b) Apagado de motores (h = %.1f m, t = %.2f s):\n", m->hObjetivo, m->tTotal);
    printf("     v2 = %.2f m/s\n", m->v2);
    printf("c) Con falla en caida libre (g = %.2f m/s^2):\n", G_TIERRA);
    printf("     h_max = %.2f m (%.2f km)\n", m->hMax, m->hMax / 1000.0);
    printf("d) Aceleracion maxima de la tripulacion:\n");
    printf("     %.2f g\n", m->aMaxG);
}
