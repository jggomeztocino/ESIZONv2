#include "devoluciones.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>
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
#include <stdio.h>
#include <stdlib.h>

void cargar_devoluciones(VectorDevoluciones *v_devoluciones)
{
    // Abrir archivo de devoluciones para lectura
    FILE *f = fopen("../data/Devoluciones.txt", "r");
    if (f == NULL)
    {
        perror("Error al abrir el archivo");
        return;
    }

    // Inicializar la memoria para almacenar devoluciones
    v_devoluciones->devoluciones = (Devolucion *)malloc(sizeof(Devolucion));
    if (v_devoluciones->devoluciones == NULL)
    {
        perror("Error al reservar memoria inicial");
        fclose(f);
        return;
    }
    v_devoluciones->n_devoluciones = 0;

    Devolucion *temp;
    unsigned n_devoluciones_actual = 0;

    // Leer los datos de las devoluciones del archivo
    while (fscanf(f, "%7[^-]-%7[^-]-%d/%d/%d-%50[^-]-%8[^-]-%d/%d/%d-%d/%d/%d\n",
                  v_devoluciones->devoluciones[n_devoluciones_actual].id_pedido,
                  v_devoluciones->devoluciones[n_devoluciones_actual].id_producto,
                  &v_devoluciones->devoluciones[n_devoluciones_actual].fecha_devolucion.dia,
                  &v_devoluciones->devoluciones[n_devoluciones_actual].fecha_devolucion.mes,
                  &v_devoluciones->devoluciones[n_devoluciones_actual].fecha_devolucion.anio,
                  v_devoluciones->devoluciones[n_devoluciones_actual].motivo,
                  v_devoluciones->devoluciones[n_devoluciones_actual].estado,
                  &v_devoluciones->devoluciones[n_devoluciones_actual].fecha_aceptacion.dia,
                  &v_devoluciones->devoluciones[n_devoluciones_actual].fecha_aceptacion.mes,
                  &v_devoluciones->devoluciones[n_devoluciones_actual].fecha_aceptacion.anio,
                  &v_devoluciones->devoluciones[n_devoluciones_actual].fecha_caducidad.dia,
                  &v_devoluciones->devoluciones[n_devoluciones_actual].fecha_caducidad.mes,
                  &v_devoluciones->devoluciones[n_devoluciones_actual].fecha_caducidad.anio) == 14)
    {

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

    // Actualizar la cantidad de devoluciones después de la lectura completa
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

// Función que muestra las devoluciones con estado pendiente de un cliente.
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

// Funcion que realiza y da de alta una devolucion
void realizar_devolucion(Cliente *cliente, VectorPedidos v_pedidos, VectorProductosPedido v_productos_pedido, VectorDevoluciones v_devoluciones)
{

    // Mostrar los productos de los pedidos entregados y en fecha de devolucion
    // tienes que comprobar en todo momento que el pedido pertenezca al cliente y
    // los productos mostrados al pedido
    listar_pedidos_cliente(&v_pedidos, cliente->id_cliente);
    Pedido *pedido;
    char id_pedido[8];
    leer_cadena("Introduce el id del pedido: ", id_pedido, 8);
    if (pertenece_pedido(&v_productos_pedido, id_pedido, cliente->id_cliente))
    {
        listar_productos_pedido(&v_productos_pedido, id_pedido);
        char id_producto[8];
        leer_cadena("Introduce el id del producto: ", id_producto, 8);
        if (pertenece_pedido(&v_productos_pedido, id_pedido, id_producto))
        {
            pedido = buscar_pedido_por_id(&v_pedidos, id_pedido);
            char motivo[51];
            leer_cadena("Introduce el motivo de la devolucion: ", motivo, 51);
            alta_devolucion(&v_devoluciones,pedido, id_producto, motivo);
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

}