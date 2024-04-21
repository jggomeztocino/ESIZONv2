#include <stdio.h>
#include "menu_cliente.h"


////A)Perfil mostrar perfil del cliente y preguntarle si quiere modificar, llamar a modificar
//    //Mostrar los datos del perfil del cliente. haz la cabecera de la funcion con los parametros necesarios
void perfil_cliente(Cliente* cliente)
{
    //Comienza a mostrar la informacion del cliente
    printf("Nombre: %s\n", cliente->nombre_cliente);
    printf("Direccion: %s\n", cliente->direccion_cliente);
    printf("Poblacion: %s\n", cliente->poblacion);
    printf("Provincia: %s\n", cliente->provincia);
    printf("Email: %s\n", cliente->email);
    printf("Contrasena: %s\n", cliente->contrasena);
    printf("Cartera: %.2f\n", cliente->cartera);
    //Preguntar si quiere modificar
    char respuesta;
    printf("¿Desea modificar su perfil? (s/n): ");
    leer_caracter( "Introduce una opcion valida",&respuesta);
    if (respuesta == 's' || respuesta == 'S')
    {
        modificar_cliente(cliente);
    }

}

//Menu que pregunta si se quiere listar los productos por id o categoria
void listado_productos()
{

    VectorProductos v_productos;
    cargar_productos(&v_productos);

    printf( "1. Buscar por id\n");
    printf( "2. Buscar por categoria\n");
    int opcion;
    leer_entero("Introduce una opcion valida",&opcion);
    if (opcion == 1)
    {
        char id_producto[8];
        leer_cadena("Introduce el id del producto: ", id_producto, 8);
        Producto* producto = buscar_producto_id(&v_productos, id_producto);
        if (producto == NULL)
        {
            printf("Producto no encontrado\n");
        }
        else
        {
            listar_producto(producto);
        }
    }
    else if (opcion == 2)
    {
        int id_categoria;
        leer_entero("Introduce el id de la categoria: ", &id_categoria);
        listar_productos_categoria(&v_productos, id_categoria);
    }
    else
    {
        printf("Opcion no valida\n");
    }
    guardar_productos(&v_productos);
}

//Muestra los descuentos del cliente
void mostrar_descuentos(Cliente* cliente)
{
    VectorDescuentosClientes v_descuentosclientes;
    cargar_descuentos_clientes(&v_descuentosclientes);
    VectorDescuentos v_descuentos;
    cargar_descuentos(&v_descuentos);
    mostrar_descuentos_cliente(&v_descuentosclientes, &v_descuentos, cliente->id_cliente);
    guardar_descuentos_clientes(&v_descuentosclientes);
    guardar_descuentos(&v_descuentos);
}

//Aplica el descuento al importe de un pedido y lo devuelve con el descuento aplicado o no si no se puede aplicar el descuento al importe del pedido
//Comprobar si es aplicable , si está activo y si no ha caducado la fecha de caducidad
//Devolver mensajes en caso de que no se haya podido aplicar , en caso de aplicarlo actualizar a estado correspondiente. El descuento se aplica restando el importe del descuento al importe del pedido
float aplicar_descuento_a_importe( VectorDescuentosClientes* v_descuentos_cliente, VectorDescuentos* v_descuentos, char* id_cliente, char* id_descuento, float importe)
{

    DescuentoCliente* descuento_cliente = obtener_descuento_cliente(v_descuentos_cliente, id_cliente, id_descuento);
    if (descuento_cliente == NULL)
    {
        printf("Descuento no encontrado\n");
        return importe;
    }
    Descuento* descuento = obtener_descuento(v_descuentos, id_descuento);
    if (descuento == NULL)
    {
        printf("Descuento no encontrado\n");
        return importe;
    }
    if (strcmp(descuento->estado, "inactivo") == 0)
    {
        printf("Descuento inactivo\n");
        return importe;
    }
    if (strcmp(descuento->aplicable, "esizon") == 0)
    {
        printf("Descuento no aplicable\n");
        return importe;
    }
    Fecha fecha_actual;
    fecha_actual = obtener_fecha_actual();
    if (comparar_fechas(fecha_actual, descuento_cliente->fecha_caducidad) > 0)
    {
        printf("Descuento caducado\n");
        return importe;
    }
    importe -= descuento->importe;
    descuento_cliente->estado = 1;
    return importe;
}

