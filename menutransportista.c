#include "menutransportista.h"
#include "stdlib.h"
#include "pedido.h"

#include "stdio.h"
#include "string.h"
#include "fecha.h"

void listar_productos_asignados(VectorProductosPedido *v_productos_pedido, char *id_transportista)
{
    int i;
    for (i = 0; i < v_productos_pedido->size; i++) {
        if (strcmp(v_productos_pedido->productos_pedido[i].id_transportista, id_transportista) == 0) {
            printf("========================================\n");
            printf("ID Pedido: %s\n", v_productos_pedido->productos_pedido[i].id_pedido);
            printf("ID Producto: %s\n", v_productos_pedido->productos_pedido[i].id_producto);
            printf("Unidades: %u\n", v_productos_pedido->productos_pedido[i].num_unidades);
            printf("Fecha prevista de entrega: %d/%d/%d\n", v_productos_pedido->productos_pedido[i].fecha_prevista_entrega.dia,
                   v_productos_pedido->productos_pedido[i].fecha_prevista_entrega.mes,
                   v_productos_pedido->productos_pedido[i].fecha_prevista_entrega.anio);
            printf("Importe: %.2f\n", v_productos_pedido->productos_pedido[i].importe);
            printf("Estado: %u\n", v_productos_pedido->productos_pedido[i].estado);
            //Puede que no tengan ID locker

            if(strcmp(v_productos_pedido->productos_pedido[i].id_locker, " ")!=0) {

                printf("ID Locker: %s\n", v_productos_pedido->productos_pedido[i].id_locker);
                // printf("Codigo Locker: %s\n", v_productos_pedido->productos_pedido[i].cod_locker);
                // Rehacer con el nuevo tipo de dato TODO
            }
            printf("Fecha de entrega o devolución: %d/%d/%d\n", v_productos_pedido->productos_pedido[i].fecha_entrega_devolucion.dia,
                   v_productos_pedido->productos_pedido[i].fecha_entrega_devolucion.mes,
                   v_productos_pedido->productos_pedido[i].fecha_entrega_devolucion.anio);
        }
    }
}

//Funcion que lista los productos pedidos no recogidos en fecha de lockers de una localidad
////Funcion que devuelve un producto pedido que se busca mediante , ID del pedido , ID del producto ,transportista asignado y estado de enReparto
//ProductoPedido *buscar_producto_pedido_por_compartimento(VectorProductosPedido *v_productos_pedido, char *id_locker, unsigned n_compartimento);
void listar_productos_no_recogidos(VectorCompartimentos *v_compartimentos, VectorProductosPedido *v_productos_pedido,VectorLockers *v_lockers, char *localidad)
{
    //Recorro los lockers de la localidad
    int i;
    for (i = 0; i < v_lockers->size; i++) {

        //Selecciono los lockers que son de esa localidad
        if (strcmp(v_lockers->lockers[i].localidad, localidad) == 0) {
        //miro cuantos compartimentos ocupados tiene el locker
    int j;
            for (j = 0; j < v_compartimentos->size; j++) {
                //Si el compartimento esta ocupado , pertenece al locker y si ha pasado la fecha de caducidad
                if (strcmp(v_compartimentos->compartimentos[j].id_locker, v_lockers->lockers[i].id_locker) == 0 && v_compartimentos->compartimentos[j].estado == 1 && comparar_fechas(obtener_fecha_actual(), v_compartimentos->compartimentos[j].fecha_caducidad) > 0){
                    //Busco el producto pedido asociado al compartimento y lo muestro si no ha sido recogido
                    ProductoPedido *producto_pedido = buscar_producto_pedido_por_compartimento(v_productos_pedido, v_compartimentos->compartimentos[j].id_locker, v_compartimentos->compartimentos[j].n_compartimento);
                    if (producto_pedido != NULL) {
                        printf("========================================\n");
                        printf("ID Pedido: %s\n", producto_pedido->id_pedido);
                        printf("ID Producto: %s\n", producto_pedido->id_producto);
                        printf("Unidades: %u\n", producto_pedido->num_unidades);
                        printf("Fecha prevista de entrega: %d/%d/%d\n", producto_pedido->fecha_prevista_entrega.dia,
                               producto_pedido->fecha_prevista_entrega.mes,
                               producto_pedido->fecha_prevista_entrega.anio);
                        printf("Importe: %.2f\n", producto_pedido->importe);
                        printf("Estado: %u\n", producto_pedido->estado);
                        printf("Fecha de entrega o devolución: %d/%d/%d\n", producto_pedido->fecha_entrega_devolucion.dia,
                               producto_pedido->fecha_entrega_devolucion.mes,
                               producto_pedido->fecha_entrega_devolucion.anio);
                    }
                }
            }


        }
    }
}



