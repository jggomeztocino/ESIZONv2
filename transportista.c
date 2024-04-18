#include <stdio.h>
#include "transportista.h"
#include "stdio.h"
#include "stdlib.h"
/**
 * Muestra el perfil del transportista.
 * @param transportista Estructura que contiene la información del transportista.
 * @pre transportista debe ser una estructura válida.
 * @post Se muestra el perfil del transportista en la consola.
 */
void mostrar_perfil_transportista(Transportista  transportista){

    printf("SU PERFIL:\n"
           "---------------------------\n"
           "ID:     %i\n"
           "Nombre:  %s\n"
           "Email:  %s\n"
           "Contraseña:  %s\n"
           "Empresa:      %s\n"
           "Ciudad de reparto  %s\n"
           "---------------------------\n",
           transportista.id_transportista, transportista.nombre, transportista.email 
            , transportista.contrasena, transportista.nombre_empresa,transportista.ciudad);

}
/**
 * Permite al transportista modificar su perfil.
 * @param v_transport Puntero al array de estructuras Transportista.
 * @param pos_transportista Posición del transportista en el array.
 * @pre v_transport debe ser un puntero válido a un array de estructuras Transportista.
 * @pre pos_transportista debe ser una posición válida en el array.
 * @post Se muestra un menú de opciones para modificar el perfil del transportista.
 * @post Se permite al transportista seleccionar qué campo desea modificar y realizar la modificación.
 * @post El bucle continúa hasta que el transportista selecciona la opción de salir del menú.
 */
void modificar_perfil_transportista(Transportista* v_transport, int pos_transportista){

 int seleccion;
    char nombre[21],ciudad[21], nombre_empresa[21],
    email[31],contrasena[16];
    float cartera;
    do {
        printf("¿Qué deseas modificar?\n"
          "---------------------------\n"
           "1. Nombre:      \n"
           "2. Email:       \n"
           "3. Contraseña:  \n"
           "4. Empresa:     \n"
           "5. Ciudad:      \n"
           "6. Salir        \n"
           "---------------------------\n");
        leer_entero("Introduce una opción [1-5]", &seleccion);

        if (seleccion < 1 || seleccion > 9) {
            puts("Introduzca una opción válida\n");
            continue; // Vuelve al inicio del bucle para solicitar una nueva opción
        }
        
        switch (seleccion) {
            case 1:
                leer_cadena("Introduzca su nuevo nombre\n", nombre, 21);
                strcpy(v_transport[pos_transportista].nombre, nombre);
                break;
            case 2:
                leer_cadena("Introduzca su nuevo email\n", email, 31);
                strcpy(v_transport[pos_transportista].email, email);
                break;
            case 3:
                leer_cadena("Introduzca su nueva contraseña\n", contrasena, 16);
                strcpy(v_transport[pos_transportista].contrasena, contrasena);
                break;
            case 4:
                leer_cadena("Introduzca su nueva provincia\n", nombre_empresa, 21);
                strcpy(v_transport[pos_transportista].nombre_empresa, nombre_empresa);
                break;
            case 5:
                leer_cadena("Introduzca su nueva ciudad de reparto\n", ciudad, 21);
                strcpy(v_transport[pos_transportista].ciudad, ciudad);
            case 6:
                break;
            default:
                puts("Introduzca una opción valida \n");
                break;
        }
        if (seleccion > 1 && seleccion < 8)
            mostrar_perfil_transportista(v_transport[pos_transportista]); // muestra el perfil modificado
    } while (seleccion != 6);
}

/**
 * Marcar un producto como entregado por un transportista.
 *
 * @param v_pedidos Puntero al array de estructuras pedidos.
 * @param v_productospedidos Puntero al array de estructuras ProductoPedido.
 * @param n_productos_pedidos Número de elementos en v_productospedidos.
 * @param id_producto Identificador del producto a marcar como entregado.
 * @param transport Estructura Transportista que representa al transportista actual.
 * @param n_pedidos Número de elementos en v_pedidos.
 *
 * @pre v_pedidos debe ser un puntero válido a un array de estructuras pedidos.
 * @pre v_productospedidos debe ser un puntero válido a un array de estructuras ProductoPedido.
 * @pre n_productos_pedidos debe contener el número actual de elementos en v_productospedidos.
 * @pre id_producto debe ser un valor válido.
 * @pre transport debe ser una estructura válida de tipo Transportista.
 * @pre n_pedidos debe contener el número actual de elementos en v_pedidos.
 *
 * @post El estado del producto asociado al id_producto se actualiza según la acción realizada.
 * @post Se muestra un mensaje indicando si el producto fue marcado como entregado o no.
 */
