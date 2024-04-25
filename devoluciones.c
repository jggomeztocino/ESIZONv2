#include "devoluciones.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "pedido.h"
// Funciones para cargar y guardar las devoluciones (al estilo de cliente.c)
/*
    Los campos, separados por guiones, son los que se describen a continuación:
    o Identificador del pedido (Id_pedido), 7 dígitos.
    o Identificador del producto (Id_prod), 7 dígitos.
    o Fecha de devolución (día, mes y año).
    o Motivo (Motivo), 50 caracteres máximo.
    o Estado (Estado): «pendiente» (de aceptación), «aceptado», «denegado», «enviado» (por cliente)
    o «recibido».
    o Fecha aceptación (día, mes y año).
    o Fecha caducidad (día, mes y año).

    Ejemplo de línea de devolución:
    0000002-0000001-25/02/2024-desperfecto-pendiente-00/00/0000-00/00/0000


    Es decir:
    id_pedido-id_producto-fecha_devolucion-motivo-estado-fecha_aceptacion-fecha_caducidad

    Primero deberá inicializar el puntero de clientes para alojar un solo cliente y su tamaño a 0.
    Luego, abrir el archivo en modo lectura y leer cada línea, separando los campos por el carácter '-'.
    Si el vector, definido en el puntero de clientes, no tiene espacio suficiente, deberá incrementar su tamaño en 1 unidad.
 */
#include <stdlib.h>

void cargar_devoluciones(VectorDevoluciones *v_devoluciones)
{
    FILE *f = fopen("../data/Devoluciones.txt", "r");
    if (f == NULL)
    {
        perror("Error al abrir el archivo de devoluciones");
        return;
    }

    v_devoluciones->devoluciones = (Devolucion *)malloc(sizeof(Devolucion));
    if (v_devoluciones->devoluciones == NULL)
    {
        perror("Error al reservar memoria inicial");
        fclose(f);
        return;
    }
    v_devoluciones->n_devoluciones = 0;

    char dia_dev[3], mes_dev[3], anio_dev[5];
    char dia_acept[3], mes_acept[3], anio_acept[5];
    char dia_cad[3], mes_cad[3], anio_cad[5];
    Devolucion *temp;
    unsigned n_devoluciones_actual = 0;

    while (fscanf(f, "%7[^-]-%7[^-]-%2[^/]/%2[^/]/%4[^-]-%50[^-]-%8[^-]-%2[^/]/%2[^/]/%4[^-]-%2[^/]/%2[^/]/%4[^\n]",
                  v_devoluciones->devoluciones[n_devoluciones_actual].id_pedido,
                  v_devoluciones->devoluciones[n_devoluciones_actual].id_producto,
                  dia_dev, mes_dev, anio_dev,
                  v_devoluciones->devoluciones[n_devoluciones_actual].motivo,
                  v_devoluciones->devoluciones[n_devoluciones_actual].estado,
                  dia_acept, mes_acept, anio_acept,
                  dia_cad, mes_cad, anio_cad) == 14)
    {
        v_devoluciones->devoluciones[n_devoluciones_actual].fecha_devolucion.dia = atoi(dia_dev);
        v_devoluciones->devoluciones[n_devoluciones_actual].fecha_devolucion.mes = atoi(mes_dev);
        v_devoluciones->devoluciones[n_devoluciones_actual].fecha_devolucion.anio = atoi(anio_dev);
        v_devoluciones->devoluciones[n_devoluciones_actual].fecha_aceptacion.dia = atoi(dia_acept);
        v_devoluciones->devoluciones[n_devoluciones_actual].fecha_aceptacion.mes = atoi(mes_acept);
        v_devoluciones->devoluciones[n_devoluciones_actual].fecha_aceptacion.anio = atoi(anio_acept);
        v_devoluciones->devoluciones[n_devoluciones_actual].fecha_caducidad.dia = atoi(dia_cad);
        v_devoluciones->devoluciones[n_devoluciones_actual].fecha_caducidad.mes = atoi(mes_cad);
        v_devoluciones->devoluciones[n_devoluciones_actual].fecha_caducidad.anio = atoi(anio_cad);

        n_devoluciones_actual++;
        temp = (Devolucion *)realloc(v_devoluciones->devoluciones, (n_devoluciones_actual + 1) * sizeof(Devolucion));
        if (temp == NULL)
        {
            perror("Error al reservar memoria durante la lectura");
            free(v_devoluciones->devoluciones);
            fclose(f);
            return;
        }
        v_devoluciones->devoluciones = temp;
    }

    v_devoluciones->n_devoluciones = n_devoluciones_actual;
    fclose(f);
}



