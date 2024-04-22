#include "menutransportista.h"

//Funcion que lista los productos pedidos no recogidos en fecha de lockers de una localidad
void listar_productos_no_recogidos(VectorCompartimentos* v_compartimentos,VectorPedidos* v_pedidos, VectorProductosPedido* v_productos_pedido, VectorLockers* v_lockers, char* localidad)
{

    int i;
    int j;
    int flag_localidad =0;
    int flag_productos_caducados=0;
    for(i = 0; i < v_lockers->size; i++)
    {
        if(strcmp(v_lockers->lockers[i].localidad, localidad) == 0)
        {
            flag_localidad =1;

            for(j = 0; j < v_compartimentos->size; j++)
            {
                if(strcmp(v_compartimentos->compartimentos[j].id_locker, v_lockers->lockers[i].id_locker) == 0)
                {
                    //Buscar el producto asociado al compartimento
                    ProductoPedido* producto_pedido = buscar_producto_pedido_locker(v_productos_pedido, v_lockers->lockers[i].id_locker, v_compartimentos->compartimentos[j].n_compartimento);
                    if(producto_pedido != NULL)
                    {
                        //Comprobar si la fecha actual es mayor a la fecha de caducidad del compartimento
                        if(comparar_fechas(obtener_fecha_actual(), producto_pedido->fecha_entrega_devolucion) == 1)
                        {
                            flag_productos_caducados = 1;
                            //Mostrar el producto no recogido
                            printf("Producto no recogido\n");
                            printf("ID: %s\n", producto_pedido->id_producto);
                            printf("ID pedido: %s\n", producto_pedido->id_pedido);
                            printf("Número de unidades: %u\n", producto_pedido->num_unidades);
                            printf("Fecha prevista de entrega: %02d/%02d/%d\n", producto_pedido->fecha_prevista_entrega.dia, producto_pedido->fecha_prevista_entrega.mes, producto_pedido->fecha_prevista_entrega.anio);
                            printf("Importe: %.2f\n", producto_pedido->importe);
                            printf("Estado: %d\n", producto_pedido->estado);
                            printf("Fecha de entrega: %02d/%02d/%d\n", producto_pedido->fecha_entrega_devolucion.dia, producto_pedido->fecha_entrega_devolucion.mes, producto_pedido->fecha_entrega_devolucion.anio);
                            printf("Locker: %s\n", producto_pedido->id_locker);
                            printf("Compartimento: %u\n", v_compartimentos->compartimentos[j].n_compartimento);
                            printf("\n");
                        }
                    }
                }
            }
        }
    }
    if(flag_localidad == 0)
    {
        printf("No hay lockers en la localidad %s\n", localidad);
    }
    if(flag_productos_caducados == 0)
    {
        printf("No hay productos no recogidos en fecha\n");
    }
}

void gestion_perfil( Transportista* transportista)
{
    printf("\nPerfil del transportista\n");
    printf("ID: %s\n", transportista->id_transportista);
    printf("Nombre: %s\n", transportista->nombre);
    printf("Email: %s\n", transportista->email);
    printf("Nombre empresa: %s\n", transportista->nombre_empresa);
    printf("Ciudad: %s\n", transportista->ciudad);
    printf("\n");
    char respuesta;
    printf("¿Desea modificar su perfil? (s/n): ");
    scanf(" %c", &respuesta);
    if(respuesta == 's')
    {
        printf("Introduzca su nuevo nombre: ");
        scanf(" %s", transportista->nombre);
        printf("Introduzca su nuevo email: ");
        scanf(" %s", transportista->email);
        printf("Introduzca su nueva contraseña: ");
        scanf(" %s", transportista->contrasena);
        printf("Introduzca el nombre de su nueva empresa: ");
        scanf(" %s", transportista->nombre_empresa);
        printf("Introduzca la ciudad de operación: ");
        scanf(" %s", transportista->ciudad);
    }
}



