#include "fecha.h"
#include <time.h>
#include <stdio.h>
// Implementación del constructor para la estructura Fecha
Fecha crearFecha(int dia, int mes, int anio) {
    Fecha f;
    // Normalización de la fecha
    if(dia > 31) {
        dia = 1;
        mes++;
    }
    if(mes > 12) {
        mes = 1;
        anio++;
    }
    f.dia = dia;
    f.mes = mes;
    f.anio = anio;
    return f;
}


Fecha obtener_fecha_actual() {
    // Obtener la fecha actual del sistema
    time_t tiempo_actual = time(NULL);
    struct tm *fecha = localtime(&tiempo_actual);
    
    // Crear una estructura Fecha y asignar los valores
    Fecha fecha_actual;
    fecha_actual.dia = fecha->tm_mday;
    fecha_actual.mes = fecha->tm_mon + 1; // tm_mon está basado en 0 (enero = 0), por lo que sumamos 1
    fecha_actual.anio = fecha->tm_year + 1900; // tm_year es el año desde 1900, por lo que sumamos 1900

    return fecha_actual;
}


void imprimir_cadena_y_fecha(char* cadena, Fecha fecha) {
    printf("%s %02d/%02d/%d\n", cadena, fecha.dia, fecha.mes, fecha.anio);
}

//FUncion que compara fechas
int comparar_fechas(Fecha fecha1, Fecha fecha2) {
    if(fecha1.anio < fecha2.anio) {
        return -1;
    } else if(fecha1.anio > fecha2.anio) {
        return 1;
    } else {
        if(fecha1.mes < fecha2.mes) {
            return -1;
        } else if(fecha1.mes > fecha2.mes) {
            return 1;
        } else {
            if(fecha1.dia < fecha2.dia) {
                return -1;
            } else if(fecha1.dia > fecha2.dia) {
                return 1;
            } else {
                return 0;
            }
        }
    }
}

