#include "stdio.h"
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#include "categoria.h"




void cargar_categorias(VectorCategorias* categorias)
{
    FILE* f = fopen("../data/Categorias.txt", "r");
    if (f == NULL) {
        perror("\nError al abrir el archivo\n");
        return;
    }
    categorias->categorias = (Categoria*)malloc(sizeof(Categoria));
    categorias->size = 0;
    while (fscanf(f, "%4[^-]-%50[^\n]\n",
                  categorias->categorias[categorias->size].id_categoria,
                  categorias->categorias[categorias->size].descripcion) == 2) {
        categorias->size++;
        categorias->categorias = (Categoria*)realloc(categorias->categorias, (categorias->size + 1) * sizeof(Categoria));
        if(categorias->categorias == NULL) {
            free(categorias->categorias);
            perror("\nError al reservar memoria\n");
        }
    }
    fclose(f);
}


void guardar_categorias(VectorCategorias* categorias)
{
    FILE* f = fopen("../data/Categorias.txt", "w");
    if (f == NULL) {
        return;
    }
    int i;
    for (i = 0; i < categorias->size; i++) {
        fprintf(f, "%s-%s\n",
                categorias->categorias[i].id_categoria,
                categorias->categorias[i].descripcion);
    }
    fclose(f);
    free(categorias->categorias);
    categorias->size = 0;
}


Categoria* buscar_categoria_id(VectorCategorias* categorias, char* id_categoria)
{
    int i;
    for (i = 0; i < categorias->size; i++) {
        if (strcmp(categorias->categorias[i].id_categoria, id_categoria) == 0) {
            return &categorias->categorias[i];
        }
    }
    return NULL;
}

void listar_categoria(Categoria* categoria)
{
    printf("ID: %s\n", categoria->id_categoria);
    printf("Descripción: %s\n", categoria->descripcion);
}

void listar_categorias(VectorCategorias* categorias)
{
    int i;
    for (i = 0; i < categorias->size; i++) {
        listar_categoria(&categorias->categorias[i]);
    }
}

Categoria* modificar_categoria(Categoria* categoria)
{
    leer_cadena("Ingrese la nueva descripción de la categoría: ", categoria->descripcion, 50);
    return categoria;
}

Categoria* alta_categoria(VectorCategorias* categorias)
{
    categorias->categorias = (Categoria*)realloc(categorias->categorias, (categorias->size + 1) * sizeof(Categoria));
    if(categorias->categorias == NULL) {
        free(categorias->categorias);
        perror("\nError al reservar memoria\n");
    }
    sprintf(categorias->categorias[categorias->size].id_categoria, "%04d", atoi(categorias->categorias[categorias->size - 1].id_categoria) + 1);
    leer_cadena("Ingrese la descripción de la categoría: ", categorias->categorias[categorias->size].descripcion, 51);
    categorias->size++;
    return &categorias->categorias[categorias->size - 1];
}


void baja_categoria(VectorCategorias *categorias, char *id_categoria)
{
    int i;
    for (i = 0; i < categorias->size; i++) {
        if (strcmp(categorias->categorias[i].id_categoria, id_categoria) == 0) {
            break;
        }
    }
    for (; i < categorias->size - 1; i++) {
        categorias->categorias[i] = categorias->categorias[i + 1];
    }
    categorias->size--;
    categorias->categorias = (Categoria*)realloc(categorias->categorias, categorias->size * sizeof(Categoria));
    if(categorias->categorias == NULL) {
        free(categorias->categorias);
        perror("\nError al reservar memoria\n");
    }
}