//Gestiona la entrega de un producto pedido
void gestion_entrega(  VectorPedidos v_pedidos, VectorProductosPedido v_productos_pedido, Transportista* transportista , VectorLockers v_lockers, VectorCompartimentos v_compartimentos) {
    //buscar el pedido por id
    char id_pedido[8];
    leer_cadena("Introduzca el id del pedido: ", id_pedido, 8);
    Pedido* pedido = buscar_pedido_por_id(&v_pedidos, id_pedido);
    if(pedido == NULL)
    {
        printf("No se ha encontrado el pedido con id %s\n", id_pedido);
        return;
    }
    //Listar los productos asignados al transportista en el pedido
    listar_productos_asignados_pedido(&v_productos_pedido, id_pedido, transportista->id_transportista);

    //Seleccionar un producto para gestionar la entrega
    char id_producto[9];
    leer_cadena("Introduzca el id del producto: ", id_producto, 9);

    //Buscar el producto en el pedido
    ProductoPedido* producto_pedido = buscar_producto_pedido(&v_productos_pedido, id_pedido, id_producto, transportista->id_transportista);
    if(producto_pedido == NULL)
    {
        printf("No se ha encontrado un producto asociado a ese id para su entrega\n");
        return;
    }

    //Comprobar si el pedido se entrega a domicilio o en locker
    if(pedido->lugar == 1)
    {
        //Entrega a domicilio
        printf("Entrega a domicilio\n");
        printf("Fecha prevista de entrega: %02d/%02d/%d\n", producto_pedido->fecha_prevista_entrega.dia, producto_pedido->fecha_prevista_entrega.mes, producto_pedido->fecha_prevista_entrega.anio);
        printf("Importe: %.2f\n", producto_pedido->importe);
        printf("Estado: %d\n", producto_pedido->estado);
        printf("Fecha de entrega: %02d/%02d/%d\n", producto_pedido->fecha_entrega_devolucion.dia, producto_pedido->fecha_entrega_devolucion.mes, producto_pedido->fecha_entrega_devolucion.anio);
        printf("¿Ha podido realizar la entrega? (s/n): ");
        char respuesta;
        scanf(" %c", &respuesta);
        if(respuesta == 's')
        {
            producto_pedido->estado = 5;
            producto_pedido->fecha_entrega_devolucion = obtener_fecha_actual();
            printf("Producto marcado como entregado\n");
        }else{
            //Marcar el producto con el estado de transportista
            producto_pedido->estado = 7;
            printf("Producto marcado con el estado transportista\n");
        }
    }
    if(pedido->lugar == 2)
    {
        char cod_locker[21];
        leer_cadena("Introduzca el código del locker: ", cod_locker, 21);
        //Buscar el locker por el código
        Locker* locker = buscar_locker_id(&v_lockers, cod_locker);
        if(locker == NULL)
        {
            printf("No se ha encontrado un locker con el código %s\n", cod_locker);
            return;
        }
        //Buscar un compartimento libre en el locker
        CompartimentoLocker* compartimento = buscar_compartimento_libre(&v_compartimentos, locker->id_locker);
        if(compartimento == NULL)
        {
            printf("No hay compartimentos libres en el locker %s\n", locker->id_locker);
            return;
        }
        //Asignar el compartimento al producto
        strcpy(producto_pedido->id_locker, locker->id_locker);
        strcpy(producto_pedido->cod_locker, cod_locker);
        //Actualizar el estado del producto
        producto_pedido->estado = 4;
        //Actualizar la fecha de entrega del producto
        producto_pedido->fecha_entrega_devolucion = obtener_fecha_actual();
        //Actualizar el estado del compartimento
        compartimento->estado = 1;
        //Actualizar la fecha de ocupación del compartimento
        compartimento->fecha_ocupacion = obtener_fecha_actual();
        //Incrementar el número de compartimentos ocupados en el locker
        locker->num_compartimentos_ocupados++;
        printf("Producto asignado al locker %s en el compartimento %u\n", locker->id_locker, compartimento->n_compartimento);
    }
}
/*Getion de repartos, al principio de la función cargará en memoria los vectores necesarios y al terminar los guardará

 Mostrará un submenu con las siguientes opciones:
    1. Listar productos asignados al transportista con su fecha de entrega
    2. Gestionar una entrega
    3. Salir
 */
