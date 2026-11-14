/* main.c - Menu principal y flujo general del programa */
#include <stdio.h>
#include "artemis.h"
#include "validaciones.h"
 
static void mostrarMenu(void)
{
    mostrarTitulo("SIMULADOR ARTEMIS - ASCENSO SLS");
    printf("  1. Cargar datos del enunciado\n");
    printf("  2. Ingresar datos propios\n");
    printf("  3. Ejecutar simulacion\n");
    printf("  4. Ver reporte final\n");
    printf("  0. Salir\n");
}
 
int main(void)
{
    Mision mision;
    int opcion;
 
    misionInicializar(&mision);
 
    do {
        mostrarMenu();
        opcion = leerEntero("Opcion: ", 0, 4);
 
        switch (opcion) {
            case 1:
                misionCargarEnunciado(&mision);
                break;
            case 2:
                misionConfigurar(&mision);
                break;
            case 3:
                if (mision.configurada) {
                    misionSimular(&mision);
                } else {
                    mostrarAdvertencia("Primero cargue o ingrese los datos (opcion 1 o 2).");
                }
                break;
            case 4:
                if (mision.calculada) {
                    misionMostrarReporte(&mision);
                } else {
                    mostrarAdvertencia("Primero ejecute la simulacion (opcion 3).");
                }
                break;
            case 0:
                printf("\nFin de la mision. Hasta pronto!\n");
                break;
        }
        if (opcion != 0) {
            pausar();
        }
    } while (opcion != 0);
 
    return 0;
}