void guardar_devoluciones(VectorDevoluciones *v_devoluciones)
{
    FILE *f = fopen("../data/Devoluciones.txt", "w");
    if (f == NULL)
    {
        return;
    }
    int i;
    for (i = 0; i < v_devoluciones->n_devoluciones; i++)
    {
        fprintf(f, "%s-%s-%02d/%02d/%d-%s-%s-%02d/%02d/%d-%02d/%02d/%d\n",
                v_devoluciones->devoluciones[i].id_pedido,
                v_devoluciones->devoluciones[i].id_producto,
                v_devoluciones->devoluciones[i].fecha_devolucion.dia,
                v_devoluciones->devoluciones[i].fecha_devolucion.mes,
                v_devoluciones->devoluciones[i].fecha_devolucion.anio,
                v_devoluciones->devoluciones[i].motivo,
                v_devoluciones->devoluciones[i].estado,
                v_devoluciones->devoluciones[i].fecha_aceptacion.dia,
                v_devoluciones->devoluciones[i].fecha_aceptacion.mes,
                v_devoluciones->devoluciones[i].fecha_aceptacion.anio,
                v_devoluciones->devoluciones[i].fecha_caducidad.dia,
                v_devoluciones->devoluciones[i].fecha_caducidad.mes,
                v_devoluciones->devoluciones[i].fecha_caducidad.anio);
    }
    fclose(f);
}

void mostrar_devoluciones_pendientes(VectorPedidos *v_pedidos, VectorDevoluciones *v_devoluciones, char *id_cliente)
{

    int i;
    for (i = 0; i < v_devoluciones->n_devoluciones; i++)
    {
        if (strcmp(v_devoluciones->devoluciones[i].estado, "pendiente") == 0)
        {
            Pedido *pedido = buscar_pedido_por_id(v_pedidos, v_devoluciones->devoluciones[i].id_pedido);
            if (pedido != NULL && strcmp(pedido->id_cliente, id_cliente) == 0)
            {
                printf("ID Pedido: %s\n", v_devoluciones->devoluciones[i].id_pedido);
                printf("ID Producto: %s\n", v_devoluciones->devoluciones[i].id_producto);
                printf("Fecha de devolución: %02d/%02d/%d\n", v_devoluciones->devoluciones[i].fecha_devolucion.dia, v_devoluciones->devoluciones[i].fecha_devolucion.mes, v_devoluciones->devoluciones[i].fecha_devolucion.anio);
                printf("Motivo: %s\n", v_devoluciones->devoluciones[i].motivo);
                printf("Estado: %s\n", v_devoluciones->devoluciones[i].estado);
                printf("Fecha de aceptación: %02d/%02d/%d\n", v_devoluciones->devoluciones[i].fecha_aceptacion.dia, v_devoluciones->devoluciones[i].fecha_aceptacion.mes, v_devoluciones->devoluciones[i].fecha_aceptacion.anio);
                printf("Fecha de caducidad: %02d/%02d/%d\n", v_devoluciones->devoluciones[i].fecha_caducidad.dia, v_devoluciones->devoluciones[i].fecha_caducidad.mes, v_devoluciones->devoluciones[i].fecha_caducidad.anio);
                printf("\n");
            }
        }
    }
}

void alta_devolucion(char* id_pedido, char* id_producto, Fecha* fecha_devolucion, VectorDevoluciones* v_devoluciones)
{
    Fecha fecha_nula = {0, 0, 0}; // Fecha nula para inicializar la fecha de aceptación y caducidad

    char motivo[51];
    leer_cadena("Introduce el motivo de la devolución: ", motivo, 51);

    Devolucion* temp = (Devolucion*)realloc(v_devoluciones->devoluciones, (v_devoluciones->n_devoluciones + 1) * sizeof(Devolucion));
    if (temp == NULL)
    {
        perror("Error al reservar memoria para la devolución");
        return;
    }
    v_devoluciones->devoluciones = temp;

    Devolucion* devolucion = &v_devoluciones->devoluciones[v_devoluciones->n_devoluciones];
    strcpy(devolucion->id_pedido, id_pedido);
    strcpy(devolucion->id_producto, id_producto);
    devolucion->fecha_devolucion = crearFecha(fecha_devolucion->dia, fecha_devolucion->mes, fecha_devolucion->anio);
    strcpy(devolucion->motivo, motivo);
    strcpy(devolucion->estado, "pendiente");
    devolucion->fecha_aceptacion = fecha_nula;
    devolucion->fecha_caducidad = fecha_nula;

    v_devoluciones->n_devoluciones++;
}

void iniciar_devolucion(ProductoPedido* productoPedido, char* id_producto, VectorDevoluciones* v_devoluciones)
{
    Fecha fecha_actual = obtener_fecha_actual();

    productoPedido->estado = 6;
    productoPedido->fecha_entrega_devolucion = fecha_actual;

    alta_devolucion(productoPedido->id_pedido, id_producto, &fecha_actual, v_devoluciones);
}

