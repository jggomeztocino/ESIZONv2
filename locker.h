#ifndef LOCKER_H
#define LOCKER_H

// Estructura que representa a un locker
typedef struct {
    char id_locker[11]; // 10 caracteres + '\0'
    char localidad[21]; // Localidad donde se encuentra el locker
    char provincia[21]; // Provincia donde se encuentra el locker
    char ubicacion[21]; // Ubicación específica del locker
    int num_compartimentos_total; // Número total de compartimentos
    int num_compartimentos_ocupados; // Número de compartimentos ocupados
} Locker;

#endif // LOCKER_H
