#ifndef COMPARTIMENTOLOCKER_H
#define COMPARTIMENTOLOCKER_H

#include "fecha.h"

// Estructura que representa un compartimento de un locker
typedef struct
{
    char id_locker[11];    // 10 caracteres + '\0'
    unsigned num_compartimento; // Número del compartimento
    unsigned cod_locker;   // Código asociado al locker
    char estado[8];        // "ocupado" o "vacío"
    Fecha fecha_ocupacion; // Fecha en que se ocupó el compartimento
    Fecha fecha_caducidad; // Fecha en que se liberará el compartimento
} CompartimentoLocker;

#endif // COMPARTIMENTOLOCKER_H