void gestion_perfil_transportista(Transportista* transportista)
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
    //buscar el pedido por ID
    char id_pedido[8];
    leer_cadena("Introduzca el ID del pedido: ", id_pedido, 8);
    Pedido* pedido = buscar_pedido_por_id(&v_pedidos, id_pedido);
    if(pedido == NULL)
    {
        printf("No se ha encontrado el pedido con ID %s\n", id_pedido);
        return;
    }
     listar_productos_pedido(&v_productos_pedido,pedido->id_pedido );

    //Seleccionar un producto para gestionar la entrega
    char id_producto[9];
    leer_cadena("Introduzca el ID del producto: ", id_producto, 9);


    //Buscar el producto en el pedido
    ProductoPedido* producto_pedido = buscar_producto_pedido(&v_productos_pedido, id_pedido, id_producto);
    if(producto_pedido == NULL)
    {
        printf("No se ha encontrado un producto asociado a ese ID para su entrega\n");
        return;
    }

    //Comprobar si el producto está asignado al transportista
    if(strcmp(producto_pedido->id_transportista, transportista->id_transportista)!=0){

        printf("EL producto no está asignado al transportista\n");
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
        char respuesta;
        leer_caracter("¿Ha podido realizar la entrega? (s/n): ",&respuesta);
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

        //Buscar el locker asignado al pedido mediante el ID de locker en pedido
        Locker* locker = buscar_locker_id(&v_lockers, pedido->id_locker);
        if(locker == NULL)
        {
            printf("No se ha encontrado el locker con ID %s\n", pedido->id_locker);
            return;
        }

        //Buscar el primer compartimento libre del locker
        CompartimentoLocker* compartimento = buscar_primer_compartimento_libre(&v_compartimentos, pedido->id_locker);
        if(compartimento == NULL)
        {
            printf("No hay compartimentos libres en el locker\n");
            return;
        }
      //Pedir un cod_locker y asignarlo al producto pedido y al compartimento, usando utilidades.h
       unsigned cod_locker;
         leer_unsigned("Introduzca el código del locker: ", &cod_locker);

        producto_pedido->cod_locker = cod_locker;
        compartimento->cod_locker = cod_locker;
        //Actualizar el compartimento a ocupado
        compartimento->estado = 1;
        //Actualizar el numero de compartimentos ocupados en el locker
        locker->num_compartimentos_ocupados++;
        //Actualizar el producto pedido a enLocker
        producto_pedido->estado = 4;
        printf("Producto marcado como en locker\n");


    }
}



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
    unsigned opcion;
    do
    {
        printf("\nMenu repartos\n\n");
        printf("1. Listar productos asignados al transportista con su fecha de entrega\n");
        printf("2. Gestionar una entrega\n");
        printf("3. Salir\n");
        leer_unsigned("Seleccione una opcion:",&opcion);
        switch(opcion)
        {
            case 1:
                //Listar productos asignados al transportista con su fecha de entrega
                listar_productos_asignados(&v_productos_pedido, transportista->id_transportista);
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
    //Guarda en memoria los vectores
    guardar_pedidos(&v_pedidos);
    guardar_productos_pedido(&v_productos_pedido);
    guardar_lockers(&v_lockers);
    guardar_compartimentos(&v_compartimentos);
}

//Funcion que gestiona la recogida de un producto de un compartimento locker
void gestion_recogida(VectorProductosPedido* v_productos_pedido, Transportista* transportista, VectorLockers* v_lockers, VectorCompartimentos* v_compartimentos)
{
    //Pedir el ID del locker
    char id_locker[11];
    leer_cadena("Introduzca el ID del locker: ", id_locker, 11);
    //Buscar el locker
    Locker* locker = buscar_locker_id(v_lockers, id_locker);
    if(locker == NULL)
    {
        printf("No se ha encontrado el locker con ID %s\n", id_locker);
        return;
    }
    //Listar los compartimentos ocupados del locker
    int i;
    for(i = 0; i < v_compartimentos->size; i++)
    {
        if(strcmp(v_compartimentos->compartimentos[i].id_locker, id_locker) == 0 && v_compartimentos->compartimentos[i].estado == 1)
        {
            listar_compartimento(&v_compartimentos->compartimentos[i]);
        }
    }
    //Pedir el numero de compartimento
    unsigned num_compartimento;
    leer_unsigned("Introduzca el numero de compartimento: ", &num_compartimento);
    //Buscar el compartimento
    CompartimentoLocker* compartimento = buscar_compartimento(v_compartimentos, id_locker, num_compartimento);
    if(compartimento == NULL)
    {
        printf("No se ha encontrado el compartimento con ID %s y numero %u\n", id_locker, num_compartimento);
        return;
    }
    //Buscar el producto pedido asociado al compartimento
    ProductoPedido* producto_pedido = buscar_producto_pedido_por_compartimento(v_productos_pedido, id_locker, num_compartimento);
    if(producto_pedido == NULL)
    {
        printf("No se ha encontrado el producto pedido asociado al compartimento\n");
        return;
    }
    //Marcar el producto como recogido
    strcpy(producto_pedido->id_locker," ");
    producto_pedido->cod_locker=0;
    strcpy(producto_pedido->id_transportista,transportista->id_transportista);
    producto_pedido->estado = 7;
    producto_pedido->fecha_entrega_devolucion = obtener_fecha_actual();
    //Marcar el compartimento como vacio
    compartimento->estado = 0;
    compartimento->cod_locker=0;
    //Actualizar el numero de compartimentos ocupados en el locker
    locker->num_compartimentos_ocupados--;
    printf("Producto recogido\n");
}


void gestion_retornos( Transportista* transportista)
{
    //Cargar en memoria los vectores necesarios
    VectorProductosPedido v_productos_pedido;
    cargar_productos_pedido(&v_productos_pedido);
    //Inicializar los vectores de lockers y compartimentos
    VectorLockers v_lockers;
    cargar_lockers(&v_lockers);
    VectorCompartimentos v_compartimentos;
    cargar_compartimentos(&v_compartimentos);

    //Mostrar el menu de opciones
    unsigned opcion;
    char localidad[21];

    do {
        printf("\nMenu retornos\n\n");
        printf("1. Consultar lockers por localidad y mostrando pedidos no recogidos en fecha\n");
        printf("2. Gestionar recogida de producto de un locker\n");
        printf("3. Salir\n");
        leer_unsigned("Seleccione una opcion:",&opcion);
        switch (opcion) {
            case 1:
                //Consultar lockers por localidad y mostrando pedidos no recogidos en fecha
                leer_cadena("Introduzca la localidad: ", localidad, 21);
                //Listar de una localidad los lockers
                listar_lockers_localidad(&v_lockers, localidad);
                //Listar los productos no recogidos en fecha
                listar_productos_no_recogidos(&v_compartimentos, &v_productos_pedido, &v_lockers, localidad);
                break;
            case 2:
                //Funcion para gestionar la recogida de un producto de un locker
                gestion_recogida(&v_productos_pedido, transportista, &v_lockers, &v_compartimentos);
                break;
            case 3:
                break;
            default:
                printf("\n Opcion no valida\n");
        }
    } while (opcion != 3);

    //Guardar en memoria los vectores necesarios
    guardar_productos_pedido(&v_productos_pedido);
    guardar_lockers(&v_lockers);
    guardar_compartimentos(&v_compartimentos);
}


//Mostrará las distintas opciones del menu de transportistas y seguirá mostrando el menu hasta que se seleccione salir
void mostrar_menu_transportista(Transportista *transportista)
{
    /*
     Menu transportista

     1. Perfil --> Permite consultar su perfil y pregunta si desea modificarlo
     2. Repartos --> Submenu : Consultar pedidos asignados , gestionar entrega de un producto pedido a domicilo o locker.
     3. Retorno --> Gestionar productospedidos no recogidos a tiempo
     4. Salir del sistema
     */

    unsigned opcion;
    do
    {
        printf("\nMenu transportista\n\n");
        printf("1. Perfil\n");
        printf("2. Repartos\n");
        printf("3. Retorno\n");
        printf("4. Salir del sistema\n");
        leer_unsigned("Seleccione una opcion:",&opcion);
        switch(opcion)
        {
            case 1:
                gestion_perfil_transportista(transportista);
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
