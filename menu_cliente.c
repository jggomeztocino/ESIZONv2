#include <stdio.h>
#include "menu_cliente.h"
#include "cliente.h"
//#include "devoluciones.h"


/**
 * Muestra el menú de opciones para un cliente y gestiona las opciones seleccionadas.
 * @param v_devoluciones Puntero al array de estructuras Devolucion.
 * @param v_clientes Puntero al array de estructuras Cliente.
 * @param v_productos Puntero al array de estructuras productos.
 * @param v_descuentos Puntero al array de estructuras Descuento.
 * @param v_descuentosclientes Puntero al array de estructuras DescuentoCliente.
 * @param v_pedidos Puntero al array de estructuras pedidos.
 * @param v_productospedidos Puntero al array de estructuras ProductoPedido.
 * @param pos_cliente Posición del cliente en el array de clientes.
 * @param n_ Estructura que contiene los números de elementos de los distintos arrays.
 * @pre v_devoluciones, v_clientes, v_productos, v_descuentos, v_descuentosclientes, v_pedidos, v_productospedidos deben ser punteros válidos.
 * @pre pos_cliente debe ser una posición válida en el array de clientes.
 * @pre n_ debe ser una estructura válida que contiene los números de elementos de los arrays.
 * @post Se muestra el menú de opciones para el cliente.
 * @post Se permite al cliente seleccionar entre ver/modificar su perfil, ver productos, descuentos, pedidos, realizar devoluciones o cerrar sesión.
 * @post Se ejecuta la opción seleccionada por el cliente.
 * @post El bucle continúa hasta que el cliente selecciona la opción de cerrar sesión.
 */
void menu_cliente(Devolucion * v_devoluciones,Cliente * v_clientes,productos *v_productos,Descuento* v_descuentos, DescuentoCliente*v_descuentosclientes, pedidos *v_pedidos,ProductoPedido *v_productospedidos ,int pos_cliente){
    int seleccion;
    char seleccion_perfil;
    printf("Bienvenido, %s\n", v_clientes[pos_cliente].nombre_cliente);
    do {
        printf("--------------------------\n"
               "1. Perfil\n"
               "2. Productos\n"
               "3. Descuentos\n"
               "4. Pedidos\n" 
               "5. Devoluciones\n"
               "6. Cerrar sesión\n"
               "--------------------------\n");
        leer_entero("Introduce una opción [1-6]", &seleccion);
        switch (seleccion) {
            case 1:

                mostrar_perfil(v_clientes[pos_cliente]);
                
                do leer_caracter("¿Quieres modificar tu perfil? [s/n]", &seleccion_perfil);
                while (seleccion_perfil != 's' && seleccion_perfil != 'n');
                
                if (seleccion_perfil == 's')
                    modificar_perfil(v_clientes, pos_cliente, n_.n_clientes);
                break;

            case 2:
                 mostrar_productos_clientes(v_productos ,n_.n_productos);
                break;
            case 3:
                 mostrar_descuentos_cliente(v_descuentosclientes,v_descuentos ,n_.n_descuentosclientes, v_clientes[pos_cliente].id_cliente, n_.n_descuentos);
                break;
            case 4:

                 menu_pedidos_cliente(v_productos , v_pedidos, v_productospedidos,v_descuentosclientes,v_descuentos, &n_.n_productos ,&n_.n_pedidos, &n_.n_productospedidos,& n_.n_descuentosclientes,&n_.n_descuentos, v_clientes[pos_cliente].id_cliente);
                break;
            case 5:
                  devoluciones_clientes(v_devoluciones,v_productospedidos, v_pedidos,  n_.n_productospedidos, &n_.n_devoluciones, n_.n_pedidos, v_clientes[pos_cliente].id_cliente);
                break;
            case 6:
                break;
            default:
                printf("Opción no válida. Por favor, seleccione una opción válida.\n");

                break;
        }
    } while (seleccion != 6);
}