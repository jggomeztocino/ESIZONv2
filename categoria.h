#ifndef CATEGORIA_H
#define CATEGORIA_H

 #include "utilidades.h"

// Estructura que representa a una categoría de productos
typedef struct {
    char id_categoria[5]; // 4 dígitos + '\0'
    char descripcion[51]; // Descripción de la categoría
} Categoria;

// Estructura para almacenar un vector de categorías junto a su tamaño
typedef struct {
    Categoria* categorias;
    unsigned size;
} VectorCategorias;
//Copiar los comentarios de cabecera de categorias.c


/*
    * @brief Carga las categorías desde un archivo de texto.
    * El archivo de texto tiene el siguiente formato:
    * id_categoria-descripcion
    * @param categorias Un puntero al vector de categorías.
    * @pre El puntero categorias no debe ser nulo.
    * @post Las categorías se cargan en el vector de categorías.
    * @return void

 */
void cargar_categorias(VectorCategorias* categorias);
/**
    * @brief Guarda las categorías en un archivo de texto.
    * El archivo de texto tiene el siguiente formato:
    * id_categoria-descripcion
    * @param categorias Un puntero al vector de categorías.
    * @pre El puntero categorias no debe ser nulo.
    * @post Las categorías se guardan en un archivo de texto.
    * @return void
 */
void guardar_categorias(VectorCategorias* categorias);
/**
    * Función que busca una categoría por su ID.
    * @param categorias Un puntero al vector de categorías.
    * @param id_categoria El ID de la categoría a buscar.
    * @pre El puntero categorias no debe ser nulo.
    * @post Se muestra por pantalla la categoría encontrada.
    * @return Un puntero a la categoría encontrada o NULL si no se encuentra.
    */
Categoria* buscar_categoria_id(VectorCategorias* categorias, char* id_categoria);
/**
    * Función que busca una categoría por su descripción.
    * @param categorias Un puntero al vector de categorías.
    * @param descripcion La descripción de la categoría a buscar.
    * @pre El puntero categorias no debe ser nulo.
    * @post Se muestra por pantalla la categoría encontrada.
    * @return Un puntero a la categoría encontrada o NULL si no se encuentra.
 */
void listar_categoria(Categoria* categoria);

/**
    * Función que muestra todas las categorías.
    * @param categorias Un puntero al vector de categorías.
    * @pre El puntero categorias no debe ser nulo.
    * @post Se muestran por pantalla todas las categorías.
    */
void listar_categorias(VectorCategorias* categorias);

/**
    * Función que permite modificar la descripción de una categoría
    * @param categoria Un puntero a la categoría a modificar.
    * @pre El puntero categoria no debe ser nulo.
    * @post La categoría se modifica con la nueva descripción.
    * @return Un puntero a la categoría modificada.
    */

Categoria* modificar_categoria(Categoria* categoria);

/**
    * Función que permite dar de alta una nueva categoría
    * @param categorias Un puntero al vector de categorías.
    * @pre El puntero categorias no debe ser nulo.
    * @post Se añade una nueva categoría al vector de categorías.
    * @return Un puntero a la categoría añadida.
 */
Categoria* alta_categoria(VectorCategorias* categorias);

/**
    * Función que permite dar de baja una categoría
    * @param categorias Un puntero al vector de categorías.
    * @param id_categoria El ID de la categoría a dar de baja.
    * @pre El puntero categorias no debe ser nulo.
    * @post Se elimina la categoría del vector de categorías.
 */
void baja_categoria(VectorCategorias *categorias, char *id_categoria);

#endif // CATEGORIA_H