//Funcion para realizar un pedido,
void realizar_pedido( Cliente* cliente, VectorPedidos v_pedidos, VectorProductosPedido v_productos_pedido, VectorLockers v_lockers, VectorCompartimentos v_compartimentos, VectorDescuentos v_descuentos, VectorDescuentosClientes v_descuentos_cliente, VectorProductos v_productos)
{

   //Crear un pedido temporal
   Pedido pedido_temp;
    float importe =0;
    unsigned num_unidades;
    char id_pedido[8];
    unsigned opcion_lugar;
    sprintf(id_pedido, "%07d", atoi(v_pedidos.pedidos[v_pedidos.size - 1].id_pedido) + 1);

    strcpy(pedido_temp.id_pedido, id_pedido);
    //Obtener la fecha actual
    pedido_temp.fecha = obtener_fecha_actual();
    //Copiar el id del cliente
    strcpy(pedido_temp.id_cliente, cliente->id_cliente);

    //Crear un vector de producos pedido temporal e inicializar su tamaño a 0 y su puntero a NULL
    VectorProductosPedido v_productos_pedido_temp;
    v_productos_pedido_temp.size = 0;
    v_productos_pedido_temp.productos_pedido = NULL;

    //Crear un producto pedido temporal
    ProductoPedido producto_pedido_temp;
    strcpy(producto_pedido_temp.id_pedido, id_pedido);

    //Preguntar si desea entrega del pedido a domicilio o en un locker
    do
    {
        printf("1. Domicilio\n");
        printf("2. Locker\n");
        leer_unsigned("Introduce una opcion valida",&opcion_lugar);
    } while (opcion_lugar != 1 && opcion_lugar != 2);


    //Listar los productos
    listar_productos(&v_productos);

   //Pedirle al cliente que introduzca el id del producto
    do {
        char id_producto[8];
        leer_cadena("Introduce el id del producto: ", id_producto, 8);
        // Comprobar que el producto existe
        Producto *producto = buscar_producto_id(&v_productos, id_producto);
        if (producto == NULL) {
            printf("Producto no encontrado\n");

        } else { //Si el producto existe pedirle el numero de unidades
            leer_unsigned("Introduce el numero de unidades: ", &num_unidades);
            if (num_unidades < producto->stock) {
                printf("No hay suficiente stock\n");
            } else { // Si hay suficiente stock rellenar los datos del producto pedido temporal
                //Rellenar los datos de un producto pedido temporal
                strcpy(producto_pedido_temp.id_producto, id_producto);
                producto_pedido_temp.num_unidades = num_unidades;
                producto_pedido_temp.fecha_prevista_entrega = crearFecha(pedido_temp.fecha.dia, pedido_temp.fecha.mes,
                                                                         pedido_temp.fecha.anio);
                producto_pedido_temp.importe = producto->importe * num_unidades;
                producto_pedido_temp.estado = 1;
                strcpy(producto_pedido_temp.id_transportista, "");
                strcpy(producto_pedido_temp.id_locker, "");
                strcpy(producto_pedido_temp.cod_locker, "");
                producto_pedido_temp.fecha_entrega_devolucion = crearFecha(0, 0, 0);
                //Aumentar el numero de productos en el vector de productos pedido temporal
                v_productos_pedido_temp.size++;
                //Incluir el producto pedido temporal en el vector de productos pedido temporal
                //COmprueba que se haya podido realizar la reserva de memoria

                ProductoPedido *temp = (ProductoPedido *) realloc(v_productos_pedido_temp.productos_pedido,v_productos_pedido_temp.size *sizeof(ProductoPedido));
                if (temp == NULL) {
                    perror("Error al reservar memoria");
                    return;
                }
                v_productos_pedido_temp.productos_pedido = temp;
                v_productos_pedido_temp.productos_pedido[v_productos_pedido_temp.size - 1] = producto_pedido_temp;
                //Actualizar el importe total del pedido
                importe += producto_pedido_temp.importe;

            }

            //Preguntar si quiere añadir otro producto
            char respuesta;
            printf("¿Desea añadir otro producto? (s/n): ");
            leer_caracter("Introduce una opcion valida",&respuesta);
            if (respuesta == 'n' || respuesta == 'N') {
                break;
            }

        }
    } while (1); //Se han terminado de añadir productos

    //Mostrar el importe total y  el numero de productos solicitados (size del vector temporal)

    printf("Importe total: %.2f\n", importe);
    printf("Numero de productos: %u\n", v_productos_pedido_temp.size);

    //Preguntar si desea aplicar un descuento
    char respuesta;
    printf("¿Desea aplicar un descuento? (s/n): ");
    leer_caracter("Introduce una opcion valida",&respuesta);
    if (respuesta == 's' || respuesta == 'S') {
        //Mostrar los descuentos del cliente EN CONCRETO
        mostrar_descuentos_cliente(&v_descuentos_cliente, &v_descuentos, cliente->id_cliente);
        //Pedirle que introduzca el id del descuento
        char id_descuento[11];
        leer_cadena("Introduce el id del descuento: ", id_descuento, 11);
        //Aplicar el descuento al importe del pedido
        printf("Importe antes del descuento: %.2f\n", importe);
        importe = aplicar_descuento_a_importe(&v_descuentos_cliente, &v_descuentos, cliente->id_cliente, id_descuento, importe);
        //Copiar el id del descuento en el pedido temporal
        strcpy(pedido_temp.id_descuento, id_descuento);

        printf("Su nuevo importe es de %.2f\n", importe);
    }else{
        //Si no se aplica descuento copiar un string vacio en el id del descuento del pedido temporal
        strcpy(pedido_temp.id_descuento, " ");

    }

    //Restar el importe a la cartera del cliente indicando que se está procediendo al pago , en caso de no tener suficiente saldo mostrar un mensaje
    if (cliente->cartera < importe) {
        printf("No tiene suficiente saldo\n");

    } else {
        cliente->cartera -= importe;
        printf("Se ha procedido al pago\n");

        //Añadir al vector de pedidos el pedido temporal
        Pedido *temp = (Pedido *) realloc(v_pedidos.pedidos, (v_pedidos.size + 1) * sizeof(Pedido));
        if (temp == NULL) {
            perror("Error al reservar memoria");
            return;
        }
        v_pedidos.pedidos = temp;
        v_pedidos.pedidos[v_pedidos.size] = pedido_temp;
        v_pedidos.size++;

    }
}




