#include "stdio.h"
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#include "productos.h"

void cargar_productos(VectorProductos* v_productos) {
    // Abrir archivo de productos para lectura
    FILE* f = fopen("../data/Productos.txt", "r");
    if (f == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    // Inicializar la memoria para almacenar los productos
    v_productos->productos = (Producto*)malloc(sizeof(Producto));
    if (v_productos->productos == NULL) {
        perror("Error al reservar memoria inicial");
        fclose(f);
        return;
    }
    v_productos->size = 0;

    Producto* temp;
    int n_productos_actual = 0;

    // Leer los datos de los productos del archivo
    while (fscanf(f, "%7[^-]-%15[^-]-%50[^-]-%4[^-]-%4[^-]-%u-%u-%f\n",
                  v_productos->productos[n_productos_actual].id_producto,
                  v_productos->productos[n_productos_actual].nombre,
                  v_productos->productos[n_productos_actual].descripcion,
                  v_productos->productos[n_productos_actual].id_categoria,
                  v_productos->productos[n_productos_actual].id_gestor,
                  &v_productos->productos[n_productos_actual].stock,
                  &v_productos->productos[n_productos_actual].entrega,
                  &v_productos->productos[n_productos_actual].importe) == 8) {

        n_productos_actual++;
        temp = (Producto*)realloc(v_productos->productos, (n_productos_actual + 1) * sizeof(Producto));
        if (temp == NULL) {
            perror("Error al reservar memoria durante la lectura");
            free(v_productos->productos);
            fclose(f);
            return;
        }
        v_productos->productos = temp;
    }

    // Actualizar la cantidad de productos después de la lectura completa
    v_productos->size = n_productos_actual;
    fclose(f);
}

void guardar_productos(VectorProductos* v_productos)
{
    FILE* f = fopen("../data/Productos.txt", "w");
    if (f == NULL) {
        return;
    }
    int i;
    for (i = 0; i < v_productos->size; i++) {
        fprintf(f, "%s-%s-%s-%s-%s-%u-%u-%.2f\n",
                v_productos->productos[i].id_producto,
                v_productos->productos[i].nombre,
                v_productos->productos[i].descripcion,
                v_productos->productos[i].id_categoria,
                v_productos->productos[i].id_gestor,
                v_productos->productos[i].stock,
                v_productos->productos[i].entrega,
                v_productos->productos[i].importe);
    }
    fclose(f);
    free(v_productos->productos);
    v_productos->size = 0;
}

Producto* buscar_producto_id(VectorProductos* v_productos, char* id_producto)
{
    int i;
    for (i = 0; i < v_productos->size; i++) {
        if (strcmp(v_productos->productos[i].id_producto, id_producto) == 0) {
            return &v_productos->productos[i];
        }
    }
    return NULL;
}

void listar_producto(Producto* producto)
{
    printf(
        "\n------------------------------------------------------\n"
        "Producto:  %s\n"
        "Nombre:     %s\n"
        "Descripción:  %s\n"
        "Categoría:  %s\n"
        "Gestor:  %s\n"
        "Stock:  %u\n"
        "Entrega:  %u\n"
        "Importe:  %.2f\n"
        "------------------------------------------------------\n",
        producto->id_producto,
        producto->nombre,
        producto->descripcion,
        producto->id_categoria,
        producto->id_gestor,
        producto->stock,
        producto->entrega,
        producto->importe);
}

void listar_productos(VectorProductos* v_productos)
{
    int i;
    for (i = 0; i < v_productos->size; i++) {
        listar_producto(&v_productos->productos[i]);
    }
}

void listar_productos_categoria(VectorProductos* v_productos, int id_categoria)
{
    int i;
    for (i = 0; i < v_productos->size; i++) {
        if (atoi(v_productos->productos[i].id_categoria) == id_categoria) {
            listar_producto(&v_productos->productos[i]);
        }
    }
}

unsigned listar_productos_nombre(VectorProductos* v_productos, char* nombre)
{
    int i;
    unsigned encontrados = 0;
    for (i = 0; i < v_productos->size; i++) {
        if (strcmp(v_productos->productos[i].nombre, nombre) == 0) {
            encontrados++;
            listar_producto(&v_productos->productos[i]);
        }
    }
    return encontrados;
}

void listar_productos_gestor(VectorProductos* v_productos, char* id_gestor)
{
    int i;
    for (i = 0; i < v_productos->size; i++) {
        if (strcmp(v_productos->productos[i].id_gestor, id_gestor) == 0) {
            listar_producto(&v_productos->productos[i]);
        }
    }
}

Producto* alta_producto(VectorProductos* v_productos, VectorCategorias* v_categorias, VectorAdminProv* v_adminprov)
{
    v_productos->productos = (Producto*)realloc(v_productos->productos, (v_productos->size + 1) * sizeof(Producto));
    if(v_productos->productos == NULL) {
        perror("\nError al reservar memoria\n");
        return NULL;
    }
    // El identificador del producto se generará automáticamente, convirtiendo el ID del último producto en entero y sumándole 1
    sprintf(v_productos->productos[v_productos->size].id_producto, "%07d", atoi(v_productos->productos[v_productos->size - 1].id_producto) + 1);
    leer_cadena("Introduzca el nombre del producto (16 caracteres): ", v_productos->productos[v_productos->size].nombre, 16);
    leer_cadena("Introduzca la descripción del producto (50 caracteres): ", v_productos->productos[v_productos->size].descripcion, 51);
    int valido = 0;
    char opcion_listado[2];
    while (!valido) {
        char id_categoria[5];
        leer_cadena("Introduzca el ID de la categoría del producto (4 dígitos): ", id_categoria, 5);
        Categoria* categoria = buscar_categoria_id(v_categorias, id_categoria);
        if (categoria != NULL) {
            strcpy(v_productos->productos[v_productos->size].id_categoria, id_categoria);
            valido = 1;
        } else {
            printf("\nCategoría no existente. Introduzca un ID de categoría válido.\n");
            leer_cadena("¿Desea listar las categorías existentes? (S/N): ", opcion_listado, 2);
            if (strcmp(opcion_listado, "S") == 0 || strcmp(opcion_listado, "s") == 0) {
                listar_categorias(v_categorias);
            }
        }
    }
    valido = 0;
    while (!valido) {
        char id_gestor[5];
        leer_cadena("Introduzca el ID del gestor del producto (4 dígitos): ", id_gestor, 5);
        AdminProv* adminprov = buscar_proveedor_id(v_adminprov, id_gestor);
        if (adminprov != NULL) {
            strcpy(v_productos->productos[v_productos->size].id_gestor, id_gestor);
            valido = 1;
        } else {
            printf("\nGestor no existente. Introduzca un ID de gestor válido.\n");
            leer_cadena("¿Desea listar los gestores existentes? (S/N): ", opcion_listado, 2);
            if (strcmp(opcion_listado, "S") == 0 || strcmp(opcion_listado, "s") == 0) {
                listar_provs(v_adminprov);
            }
        }
    }
    leer_unsigned("Introduzca el stock del producto: ", &v_productos->productos[v_productos->size].stock);
    leer_unsigned("Introduzca el número de días máximo para la entrega del producto (Compromiso de entrega): ", &v_productos->productos[v_productos->size].entrega);
    leer_real("Introduzca el importe del producto: ", &v_productos->productos[v_productos->size].importe);
    v_productos->size++;
    return &v_productos->productos[v_productos->size - 1];
}

// Buscará el producto a eliminar, parará cuando lo encuentre y reorganizará el vector
void baja_producto(VectorProductos* v_productos, char* id_producto)
{
    int i;
    for (i = 0; i < v_productos->size; i++) {
        if (strcmp(v_productos->productos[i].id_producto, id_producto) == 0) {
            break;
        }
    }
    if (i == v_productos->size) {
        printf("\nProducto no encontrado\n");
        return;
    }
    for (; i < v_productos->size - 1; i++) {
        v_productos->productos[i] = v_productos->productos[i + 1];
    }
    v_productos->size--;
    v_productos->productos = (Producto*)realloc(v_productos->productos, v_productos->size * sizeof(Producto));
    if(v_productos->productos == NULL) {
        perror("\nError al reservar memoria\n");
    }
}

Producto* modificar_producto(Producto* producto, VectorCategorias* v_categorias, VectorAdminProv* v_adminprov) {
    unsigned opcion;
    char opcion_listado[2];
    int valido;
    do {
        printf("\n1. Nombre: %s\n", producto->nombre);
        printf("2. Descripción: %s\n", producto->descripcion);
        printf("3. Categoría: %s\n", producto->id_categoria);
        printf("4. Gestor: %s\n", producto->id_gestor);
        printf("5. Stock: %u\n", producto->stock);
        printf("6. Entrega: %u\n", producto->entrega);
        printf("7. Importe: %.2f\n", producto->importe);
        printf("8. Salir\n");
        leer_unsigned("Seleccione el campo a modificar: ", &opcion);
        switch (opcion) {
            case 1:
                leer_cadena("Introduzca el nuevo nombre del producto (15 caracteres): ", producto->nombre, 16);
                break;
            case 2:
                leer_cadena("Introduzca la nueva descripción (50 caracteres): ", producto->descripcion, 51);
                break;
            case 3:
                valido = 0;
                while (!valido) {
                    char id_categoria[5];
                    leer_cadena("Introduzca el ID de la categoría del producto (4 dígitos): ", id_categoria, 5);
                    Categoria *categoria = buscar_categoria_id(v_categorias, id_categoria);
                    if (categoria != NULL) {
                        strcpy(producto->id_categoria, id_categoria);
                        valido = 1;
                    } else {
                        printf("\nCategoría no existente. Introduzca un ID de categoría válido.\n");
                        leer_cadena("¿Desea listar las categorías existentes? (S/N): ", opcion_listado, 2);
                        if (strcmp(opcion_listado, "S") == 0 || strcmp(opcion_listado, "s") == 0) {
                            listar_categorias(v_categorias);
                        }
                    }
                }
                break;
            case 4:
                valido = 0;
                while (!valido) {
                    char id_gestor[5];
                    leer_cadena("Introduzca el ID del gestor del producto (4 dígitos): ", id_gestor, 5);
                    AdminProv *adminprov = buscar_adminprov_id(v_adminprov, id_gestor);
                    if (adminprov != NULL) {
                        strcpy(producto->id_gestor, id_gestor);
                        valido = 1;
                    } else {
                        printf("\nGestor no existente. Introduzca un ID de gestor válido.\n");
                        leer_cadena("¿Desea listar los gestores existentes? (S/N): ", opcion_listado, 2);
                        if (strcmp(opcion_listado, "S") == 0 || strcmp(opcion_listado, "s") == 0) {
                            listar_provs(v_adminprov);
                        }
                    }
                }
                break;
            case 5:
                leer_unsigned("Introduzca el nuevo stock: ", &producto->stock);
                break;
            case 6:
                leer_unsigned("Introduzca la nueva entrega: ", &producto->entrega);
                break;
            case 7:
                leer_real("Introduzca el nuevo importe: ", &producto->importe);
                break;
            case 8:
                printf("\nSaliendo del menú de modificación de producto...\n");
                break;
            default:
                printf("\nOpción no válida\n");
                break;
        }
    } while (opcion != 8);

    return producto;
}