void baja_devolucion(char* id_pedido, char* id_producto, VectorDevoluciones* v_devoluciones)
{
    int i;
    for(i = 0; i < v_devoluciones->n_devoluciones; i++)
    {
        if(strcmp(v_devoluciones->devoluciones[i].id_pedido, id_pedido) == 0 && strcmp(v_devoluciones->devoluciones[i].id_producto, id_producto) == 0)
        {
            break;
        }
    }
    for(; i < v_devoluciones->n_devoluciones - 1; i++)
    {
        v_devoluciones->devoluciones[i] = v_devoluciones->devoluciones[i + 1];
    }
    v_devoluciones->n_devoluciones--;

    Devolucion* temp = (Devolucion*)realloc(v_devoluciones->devoluciones, v_devoluciones->n_devoluciones * sizeof(Devolucion));
    if(temp == NULL && v_devoluciones->n_devoluciones > 0)
    {
        perror("Error al liberar memoria de la devolución");
        return;
    }
    v_devoluciones->devoluciones = temp;
    
}

Devolucion* buscar_devolucion(char* id_pedido, char* id_producto, VectorDevoluciones* v_devoluciones)
{
    int i;
    for(i = 0; i < v_devoluciones->n_devoluciones; i++)
    {
        if(strcmp(v_devoluciones->devoluciones[i].id_pedido, id_pedido) == 0 && strcmp(v_devoluciones->devoluciones[i].id_producto, id_producto) == 0)
        {
            return &v_devoluciones->devoluciones[i];
        }
    }
    return NULL;
}

void listar_devolucion(Devolucion* devolucion)
{
    printf("\n-------------------\n");
    printf("ID Pedido: %s\n", devolucion->id_pedido);
    printf("ID Producto: %s\n", devolucion->id_producto);
    printf("Fecha de devolución: %02d/%02d/%d\n", devolucion->fecha_devolucion.dia, devolucion->fecha_devolucion.mes, devolucion->fecha_devolucion.anio);
    printf("Motivo: %s\n", devolucion->motivo);
    printf("Estado: %s\n", devolucion->estado);
    printf("Fecha de aceptación: %02d/%02d/%d\n", devolucion->fecha_aceptacion.dia, devolucion->fecha_aceptacion.mes, devolucion->fecha_aceptacion.anio);
    printf("Fecha de caducidad: %02d/%02d/%d\n", devolucion->fecha_caducidad.dia, devolucion->fecha_caducidad.mes, devolucion->fecha_caducidad.anio);
    printf("\n-------------------\n");
}

void listar_devoluciones(VectorDevoluciones* v_devoluciones)
{
    int i;
    for(i = 0; i < v_devoluciones->n_devoluciones; i++)
    {
        listar_devolucion(&v_devoluciones->devoluciones[i]);
    }
}

unsigned listar_devoluciones_cliente(VectorDevoluciones* v_devoluciones, char* id_cliente)
{
    unsigned n_devoluciones = 0;
    int i;
    for(i = 0; i < v_devoluciones->n_devoluciones; i++)
    {
        if(strcmp(v_devoluciones->devoluciones[i].id_pedido, id_cliente) == 0)
        {
            n_devoluciones++;
            listar_devolucion(&v_devoluciones->devoluciones[i]);
        }
    }
    return n_devoluciones;
}

Devolucion* modificar_devolucion(Devolucion* devolucion)
{
    Fecha fecha_actual = obtener_fecha_actual();
    Fecha fecha_devolucion = fecha_actual;
    fecha_devolucion.dia += 7;

    printf("ID Pedido: %s\n", devolucion->id_pedido);
    printf("ID Producto: %s\n", devolucion->id_producto);
    printf("Fecha de devolución: %02d/%02d/%d\n", devolucion->fecha_devolucion.dia, devolucion->fecha_devolucion.mes, devolucion->fecha_devolucion.anio);
    printf("Motivo: %s\n", devolucion->motivo);
    printf("Estado: %s\n", devolucion->estado);
    if(strcmp(devolucion->estado, "aceptado") == 0)
    {
        printf("Fecha de aceptación: %02d/%02d/%d\n", devolucion->fecha_aceptacion.dia, devolucion->fecha_aceptacion.mes, devolucion->fecha_aceptacion.anio);
        printf("Fecha de caducidad: %02d/%02d/%d\n", devolucion->fecha_caducidad.dia, devolucion->fecha_caducidad.mes, devolucion->fecha_caducidad.anio);
    }
    unsigned nuevo_estado;
    do
    {
        printf("Nuevo estado de la devolución:\n");
        printf("1. Aceptado\n");
        printf("2. Denegado\n");
        printf("3. Enviado\n");
        printf("4. Recibido\n");
        printf("5. Salir\n");
        leer_unsigned("Seleccione una opción: ", &nuevo_estado);
    } while(nuevo_estado < 1 || nuevo_estado > 5);

    switch(nuevo_estado)
    {
        case 1:
            strcpy(devolucion->estado, "aceptado");
            devolucion->fecha_aceptacion = fecha_actual;
            devolucion->fecha_caducidad = fecha_devolucion;
            break;
        case 2:
            strcpy(devolucion->estado, "denegado");
            break;
        case 3:
            strcpy(devolucion->estado, "enviado");
            break;
        case 4:
            strcpy(devolucion->estado, "recibido");
            break;
        case 5:
            printf("Saliendo...\n");
            break;
        default:
            break;
    }

    return devolucion;
}