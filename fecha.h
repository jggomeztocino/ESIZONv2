#ifndef FECHA_H
#define FECHA_H
#include <time.h>
// Definición de la estructura Fecha
typedef struct
{
    int dia;
    int mes;
    int anio;
} Fecha;

// Declaración del constructor para la estructura Fecha
Fecha crearFecha(int dia, int mes, int anio);

Fecha obtener_fecha_actual();

int comparar_fechas(Fecha fecha1, Fecha fecha2);

#endif // FECHA_H