void gestion_repartos( Transportista* transportista)
{
    //Cargar en memoria los vectores necesarios
    VectorPedidos v_pedidos;
    cargar_pedidos(&v_pedidos);
    VectorProductosPedido v_productos_pedido;
    cargar_productos_pedido(&v_productos_pedido);
    //Inicializar los vectores de lockers y compartimentos
    VectorLockers v_lockers;
    cargar_lockers(&v_lockers);
    VectorCompartimentos v_compartimentos;
    cargar_compartimentos(&v_compartimentos);

    //Mostrar el menu de opciones
    int opcion;
    do
    {
        printf("\nMenu repartos\n\n");
        printf("1. Listar productos asignados al transportista con su fecha de entrega\n");
        printf("2. Gestionar una entrega\n");
        printf("3. Salir\n");
        printf("\nOpcion: ");
        scanf("%d", &opcion);
        switch(opcion)
        {
            case 1:
                //Listar productos asignados al transportista con su fecha de entrega
                listar_productos_asignados(&v_pedidos, &v_productos_pedido, transportista->id_transportista);
                break;
            case 2:
                //Gestionar una entrega
                gestion_entrega(v_pedidos, v_productos_pedido, transportista, v_lockers, v_compartimentos);
                break;
            case 3:
                break;
            default:
                printf("\nOpcion no valida\n");
        }
    } while(opcion != 3);

}

//Funcion que gestiona la recogida de un producto de un locker
void gestion_recogida(VectorPedidos* v_pedidos, VectorProductosPedido* v_productos_pedido, Transportista* transportista, VectorLockers* v_lockers, VectorCompartimentos* v_compartimentos)
{
    //Listar los productos no recogidos en fecha
    char localidad[21];
    char id_locker[11];
    char id_producto[9];
    unsigned n_compartimento;
    leer_cadena("Introduzca la localidad: ", localidad, 21);
    listar_productos_no_recogidos(v_compartimentos, v_pedidos, v_productos_pedido, v_lockers, localidad);

    //Seleccionar un producto pedido para recoger introduciendo el id del locker , el id del producto y el número de compartimento

    leer_cadena("Introduzca el id del locker: ", id_locker, 11);
    leer_cadena("Introduzca el id del producto: ", id_producto, 9);
    leer_unsigned( "Introduzca el número de compartimento: ", &n_compartimento);
    //Hay que comprpbar que el producto no haya sido recogido ya, que el locker exista y que el compartimento exista y que haya pasado la fecha de caducidad
    //Buscar el producto pedido
    ProductoPedido* producto_pedido = buscar_producto_pedido_locker(v_productos_pedido, id_locker, n_compartimento);
    if(producto_pedido == NULL)
    {
        printf("No se ha encontrado un producto asociado a ese id para su recogida\n");
        return;
    }
    //Comprobar si el producto ya ha sido recogido
    if(producto_pedido->estado == 6)
    {
        printf("El producto ya ha sido recogido\n");
        return;
    }
    //Comprobar si el producto ha caducado, comparando la fecha actual con la fecha actual del compartimento en el que se encuentra el producto pedido
    CompartimentoLocker* compartimento = buscar_compartimento_id(v_compartimentos, id_locker, n_compartimento);
    if(comparar_fechas(obtener_fecha_actual(), compartimento->fecha_caducidad) == 1)
    {
        printf("El producto ha caducado\n");
        return;
    }
    //Marcar el producto como recogido
    producto_pedido->estado = 7;
    //Marcar el compartimento como vacío
    compartimento->estado = 0;
    //Decrementar el número de compartimentos ocupados en el locker
    Locker* locker = buscar_locker_id(v_lockers, id_locker);
    locker->num_compartimentos_ocupados--;
    //Borrar el codigo del locker del producto pedido
    strcpy(producto_pedido->id_locker, "");
    strcpy(producto_pedido->cod_locker, "");
    printf("Producto recogido\n");
}
/*Getion de retornos, al principio de la función cargará en memoria los vectores necesarios y al terminar los guardará

 Mostrará un submenu con las siguientes opciones:
    1. Consultar lockers por localidad y mostrando pedidos no recogidos en fecha
    2. Gestionar recogida de producto de un locker
    3. Salir

    El sistema facilitará al transportista la tarea de retornar a origen todos los productos que no
hayan sido recogidos de los lockers en el plazo determinado, permitiéndole consultar todos los
lockers por localidad y mostrando sus pedidos. En el momento de la recogida de los productos
para su retorno, el sistema debe actualizar automáticamente el número de compartimentos
ocupados y eliminar el código locker asociado al producto. Así como el estado de los productos
y el stock de los mismos para que quede reflejada la operación.
 */