//Gestionar la recogida de un pedido depositado en un locker antes de la fecha de caducidad
/*
 opción para el cliente es la recogida de un pedido que haya sido depositado en
un ESILocker antes de la fecha de caducidad, para ello se le debe mostrar la opción
solicitándole el código locker asociado. Una vez introducido, el sistema mostrará un
mensaje en pantalla indicando el número de compartimento que se ha abierto. El estado
de los productos recogidos, en consecuencia, se debe actualizar

 */
void recoger_pedido(Cliente* cliente,VectorPedidos v_pedidos, VectorProductosPedido v_productos_pedido, VectorLockers v_lockers, VectorCompartimentos v_compartimentos)
{

      //Mostrar los pedidos del cliente que se encuentran en lockers
    listar_pedidos_locker_decliente(&v_pedidos, cliente->id_cliente);
      //Pedirle que seleccione un pedido para recogerlo
    char id_pedido[8];
    leer_cadena("Introduce el id del pedido a recoger: ", id_pedido, 8);
    //Comprobar que el pedido corresponde al cliente , se encuentra en locker y no ha caducado la fecha de recogida
    if (pertenece_pedido(&v_productos_pedido, id_pedido, cliente->id_cliente))
    {
        Pedido* pedido = buscar_pedido_por_id(&v_pedidos, id_pedido);
       //Comprobar que el pedido se encuentra en un locker
        if (pedido->lugar == 2)
        {
           //Comprobar que estamos en una fecha valida para recogerlo
            Fecha fecha_actual;
            fecha_actual = obtener_fecha_actual();
            if (comparar_fechas(fecha_actual, pedido->fecha) <= 0)
            {
                char codigo_locker[11];
                leer_cadena("Introduce el código del locker: ", codigo_locker, 11);
                Locker* locker = buscar_locker_id(&v_lockers, codigo_locker);
                if (locker != NULL)
                {
                    CompartimentoLocker* compartimento = buscar_compartimento_id(&v_compartimentos, codigo_locker, 1);
                    if (compartimento != NULL)
                    {
                        printf("Se ha abierto el compartimento %u\n", compartimento->n_compartimento);
                        //Actualizar el estado de los productos recogidos
                        int i;
                        for (i = 0; i < v_productos_pedido.size; i++)
                        {
                            if (strcmp(v_productos_pedido.productos_pedido[i].id_pedido, id_pedido) == 0)
                            {
                                v_productos_pedido.productos_pedido[i].estado = 5;
                                v_productos_pedido.productos_pedido[i].fecha_entrega_devolucion = fecha_actual;
                            }
                        }
                    }
                    else
                    {
                        printf("El locker no tiene compartimentos\n");
                    }
                }
                else
                {
                    printf("Locker no encontrado\n");
                }
            }
            else
            {
                printf("Fecha de recogida caducada\n");
            }
        }
        else
        {
            printf("El pedido no se encuentra en un locker\n");
        }
}
    else
    {
        printf("El pedido no pertenece al cliente\n");
    }

}

