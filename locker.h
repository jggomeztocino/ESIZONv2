#ifndef LOCKER_H
#define LOCKER_H

#include "fecha.h"

// Estructura que representa a un locker
typedef struct {
    char id_locker[11]; // 10 caracteres + '\0'
    char localidad[21]; // Localidad donde se encuentra el locker
    char provincia[21]; // Provincia donde se encuentra el locker
    char ubicacion[21]; // Ubicación específica del locker
    unsigned num_compartimentos_total; // Número total de compartimentos
    unsigned num_compartimentos_ocupados; // Número de compartimentos ocupados
} Locker;

// Estructura para almacenar un vector de lockers junto a su tamaño
typedef struct {
    Locker* lockers;
    unsigned size;
} VectorLockers;

void cargar_lockers(VectorLockers* lockers);

void guardar_lockers(VectorLockers* lockers);

Locker* buscar_locker_id(VectorLockers* lockers, char* id_locker);

void listar_locker(Locker* locker);

void listar_lockers_localidad(VectorLockers* lockers, char* localidad);

/*
 * CompartimentoLocker: Relaciona un compartimento con un locker
* o Identificador del locker (Id_locker), 10 caracteres máximo.
o Número de compartimento (Num_comp).
o Código del locker (Cod_locker).
o Estado: «ocupado» o «vacío»
o Fecha ocupación (día, mes y año).
o Fecha caducidad (día, mes y año)
 */

typedef struct {
    char id_locker[11]; // 10 caracteres + '\0'
    unsigned n_compartimento; // Número de compartimento
    unsigned cod_locker; // Código del locker
    unsigned estado; // 0: vacío, 1: ocupado
    Fecha fecha_ocupacion; // Fecha de ocupación
    Fecha fecha_caducidad; // Fecha de caducidad
} CompartimentoLocker;

// Estructura para almacenar un vector de compartimentos junto a su tamaño
typedef struct {
    CompartimentoLocker* compartimentos;
    unsigned size;
} VectorCompartimentos;

void cargar_compartimentos(VectorCompartimentos* v_compartimentos);

void guardar_compartimentos(VectorCompartimentos* v_compartimentos);


void listar_compartimento(CompartimentoLocker* v_compartimento);

//listar todos los lockers
void listar_todo_lockers(VectorLockers* v_lockers);

CompartimentoLocker* buscar_compartimento(VectorCompartimentos* v_compartimentos, char* id_locker, unsigned num_compartimento);

//buscar primer compartimento libre de un locker
CompartimentoLocker* buscar_primer_compartimento_libre(VectorCompartimentos* v_compartimentos, char* id_locker);


#endif // LOCKER_H