void marcar_producto_entregado(pedidos* v_pedidos, ProductoPedido* v_productospedidos, int n_productos_pedidos, int id_producto, Transportista transport, int n_pedidos) {
    // Variable booleana para indicar si se encontró el producto
    bool encontrado = false;
    int i;
    // Buscar el producto en la lista de productos pedidos
    for (i = 0; i < n_productos_pedidos; i++) {
        // Verificar si el producto está en la lista y si está asignado al transportista actual
        if (v_productospedidos[i].id_producto == id_producto && v_productospedidos[i].id_transportista == transport.id_transportista) {
            // Obtener el id del pedido asociado al producto
            int id_pedido = v_productospedidos[i].id_pedido;

            // Buscar la posición del pedido en la lista de pedidos
            int pos_pedido = buscar_pos_pedido(v_pedidos, n_pedidos, id_pedido);

            // Verificar si se encontró el pedido y si es para entrega a domicilio
            if (pos_pedido != -1 && strcmp(v_pedidos[pos_pedido].lugar_entrega, "domicilio") == 0) {
                // Preguntar al transportista si pudo realizar la entrega a domicilio
                char respuesta;
                printf("¿Pudo realizar la entrega a domicilio del producto con ID %d? [s/n]: ", id_producto);
                
                leer_caracter("", &respuesta);
                if (respuesta == 's' || respuesta == 'S') {
                    // Marcar el producto como entregado actualizando su estado
                    strcpy(v_productospedidos[i].estado_pedido, "entregado");
                    printf("El producto con ID %d ha sido marcado como entregado.\n", id_producto);
                } else {
                    // No se pudo realizar la entrega, asignar estado "transportista"
                    strcpy(v_productospedidos[i].estado_pedido, "transportista");
                    printf("No se pudo realizar la entrega a domicilio del producto con ID %d. Se ha asignado estado 'transportista'.\n", id_producto);
                }
                encontrado = true;
            } else {
                printf("No se puede marcar el producto con ID %d como entregado. El pedido no es para entrega a domicilio o no se encontró el pedido.\n", id_producto);
            }
            break; // Salir del bucle una vez que se haya encontrado y actualizado el producto
        }
    }

    // Si no se encontró el producto en la lista
    if (!encontrado) {
        printf("No se encontró el producto con ID %d asignado al transportista.\n", id_producto);
    }
}

/**
 * Gestiona las operaciones de reparto de productos asignados a un transportista.
 *
 * Esta función proporciona un menú de opciones para que un transportista pueda gestionar
 * las operaciones de reparto de productos asignados para entrega a domicilio. Permite ver la
 * lista de productos asignados y marcar la entrega a domicilio de un producto específico.
 *
 * @param v_pedidos Puntero al array de estructuras pedidos.
 * @param transport Estructura Transportista que representa al transportista actual.
 * @param v_productospedidos Puntero al array de estructuras ProductoPedido.
 * @param n_productos_pedidos Número de elementos en v_productospedidos.
 * @param n_pedidos Número de elementos en v_pedidos.
 *
 * @pre v_pedidos debe ser un puntero válido a un array de estructuras pedidos.
 * @pre transport debe ser una estructura válida de tipo Transportista.
 * @pre v_productospedidos debe ser un puntero válido a un array de estructuras ProductoPedido.
 * @pre n_productos_pedidos debe contener el número actual de elementos en v_productospedidos.
 * @pre n_pedidos debe contener el número actual de elementos en v_pedidos.
 *
 * @post Se muestra un menú de opciones para gestionar las operaciones de reparto de productos.
 * @post Se ejecutan las operaciones seleccionadas por el transportista hasta que elija salir del menú.
 */
void repartos(pedidos * v_pedidos ,Transportista transport, ProductoPedido *v_productospedidos, int n_productos_pedidos, int n_pedidos) {
    int opcion;
    int id_producto;
    int i;
    do {
        printf("\n--- Menú de Repartos ---\n");
        printf("1. Ver lista de productos asignados para entrega domicilio\n");
        printf("2. Marcar entrega a domicilio\n");
        printf("3. Salir\n");
        leer_entero("Seleccione una opción: ",&opcion);

        switch (opcion) {
            case 1:
                printf("\nLista de productos asignados para entrega al transportista %s:\n", transport.nombre);
                for (i = 0; i < n_productos_pedidos; i++) {
                    // Verificar si el producto está asignado al transportista actual
                    if (v_productospedidos[i].id_transportista == transport.id_transportista) {
                        printf("Producto %d:\n", i + 1);
                        printf("ID Pedido: %d\n", v_productospedidos[i].id_pedido);
                        printf("ID Producto: %d\n", v_productospedidos[i].id_producto);
                        printf("Unidades: %d\n", v_productospedidos[i].num_unidades);
                        imprimir_cadena_y_fecha("Fecha prevista de entrega: ", v_productospedidos[i].fecha_prevista_entrega);
                        printf("-----------------------------------\n");
                    }
                }
                break;
          case 2:
                    // Leer el ID del producto a marcar como entregado
                    
                    leer_entero("Ingrese el ID del producto a marcar como entregado a domicilio: ", &id_producto);

                    // Llamar a la función para marcar el producto como entregado
                    marcar_producto_entregado(v_pedidos,v_productospedidos,  n_productos_pedidos, id_producto , transport,n_pedidos) ;
                    break;
            case 3:
                printf("Saliendo del menú de repartos...\n");
                break;
            default:
                printf("Opción no válida. Por favor, seleccione una opción válida.\n");
                break;
        }
    } while (opcion != 3);
}




int seleecion_transportista(Transportista* transportistas, int n_transportistas) {
    // Verificar si hay transportistas en el vector
    if (n_transportistas <= 0) {
        // No hay transportistas, devolver -1 como índice inválido
        return -1;
    }
    
    // Inicializar la semilla para la función rand()
    srand(time(NULL));
    
    // Generar un índice aleatorio dentro del rango de 0 a n_transportistas - 1
    int indice_aleatorio;
    
    do {
        indice_aleatorio = rand() % n_transportistas;
    } while (transportistas[indice_aleatorio].id_transportista != 0 && indice_aleatorio>=0 && indice_aleatorio< n_transportistas ); // Comprobar si el id es válido
    
    // Devolver el índice aleatorio
    return indice_aleatorio;
}