//Funcionn que pregunta si quiere mirar la informacion de todos sus pedidos o de uno concreto por id
void consultar_pedido( Cliente* cliente, VectorPedidos v_pedidos, VectorProductosPedido v_productos_pedido)
{
    //Mostrar los pedidos del cliente
    listar_pedidos_cliente(&v_pedidos, cliente->id_cliente);
    //Preguntar si quiere ver un pedido en concreto
    char respuesta;
    printf("¿Desea ver un pedido en concreto? (s/n): ");
    leer_caracter("Introduce una opcion valida",&respuesta);
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

//Mostrará las distintas opciones de realizar un pedido , gestionar la recogida de alguno de un locker o consultar
//el estado de cada uno de los productos de un pedido concreto
void gestionar_pedidos(Cliente* cliente)
{
    //Cargar los pedidos , devoluciones y productos pedidos
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
    int opcion;
    do
    {
        printf("\n\n");
        printf("1. Realizar un pedido\n");
        printf("2. Recoger un pedido\n");
        printf("3. Consultar un pedido\n");
        printf("4. Salir\n");
        printf("Introduce una opcion: ");
        leer_entero("Introduce una opcion valida",&opcion);
        switch (opcion)
        {
            case 1:
                realizar_pedido(cliente, v_pedidos,v_productos_pedido, v_lockers, v_compartimentos, v_descuentos, v_descuentos_cliente, v_productos);
                break;
            case 2:
               //pasale los vectores neceesarios
                recoger_pedido( cliente, v_pedidos, v_productos_pedido, v_lockers, v_compartimentos);
                break;
            case 3:
                consultar_pedido( cliente, v_pedidos, v_productos_pedido);
                break;
            case 4:
                break;
            default:
                printf("Opcion no valida\n");
                break;
        }
    } while (opcion != 4);

    //Guardar
    guardar_pedidos(&v_pedidos);
    guardar_devoluciones(&v_devoluciones);
    guardar_productos_pedido(&v_productos_pedido);
    guardar_lockers(&v_lockers);
    guardar_compartimentos(&v_compartimentos);
    guardar_descuentos(&v_descuentos);
    guardar_descuentos_clientes(&v_descuentos_cliente);
    guardar_productos(&v_productos);
}




//Funcion que realiza y da de alta una devolucion
void realizar_devolucion(Cliente* cliente,  VectorPedidos v_pedidos, VectorProductosPedido v_productos_pedido, VectorDevoluciones v_devoluciones)
{


    //Mostrar los productos de los pedidos entregados y en fecha de devolucion
    //tienes que comprobar en todo momento que el pedido pertenezca al cliente y
    //los productos mostrados al pedido
    listar_pedidos_cliente(&v_pedidos, cliente->id_cliente);
    char id_pedido[8];
    leer_cadena("Introduce el id del pedido: ", id_pedido, 8);
    if (pertenece_pedido(&v_productos_pedido, id_pedido, cliente->id_cliente))
    {
        listar_productos_pedido(&v_productos_pedido, id_pedido);
        char id_producto[8];
        leer_cadena("Introduce el id del producto: ", id_producto, 8);
        if (pertenece_pedido(&v_productos_pedido, id_pedido, id_producto))
        {
            char motivo[51];
            leer_cadena("Introduce el motivo de la devolucion: ", motivo, 51);
            alta_devolucion(&v_devoluciones, cliente->id_cliente, id_pedido, id_producto, motivo);
        }
        else
        {
            printf("El producto no pertenece al pedido\n");
        }
    }
    else
    {
        printf("El pedido no pertenece al cliente\n");
    }
//Guardar los pedidos , devoluciones y productos pedidos

}



//FUncion que hace que aparezca un menu y pregunta que quiere hacer el cliente
void gestionar_devolucion(Cliente * cliente)
{
    VectorPedidos v_pedidos;
    cargar_pedidos(&v_pedidos);
    VectorProductosPedido v_productos_pedido;
    cargar_productos_pedido(&v_productos_pedido);
    VectorDevoluciones v_devoluciones;
    cargar_devoluciones(&v_devoluciones);

    int opcion;
    do
    {
        printf("\n\n");
        printf("1. Realizar devolucion\n");
        printf("2. Consultar devoluciones\n");
        printf("3. Salir\n");
        printf("Introduce una opcion: ");
        leer_entero("Introduce una opcion valida",&opcion);
        switch (opcion)
        {
            case 1:
                realizar_devolucion( cliente, v_pedidos, v_productos_pedido, v_devoluciones);
                break;
            case 2:
                mostrar_devoluciones_pendientes(&v_devoluciones, cliente->id_cliente);
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

//Menu del cliente al estilo de menu_administrador.c, contando que se le pasan los vectores necesarios y tambien tienes como parametro de entrada el cliente
//que ha iniciado sesion
void menu_cliente(Cliente* cliente)
{
    int opcion;
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
        leer_entero("Introduce una opcion valida",&opcion);
        switch (opcion)
        {
            case 1:
                perfil_cliente(cliente);
                break;
            case 2:
                listado_productos();
                break;
            case 3:
               mostrar_descuentos(cliente);
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