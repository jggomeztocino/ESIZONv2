#ifndef CATEGORIA_H
#define CATEGORIA_H

#include "pedido.h"
//#include "productos.h"
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

void cargar_categorias(VectorCategorias* categorias);

void guardar_categorias(VectorCategorias* categorias);

Categoria* buscar_categoria_id(VectorCategorias* categorias, char* id_categoria);

void listar_categoria(Categoria* categoria);

void listar_categorias(VectorCategorias* categorias);

Categoria* modificar_categoria(Categoria* categoria);

Categoria* alta_categoria(VectorCategorias* categorias);

void baja_categoria(VectorCategorias* categorias, VectorProductos* v_productos, char* id_categoria);

#endif // CATEGORIA_H
