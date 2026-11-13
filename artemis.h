/* artemis.h - Escenario 1: Ascenso y propulsion con el SLS (MRUV)
   Constantes, tipos de datos y prototipos publicos de la simulacion */
#ifndef ARTEMIS_H
#define ARTEMIS_H

/* ---------- Constantes fisicas y de simulacion ---------- */
#define G_TIERRA          9.80      /* m/s^2 */
#define PASO_TELEMETRIA   10.0      /* s entre registros de telemetria */
#define MAX_REGISTROS     200

/* Valores del enunciado */
#define A1_ENUNCIADO      20.0      /* m/s^2 (fase 1, con SRB) */
#define T1_ENUNCIADO      120.0     /* s     (desacople SRB) */
#define A2_ENUNCIADO      12.5      /* m/s^2 (fase 2, solo nucleo) */
#define H_ENUNCIADO       160000.0  /* m     (apagado de motores) */

/* Rangos admitidos para datos ingresados por el usuario */
#define A1_MIN 10.0
#define A1_MAX 50.0
#define T1_MIN 10.0
#define T1_MAX 300.0
#define A2_MIN 5.0
#define A2_MAX 30.0
#define H_MIN_KM 100.0
#define H_MAX_KM 400.0

/* ---------- Tipos de datos ---------- */
typedef struct {
    double tiempo;        /* s   */
    double altitud;       /* m   */
    double velocidad;     /* m/s */
    double aceleracion;   /* m/s^2 */
} Telemetria;

typedef struct {
    /* Datos de entrada */
    double a1, t1, a2, hObjetivo;
    int    configurada;

    /* Resultados */
    double v1, y1;        /* al desacople SRB */
    double v2, t2;        /* al apagado de motores */
    double tTotal;
    double hMax;          /* altitud maxima en caida libre */
    double aMaxG;         /* aceleracion maxima en multiplos de g */
    int    calculada;

    /* Registro de la simulacion (arreglo) */
    Telemetria registro[MAX_REGISTROS];
    int        cantRegistros;
} Mision;

/* ---------- Prototipos publicos ---------- */
void misionInicializar(Mision *m);
void misionCargarEnunciado(Mision *m);
void misionConfigurar(Mision *m);          /* pide datos al usuario */
void misionSimular(Mision *m);             /* calcula + recorre el ascenso por turnos */
void misionMostrarReporte(const Mision *m);

#endif
