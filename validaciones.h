/* validaciones.h - Ingreso seguro de datos y mensajes al usuario */
#ifndef VALIDACIONES_H
#define VALIDACIONES_H

/* Entrada: repiten la consulta hasta recibir un dato valido en [min, max] */
int    leerEntero(const char *mensaje, int min, int max);
double leerDouble(const char *mensaje, double min, double max);
int    leerSiNo(const char *mensaje);   /* devuelve 1 (s) o 0 (n) */

/* Interfaz */
void mostrarTitulo(const char *titulo);
void mostrarError(const char *mensaje);
void mostrarAdvertencia(const char *mensaje);
void pausar(void);

#endif
