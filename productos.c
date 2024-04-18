#include "stdio.h"
#include <string.h>
#include "productos.h"




/**
 * Muestra información sobre productos según la opción seleccionada por el cliente.
 * @param v_productos Puntero al array de estructuras productos.
 * @param n_productos Número de elementos en v_productos.
 * @pre v_productos debe ser un puntero válido a un array de estructuras productos.
 * @pre n_productos debe ser un número válido de elementos en v_productos.
 * @post Se muestra un menú para que el cliente seleccione cómo buscar productos.
 * @post Se permite al cliente buscar productos por nombre, por categoría o salir del menú.
 * @post Se muestra la información de los productos encontrados según la opción seleccionada por el cliente.
 */
void mostrar_productos_clientes(productos* v_productos, int n_productos){
 int opcion;
    char nombre_buscar[16];
    int id_categoria_buscar;
    int i;
    int encontrado = 0; // Bandera para verificar si se encontró el producto

    while (1) { //Hace que el bucle sea infinito
        printf("Seleccione una opción:\n");
        printf("1. Buscar producto por nombre\n");
        printf("2. Buscar productos por categoría\n");
        printf("3. Salir\n");
        leer_entero("Introduce una opción [1-5]", &opcion);
       

        switch (opcion) {
            case 1:
                leer_cadena("Introduce el nombre del producto:", nombre_buscar, 16);
                for (i = 0; i < n_productos; ++i) {
                    if (strcmp(v_productos[i].nombre, nombre_buscar) == 0) {
                        encontrado = 1;
                        printf("Producto encontrado:\n");
                        printf("Nombre: %s\n", v_productos[i].nombre);
                        printf("Descripción: %s\n", v_productos[i].descripcion);
                        printf("ID de categoría: %d\n", v_productos[i].id_categoria);
                        printf("ID de gestor: %d\n", v_productos[i].id_gestor);
                        printf("Stock: %d\n", v_productos[i].stock);
                        printf("Envío: %d\n", v_productos[i].envio);
                        printf("Importe: %d\n", v_productos[i].importe);
                    }
                }
                if (!encontrado) {
                    printf("El producto con el nombre \"%s\" no existe.\n", nombre_buscar);
                }
                break;
            case 2:
                
                leer_entero("Ingrese el ID de la categoría de productos a buscar: ", &id_categoria_buscar);
                 for (i = 0; i < n_productos; ++i) {
                    if (v_productos[i].id_categoria == id_categoria_buscar) {
                        encontrado = 1;
                        printf("Nombre: %s\n", v_productos[i].nombre);
                    }
                }
                if (!encontrado) {
                    printf("No se encontraron productos en la categoría con ID %d.\n", id_categoria_buscar);
                }
                break;
            case 3:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Por favor, seleccione una opción válida.\n");
                break;
        }
    }
    


}

/**
 * Busca la posición de un producto en el array de productos por su identificador.
 * @param v_productos Puntero al array de estructuras productos.
 * @param n_productos Número de elementos en v_productos.
 * @param id_producto Identificador del producto a buscar.
 * @return La posición del producto si se encuentra, -1 si no se encuentra.
 * @pre v_productos debe ser un puntero válido a un array de estructuras productos.
 * @pre n_productos debe ser un número válido de elementos en v_productos.
 * @post Devuelve la posición del producto en el array si se encuentra, -1 si no se encuentra.
 */
int buscar_pos_producto(productos* v_productos, int n_productos, int id_producto) {
    int i;
    for (i = 0; i < n_productos; i++) {
        if (v_productos[i].identificador == id_producto) {
            return i; // Devuelve la posición del producto si se encuentra
        }
    }
    return -1; // Devuelve -1 si no lo encuentra
}
