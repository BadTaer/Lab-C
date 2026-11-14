# Simulador de Misiones Artemis — Lab C

**Materia:** Algoritmos y Estructuras de Datos — UTN Facultad Regional Resistencia  
**Comisión:** 1.4

## Integrantes

- Julio Gonzalo Ezequiel AGUIRRE
- Benjamín Ezequiel MENDIBURU
- Jose Emilio SILVA

## Descripción del proyecto

Desarrollamos en **lenguaje C** un simulador por consola del **escenario 1: ascenso y propulsión del cohete SLS** de la misión Artemis. El programa utiliza ecuaciones de movimiento rectilíneo uniformemente variado (MRUV) para representar dos fases de ascenso: con los propulsores sólidos (SRB) y, después de su desacople, con el motor principal.

El usuario puede utilizar los datos del enunciado o ingresar valores propios. La simulación registra **telemetría cada 10 segundos** (tiempo, altitud, velocidad y aceleración) y presenta un reporte con la velocidad y altura al desacople, la velocidad al apagado de motores, la altura máxima ante una falla y la aceleración máxima expresada en múltiplos de *g*.

## Funcionamiento

El menú permite:

1. Cargar los valores originales del enunciado.
2. Configurar una misión con datos propios.
3. Ejecutar la simulación y visualizar la telemetría.
4. Consultar el reporte final.
0. Salir.

**Reglas:** antes de simular hay que cargar o configurar una misión; antes de consultar el reporte, hay que ejecutarla. Se validan los tipos y rangos de los datos ingresados y se comprueba que el desacople ocurra antes de alcanzar la altura objetivo. Si la entrada no es válida, el programa vuelve a solicitarla.

## Estructura del código

- `main.c`: menú y control del flujo del programa.
- `artemis.h`: constantes, estructuras `Mision` y `Telemetria`, y prototipos.
- `artemis.c`: cálculos físicos, simulación y reporte.
- `validaciones.h` / `validaciones.c`: lectura segura de datos y mensajes al usuario.
- `Makefile`: compilación de todos los módulos.

Se utilizan funciones, condicionales, ciclos, estructuras (`struct`), un arreglo para la telemetría y punteros para modificar y consultar los datos de la misión.

## Compilación y ejecución

Se necesita **GCC** y, para la opción recomendada, **Make**. Desde la carpeta del proyecto:

```bash
make
```

Si no se dispone de Make, también se puede compilar directamente:

```bash
gcc main.c artemis.c validaciones.c -o artemis -lm
```

Para ejecutar: **Windows:** `./artemis.exe` (o `.\artemis.exe` en PowerShell); **Linux/macOS:** `./artemis`.

Con los datos originales, el programa obtiene `v1 = 2400 m/s`, `v2 = 2481.93 m/s` y una altura máxima de aproximadamente `474.29 km`.

## Desarrollo colaborativo y uso de IA

El proyecto se desarrolló gradualmente y se registraron los avances en GitHub: menú inicial, estructuras y cálculos, correcciones de errores, modularización, telemetría, validaciones y Makefile.

Utilizamos **inteligencia artificial como apoyo**, principalmente para revisar errores y considerar mejoras. Entre las consultas abordadas estuvieron (resumidas, no son transcripciones literales):

- **Lectura de datos:** cómo evitar errores al ingresar opciones y validar números sin depender de `scanf`.
- **Cálculos:** cómo revisar las fórmulas del ascenso y corregir el tiempo total de la simulación.
- **Organización:** cómo separar las funciones entre archivos `.c` y `.h` y mejorar las validaciones.

Las sugerencias se revisaron y adaptaron a nuestro código. El equipo comprobó el funcionamiento mediante compilación, ejecución del escenario y pruebas de entrada, manteniendo la responsabilidad sobre la implementación final.

## Enlaces

- **Repositorio:** https://github.com/BadTaer/Lab-C
- **Video de presentación:** https://youtu.be/wfTPyD-oFxk
