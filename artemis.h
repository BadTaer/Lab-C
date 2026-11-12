#ifndef ARTEMIS_H
#define ARTEMIS_H

#define G_TIERRA          9.80     
#define PASO_TELEMETRIA   10.0    
#define MAX_REGISTROS     20
#define A1_ENUNCIADO      20.0     
#define T1_ENUNCIADO      120.0    
#define A2_ENUNCIADO      12.5     
#define H_ENUNCIADO       160000.0 

#define A1_MIN 10.0
#define A1_MAX 50.0
#define T1_MIN 10.0
#define T1_MAX 300.0
#define A2_MIN 5.0
#define A2_MAX 30.0
#define H_MIN_KM 100.0
#define H_MAX_KM 400.0

typedef struct {
    double tiempo;        
    double altitud;       
    double velocidad;     
    double aceleracion;   
} Telemetria;

typedef struct {
    double a1, t1, a2, hObjetivo;
    int    configurada;

    double v1, y1;   
    double v2, t2;        
    double tTotal;
    double hMax;          
    double aMaxG;         
    int    calculada;

    Telemetria registro[MAX_REGISTROS];
    int        cantRegistros;
} Mision;


void misionInicializar(Mision *m);
void misionCargarEnunciado(Mision *m);
void misionConfigurar(Mision *m);          
void misionSimular(Mision *m);             
void misionMostrarReporte(const Mision *m);

#endif
