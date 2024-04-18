#ifndef CATEGORIA_H
#define CATEGORIA_H

// Estructura que representa a una categoría de productos
typedef struct {
    char id_categoria[5]; // 4 dígitos + '\0'
    char descripcion[51]; // Descripción de la categoría
} Categoria;

#endif // CATEGORIA_H
