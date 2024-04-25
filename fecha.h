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

/**
    * @brief Crea una fecha
    * @param dia Día de la fecha
    * @param mes Mes de la fecha
    * @param anio Año de la fecha
    * @return Fecha
    

*/
Fecha crearFecha(int dia, int mes, int anio);
/**
    * @brief Obtiene la fecha actual
    * @return Fecha

*/
Fecha obtener_fecha_actual();
/**
    * @brief Compara dos fechas
    * @param fecha1 Fecha 1
    * @param fecha2 Fecha 2
    * @return 0 si son iguales, 1 si fecha1 es mayor que fecha2, -1 si fecha1 es menor que fecha2

*/
int comparar_fechas(Fecha fecha1, Fecha fecha2);

#endif // FECHA_H
