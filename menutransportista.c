#include "menutransportista.h"
/*
 typedef struct {
    char id_transportista[5]; // 4 digitos
    char nombre[21]; // Nombre del transportista
    char email[31]; // Email del transportista
    char contrasena[16]; // Contraseña de acceso
    char nombre_empresa[21]; // Nombre de la empresa de transporte
    char ciudad[21]; // Ciudad de operación
} Transportista;
 */
//Mostrar la informacion del perfil del transportista


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
        Locker* locker = buscar_locker_cod(&v_lockers, cod_locker);
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
        producto_pedido->estado = 4;
        producto_pedido->fecha_entrega_devolucion = obtener_fecha_actual();
        //Actualizar el estado del compartimento
        compartimento->estado = 1;
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
/*Getion de retornos, al principio de la función cargará en memoria los vectores necesarios y al terminar los guardará

 Mostrará un submenu con las siguientes opciones:
    1. Consultar lockers por localidad y mostrando pedidos no recogidos en fecha
    2. Gestionar recogida de producto de un locker
    3. Salir
 */
void gestion_retornos( Transportista* transportista)
{

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
