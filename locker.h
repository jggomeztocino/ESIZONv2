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
/**
 * Cargar los lockers desde el archivo Lockers.txt
 * @param lockers Vector de lockers
 * @pre El puntero lockers no debe ser nulo
 * @post Los lockers se cargan en el vector de lockers
 * @return void
 */
void cargar_lockers(VectorLockers* lockers);
/** Guardar los lockers en el archivo Lockers.txt
 * @param lockers Vector de lockers
 * @pre El puntero lockers no debe ser nulo
 * @post Los lockers se guardan en el archivo Lockers.txt
 * @return void
 */
void guardar_lockers(VectorLockers* lockers);
/** Buscar un locker por su ID
 * @param lockers Vector de lockers
 * @param id_locker ID del locker a buscar
 * @pre El puntero lockers no debe ser nulo
 * @post Se devuelve el locker con el ID especificado o NULL si no se encuentra
 * @return Locker encontrado o NULL
 */
Locker* buscar_locker_id(VectorLockers* lockers, char* id_locker);
/**
 * Listar un locker
 * @param locker Locker a listar
 * @return void
 */
void listar_locker(Locker* locker);
/**
 * Listar los lockers de una localidad
 * @param lockers Vector de lockers
 * @param localidad Localidad a buscar
 * @return void
 */
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

/** Funcion que carga los compartimentos desde el archivo compartimentoslockers.txt
 * @param v_compartimentos Vector de compartimentos
 * @pre El puntero v_compartimentos no debe ser nulo
 * @post Los compartimentos se cargan en el vector de compartimentos
 * @return void
 */
void cargar_compartimentos(VectorCompartimentos* v_compartimentos);
/**
 * Guardar los compartimentos en el archivo compartimentos.txt
 * @param v_compartimentos Vector de compartimentos
 * @pre El puntero v_compartimentos no debe ser nulo
 * @post Los compartimentos se guardan en el archivo compartimentos.txt
 * @return void
 */
void guardar_compartimentos(VectorCompartimentos* v_compartimentos);

/**
 * Listar un compartimento
 * @param v_compartimento Compartimento a listar
 * @return void
 */
void listar_compartimento(CompartimentoLocker* v_compartimento);

/**
 * Listar todos los lockers
 * @param v_lockers Vector de lockers
 * @return void
 */
 void listar_todo_lockers(VectorLockers* v_lockers);
/**
 * Buscar un compartimento por su número de compartimento y el ID del locker
 * @param v_compartimentos Vector de compartimentos
 * @param id_locker Identificador del locker
 * @param num_compartimento Número de compartimento
 * @return CompartimentoLocker* Puntero al compartimento encontrado o NULL si no se encuentra
 */
CompartimentoLocker* buscar_compartimento(VectorCompartimentos* v_compartimentos, char* id_locker, unsigned num_compartimento);

/**
 * Buscar el primer compartimento libre por su número de compartimento y el ID del locker
 * @param v_compartimentos Vector de compartimentos
 * @param id_locker Identificador del locker
 * @param num_compartimento Número de compartimento
 * @return CompartimentoLocker* Puntero al compartimento encontrado o NULL si no se encuentra
 */
 CompartimentoLocker* buscar_primer_compartimento_libre(VectorCompartimentos* v_compartimentos, char* id_locker);


#endif // LOCKER_H
