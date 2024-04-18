#include "stdio.h"
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#include "productos.h"

void cargar_productos(VectorProductos* productos)
{
    FILE* f = fopen("../data/productos.txt", "r");
    if (f == NULL) {
        perror("\nError al abrir el archivo\n");
        return;
    }
    productos->productos = (Producto*)malloc(sizeof(Producto));
    productos->size = 0;
    while (fscanf(f, "%s-%15[^-]-%50[^-]-%4[^-]-%4[^-]-%u-%u-%f\n",
                  productos->productos[productos->size].id_producto,
                  productos->productos[productos->size].nombre,
                  productos->productos[productos->size].descripcion,
                  productos->productos[productos->size].id_categoria,
                  productos->productos[productos->size].id_gestor,
                  &productos->productos[productos->size].stock,
                  &productos->productos[productos->size].entrega,
                  &productos->productos[productos->size].importe) == 8) {
        productos->size++;
        productos->productos = (Producto*)realloc(productos->productos, (productos->size + 1) * sizeof(Producto));
        if(productos->productos == NULL) {
            free(productos->productos);
            perror("\nError al reservar memoria\n");
        }
    }
    fclose(f);
}

void guardar_productos(VectorProductos* productos)
{
    FILE* f = fopen("../data/productos.txt", "w");
    if (f == NULL) {
        return;
    }
    int i;
    for (i = 0; i < productos->size; i++) {
        fprintf(f, "%s-%s-%s-%s-%s-%u-%u-%.2f\n",
                productos->productos[i].id_producto,
                productos->productos[i].nombre,
                productos->productos[i].descripcion,
                productos->productos[i].id_categoria,
                productos->productos[i].id_gestor,
                productos->productos[i].stock,
                productos->productos[i].entrega,
                productos->productos[i].importe);
    }
    fclose(f);
    free(productos->productos);
    productos->size = 0;
}

Producto* buscar_producto_id(VectorProductos* productos, char* id_producto)
{
    int i;
    for (i = 0; i < productos->size; i++) {
        if (strcmp(productos->productos[i].id_producto, id_producto) == 0) {
            return &productos->productos[i];
        }
    }
    return NULL;
}

void listar_producto(Producto* producto)
{
    printf(
        "---------------------------\n"
        "Nombre:     %s\n"
        "Descripción:  %s\n"
        "Categoría:  %s\n"
        "Gestor:  %s\n"
        "Stock:  %u\n"
        "Entrega:  %u\n"
        "Importe:  %.2f\n",
        producto->nombre,
        producto->descripcion,
        producto->id_categoria,
        producto->id_gestor,
        producto->stock,
        producto->entrega,
        producto->importe);
}

void listar_productos(VectorProductos* productos)
{
    int i;
    for (i = 0; i < productos->size; i++) {
        listar_producto(&productos->productos[i]);
    }
}

void listar_productos_categoria(VectorProductos* productos, int id_categoria)
{
    int i;
    for (i = 0; i < productos->size; i++) {
        if (atoi(productos->productos[i].id_categoria) == id_categoria) {
            listar_producto(&productos->productos[i]);
        }
    }
}

void listar_productos_nombre(VectorProductos* productos, char* nombre)
{
    int i;
    for (i = 0; i < productos->size; i++) {
        if (strcmp(productos->productos[i].nombre, nombre) == 0) {
            listar_producto(&productos->productos[i]);
        }
    }
}