#include <stdio.h>
#include "menu_cliente.h"

////A)Perfil mostrar perfil del cliente y preguntarle si quiere modificar, llamar a modificar
//    //Mostrar los datos del perfil del cliente. haz la cabecera de la funcion con los parametros necesarios
void perfil_cliente(Cliente *cliente)
{
    // Comienza a mostrar la informacion del cliente
    printf("Nombre: %s\n", cliente->nombre_cliente);
    printf("Direccion: %s\n", cliente->direccion_cliente);
    printf("Poblacion: %s\n", cliente->poblacion);
    printf("Provincia: %s\n", cliente->provincia);
    printf("Email: %s\n", cliente->email);
    printf("Contrasena: %s\n", cliente->contrasena);
    printf("Cartera: %.2f\n", cliente->cartera);
    // Preguntar si quiere modificar
    char respuesta;
    printf("¿Desea modificar su perfil? (s/n): ");
    leer_caracter("Introduce una opcion valida", &respuesta);
    if (respuesta == 's' || respuesta == 'S')
    {
        modificar_cliente(cliente);
    }
}





// Gestionar la recogida de un pedido depositado en un locker antes de la fecha de caducidad
/*
 recoger_pedido(cliente, v_pedidos, v_productos_pedido, id_locker,num_compartimento);
 */
void recoger_pedido(Cliente *cliente, VectorPedidos v_pedidos, ProductoPedido *producto,Locker *locker,CompartimentoLocker *compartimento)
{
    // Comprobar si el producto esta en estado enLocker
    if (producto->estado != 4)
    {
        printf("El producto no esta en el locker\n");
        return;
    }
    // Comprobar si el producto pertenece al cliente
    if (strcmp(producto->id_pedido, cliente->id_cliente) != 0)
    {
        printf("El producto no pertenece al cliente\n");
        return;
    }
    if (comparar_fechas(obtener_fecha_actual(), producto->fecha_entrega_devolucion) > 0)
    {
        printf("La fecha de caducidad ha pasado\n");
        return;
    }
    // Cambiar el estado del compartimento a vacio
    compartimento->estado = 0;
    //Actualizar el numero de compartimentos ocupados en locker
    locker->num_compartimentos_ocupados--;
    // Cambiar el estado del producto a entregado
    producto->estado = 6;
}

// Funcion que pregunta si quiere mirar la informacion de todos sus pedidos o de uno concreto por id
void consultar_pedido(Cliente *cliente, VectorPedidos v_pedidos, VectorProductosPedido v_productos_pedido)
{
    // Mostrar los pedidos del cliente
    listar_pedidos_cliente(&v_pedidos, cliente->id_cliente);
    // Preguntar si quiere ver un pedido en concreto
    char respuesta;
    printf("¿Desea ver un pedido en concreto? (s/n): ");
    leer_caracter("Introduce una opcion valida", &respuesta);
    if (respuesta == 's' || respuesta == 'S')
    {
        char id_pedido[8];
        leer_cadena("Introduce el id del pedido: ", id_pedido, 8);
        if (pertenece_pedido(&v_productos_pedido, id_pedido, cliente->id_cliente))
        {
            listar_productos_pedido(&v_productos_pedido, id_pedido);
        }
        else
        {
            printf("El pedido no pertenece al cliente\n");
        }
    }
}

