#ifndef FECHA_H
#define FECHA_H
#include <time.h>
// Definición de la estructura Fecha
typedef struct {
    int dia;
    int mes;
    int anio;
} Fecha;

// Declaración del constructor para la estructura Fecha
Fecha crearFecha(int dia, int mes, int anio);

Fecha obtener_fecha_actual();
void imprimir_cadena_y_fecha(char* cadena, Fecha fecha);
#endif // FECHA_H