void gestion_retornos( Transportista* transportista)
{
    //Cargar en memoria los vectores necesarios
    VectorPedidos v_pedidos;
    cargar_pedidos(&v_pedidos);
    VectorProductosPedido v_productos_pedido;
    cargar_productos_pedido(&v_productos_pedido);
    //Inicializar los vectores de lockers y compartimentos
    VectorLockers v_lockers;
    cargar_lockers(&v_lockers);
    VectorCompartimentos v_compartimentos;
    cargar_compartimentos(&v_compartimentos);

    //Mostrar el menu de opciones
    unsigned opcion;

    do {
        printf("\nMenu retornos\n\n");
        printf("1. Consultar lockers por localidad y mostrando pedidos no recogidos en fecha\n");
        printf("2. Gestionar recogida de producto de un locker\n");
        printf("3. Salir\n");
        printf("\nOpcion: ");
        scanf("%u", &opcion);
        switch (opcion) {
            case 1:
                //Consultar lockers por localidad y mostrando pedidos no recogidos en fecha
                char localidad[21];
                leer_cadena("Introduzca la localidad: ", localidad, 21);
                //Listar de una localidad los lockers
                listar_lockers_localidad(&v_lockers, localidad);
                //Listar los productos no recogidos en fecha
                listar_productos_no_recogidos( &v_compartimentos, &v_pedidos, &v_productos_pedido, &v_lockers, localidad);
                break;
            case 2:
                //Funcion para gestionar la recogida de un producto de un locker
                gestion_recogida(&v_pedidos, &v_productos_pedido, transportista, &v_lockers, &v_compartimentos);
                break;
            case 3:
                break;
            default:
                printf("\nOpcion no valida\n");
        }
    } while (opcion != 3);

}


//Mostrará las distintas opciones del menu de transportistas y seguirá mostrando el menu hasta que se seleccione salir
void mostrar_menu_transportista(Transportista* transportista)
{
    /*
     Menu transportista

     1. Perfil --> Permite consultar su perfil y pregunta si desea modificarlo
     2. Repartos --> Submenu : Consultar pedidos asignados , gestionar entrega de un producto pedido a domicilo o locker.
     3. Retorno --> Gestionar productospedidos no recogidos a tiempo
     4. Salir del sistema
     */

    int opcion;
    do
    {
        printf("\nMenu transportista\n\n");
        printf("1. Perfil\n");
        printf("2. Repartos\n");
        printf("3. Retorno\n");
        printf("4. Salir del sistema\n");
        printf("\nOpcion: ");
        scanf("%d", &opcion);
        switch(opcion)
        {
            case 1:
                gestion_perfil(transportista);
                break;
            case 2:
                gestion_repartos(transportista);
                break;
            case 3:
                gestion_retornos(transportista);
                break;
            case 4:
                break;
            default:
                printf("\nOpcion no valida\n");
        }
    } while(opcion != 4);

}