// Mostrará las distintas opciones de realizar un pedido , gestionar la recogida de alguno de un locker o consultar
// el estado de cada uno de los productos de un pedido concreto
void gestionar_pedidos(Cliente *cliente)
{
    // Cargar los pedidos , devoluciones y productos pedidos
    VectorPedidos v_pedidos;
    VectorCompartimentos v_compartimentos;
    VectorDevoluciones v_devoluciones;
    VectorProductosPedido v_productos_pedido;
    VectorLockers v_lockers;
    VectorDescuentos v_descuentos;
    VectorDescuentosClientes v_descuentos_cliente;
    VectorProductos v_productos;

    cargar_pedidos(&v_pedidos);
    cargar_devoluciones(&v_devoluciones);
    cargar_productos_pedido(&v_productos_pedido);
    cargar_lockers(&v_lockers);
    cargar_compartimentos(&v_compartimentos);
    cargar_descuentos(&v_descuentos);
    cargar_descuentos_clientes(&v_descuentos_cliente);
    cargar_productos(&v_productos);
    unsigned opcion;
    do
    {
        printf("\n\n");
        printf("1. Realizar un pedido\n");
        printf("2. Recoger un pedido\n");
        printf("3. Consultar un pedido\n");
        printf("4. Salir\n");
        printf("Introduce una opcion: ");
        leer_entero("Introduce una opcion valida", &opcion);
        switch (opcion)
        {
        case 1:
            realizar_pedido( cliente, v_pedidos, v_productos_pedido, v_lockers, v_compartimentos, v_descuentos, v_descuentos_cliente, v_productos);
            break;
        case 2:

            //Solicitar id_locker y numero de compartimento
            char id_locker[11];
            unsigned num_compartimento;
            unsigned cod_compartimento;
            leer_cadena("Introduce el id del locker: ", id_locker, 11);
            //comprueba si el locker existe
            Locker *locker = buscar_locker_id(&v_lockers, id_locker);
            if (locker == NULL)
            {
                printf("El locker no existe\n");
                break;
            }
            leer_entero("Introduce el numero de compartimento: ", &num_compartimento);
            //comprueba si el compartimento existe
            CompartimentoLocker *compartimento = buscar_compartimento(&v_compartimentos, id_locker, num_compartimento);
            if (compartimento == NULL)
            {
                printf("El compartimento no existe\n");
                break;
            }
            //solicitar codigo del compartimento
                leer_unsigned( "Introduce el codigo del compartimento: ", &cod_compartimento);
            //comprueba si el codigo es correcto
            if (cod_compartimento != compartimento->cod_locker)
            {
                printf("El codigo no es correcto\n");
                break;
            }
            //COmprobar si se puede recoger
            if (compartimento->estado == 0)
            {
                printf("El compartimento esta vacio\n");
                break;
            }
            //buscar el producto pedido
            ProductoPedido *producto = buscar_producto_pedido_por_compartimento(&v_productos_pedido, id_locker, num_compartimento);

            recoger_pedido(cliente, v_pedidos, producto,locker,compartimento);
            break;
        case 3:
            consultar_pedido(cliente, v_pedidos, v_productos_pedido);
            break;
        case 4:
            break;
        default:
            printf("Opcion no valida\n");
            break;
        }
    } while (opcion != 4);

    // Guardar
    guardar_pedidos(&v_pedidos);
    guardar_devoluciones(&v_devoluciones);
    guardar_productos_pedido(&v_productos_pedido);
    guardar_lockers(&v_lockers);
    guardar_compartimentos(&v_compartimentos);
    guardar_descuentos(&v_descuentos);
    guardar_descuentos_clientes(&v_descuentos_cliente);
    guardar_productos(&v_productos);
}



// FUncion que hace que aparezca un menu y pregunta que quiere hacer el cliente
void gestionar_devolucion(Cliente *cliente)
{
    VectorPedidos v_pedidos;
    cargar_pedidos(&v_pedidos);
    VectorProductosPedido v_productos_pedido;
    cargar_productos_pedido(&v_productos_pedido);
    VectorDevoluciones v_devoluciones;
    cargar_devoluciones(&v_devoluciones);

    unsigned opcion;
    do
    {
        printf("\n\n");
        printf("1. Realizar devolucion\n");
        printf("2. Consultar devoluciones\n");
        printf("3. Salir\n");
        printf("Introduce una opcion: ");
        leer_entero("Introduce una opcion valida", &opcion);
        switch (opcion)
        {
        case 1:
            realizar_devolucion(cliente, v_pedidos, v_productos_pedido, v_devoluciones);
            break;
        case 2:
            mostrar_devoluciones_pendientes(&v_pedidos, &v_devoluciones, cliente->id_cliente);
            break;
        case 3:
            break;
        default:
            printf("Opcion no valida\n");
            break;
        }
    } while (opcion != 3);
    guardar_devoluciones(&v_devoluciones);
    guardar_pedidos(&v_pedidos);
    guardar_devoluciones(&v_devoluciones);
    guardar_productos_pedido(&v_productos_pedido);
}

// Menu del cliente al estilo de menu_administrador.c, contando que se le pasan los vectores necesarios y tambien tienes como parametro de entrada el cliente
// que ha iniciado sesion
void menu_cliente(Cliente *cliente)
{

    unsigned opcion;
    do
    {
        printf("\n\n");
        printf("1. Perfil\n");
        printf("2. Productos\n");
        printf("3. Descuentos\n");
        printf("4. Pedidos\n");
        printf("5. Devoluciones\n");
        printf("6. Salir del sistema\n");
        printf("Introduce una opcion: ");
        leer_entero("Introduce una opcion valida", &opcion);
        switch (opcion)
        {
        case 1:
            perfil_cliente(cliente);
            break;
        case 2:
            listado_productos();
            break;
        case 3:
            //cargar vector descuentos y descuentos cliente
            VectorDescuentos v_descuentos;
            VectorDescuentosClientes v_descuentos_cliente;
            cargar_descuentos(&v_descuentos);
            cargar_descuentos_clientes(&v_descuentos_cliente);

            mostrar_descuentos_cliente(&v_descuentos_cliente, &v_descuentos, cliente->id_cliente);

            guardar_descuentos(&v_descuentos);
            guardar_descuentos_clientes(&v_descuentos_cliente);
            break;
        case 4:
            gestionar_pedidos(cliente);
            break;
        case 5:
            gestionar_devolucion(cliente);
            break;
        case 6:
            break;
        default:
            printf("Opcion no valida\n");
            break;
        }
    } while (opcion != 6);
}