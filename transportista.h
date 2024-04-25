#ifndef TRANSPORTISTA_H
#define TRANSPORTISTA_H
#include "utilidades.h"

// Estructura que representa a un transportista
typedef struct {
    char id_transportista[5]; // 4 digitos
    char nombre[21]; // Nombre del transportista
    char email[31]; // Email del transportista
    char contrasena[16]; // Contraseña de acceso
    char nombre_empresa[21]; // Nombre de la empresa de transporte
    char ciudad[21]; // Ciudad de operación
} Transportista;

// Estructura para almacenar un vector de transportistas junto a su tamaño
typedef struct {
    Transportista* transportistas;
    unsigned size;
} VectorTransportistas;

/**
 * @brief Carga los transportistas desde el archivo Transportistas.txt
 * @param v_transportistas Vector de transportistas
 */
void cargar_transportistas(VectorTransportistas* v_transportistas);

/**
 * @brief Guarda los transportistas en el archivo Transportistas.txt
 * @param v_transportistas Vector de transportistas
 */
void guardar_transportistas(VectorTransportistas* v_transportistas);

/**
 * @brief Busca un transportista por su ID
 * @param v_transportistas Vector de transportistas
 * @param id_transportista ID del transportista a buscar
 * @return Puntero al transportista encontrado o NULL si no se encuentra
 */
Transportista* buscar_transportista_id(VectorTransportistas* v_transportistas, char* id_transportista);

/**
 * @brief Busca un transportista por su email
 * @param v_transportistas Vector de transportistas
 * @param email Email del transportista a buscar
 * @return Puntero al transportista encontrado o NULL si no se encuentra
 */
Transportista* buscar_transportista_email(VectorTransportistas* v_transportistas, char* email);

/**
 * @brief Función que lista un transportista
 * @param transportista Puntero al transportista a listar
 */
void listar_transportista(Transportista* transportista);

/**
 * @brief Función que da de alta un transportista
 * @param v_transportistas Vector de transportistas
 * @return Puntero al transportista dado de alta
 */
Transportista* alta_transportista(VectorTransportistas* v_transportistas);

/**
 * @brief Función que da de baja un transportista
 * @param v_transportistas Vector de transportistas
 * @param id_transportista ID del transportista a dar de baja
 */
void baja_transportista(VectorTransportistas* v_transportistas, char* id_transportista);

/**
 * @brief Función que modifica un transportista
 * @param transportista Puntero al transportista a modificar
 * @return Puntero al transportista modificado
 */
Transportista* modificar_transportista(Transportista* transportista);

/**
 * @brief Función que lista todos los transportistas
 * @param v_transportistas Vector de transportistas
 */
void listar_transportistas(VectorTransportistas* v_transportistas);

/**
 * @brief Función que lista los transportistas de una ciudad
 * @param v_transportistas Vector de transportistas
 * @param ciudad Ciudad de los transportistas a listar
 */
void listar_transportistas_ciudad(VectorTransportistas* v_transportistas, char* ciudad);

#endif // TRANSPORTISTA_H


