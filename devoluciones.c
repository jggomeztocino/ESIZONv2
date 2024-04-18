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
void cargar_devoluciones(VectorDevoluciones* v_devoluciones) {
    FILE *f = fopen("../data/devoluciones.txt", "r");
    if (f == NULL) {
        perror("\nError al abrir el archivo\n");
        return;
    }
    v_devoluciones->devoluciones = (Devolucion *) malloc(sizeof(Devolucion));
    v_devoluciones->n_devoluciones = 0;
    while (fscanf(f, "%7[^-]-%7[^-]-%d/%d/%d-%50[^-]-%8[^-]-%d/%d/%d-%d/%d/%d\n",
                  v_devoluciones->devoluciones[v_devoluciones->n_devoluciones].id_pedido,
                  v_devoluciones->devoluciones[v_devoluciones->n_devoluciones].id_producto,
                  &v_devoluciones->devoluciones[v_devoluciones->n_devoluciones].fecha_devolucion.dia,
                  &v_devoluciones->devoluciones[v_devoluciones->n_devoluciones].fecha_devolucion.mes,
                  &v_devoluciones->devoluciones[v_devoluciones->n_devoluciones].fecha_devolucion.anio,
                  v_devoluciones->devoluciones[v_devoluciones->n_devoluciones].motivo,
                  v_devoluciones->devoluciones[v_devoluciones->n_devoluciones].estado,
                  &v_devoluciones->devoluciones[v_devoluciones->n_devoluciones].fecha_aceptacion.dia,
                  &v_devoluciones->devoluciones[v_devoluciones->n_devoluciones].fecha_aceptacion.mes,
                  &v_devoluciones->devoluciones[v_devoluciones->n_devoluciones].fecha_aceptacion.anio,
                  &v_devoluciones->devoluciones[v_devoluciones->n_devoluciones].fecha_caducidad.dia,
                  &v_devoluciones->devoluciones[v_devoluciones->n_devoluciones].fecha_caducidad.mes,
                  &v_devoluciones->devoluciones[v_devoluciones->n_devoluciones].fecha_caducidad.anio) == 14) {
        v_devoluciones->n_devoluciones++;
        v_devoluciones->devoluciones = (Devolucion *) realloc(v_devoluciones->devoluciones,
                                                              (v_devoluciones->n_devoluciones + 1) * sizeof(Devolucion));
        if (v_devoluciones->devoluciones == NULL) {
            free(v_devoluciones->devoluciones);
            perror("\nError al reservar memoria\n");
        }
        fclose(f);
    }
}


void guardar_devoluciones(VectorDevoluciones* v_devoluciones) {
    FILE *f = fopen("../data/devoluciones.txt", "w");
    if (f == NULL) {
        return;
    }
    int i;
    for (i = 0; i < v_devoluciones->n_devoluciones; i++) {
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
void mostrar_devoluciones_pendientes(VectorDevoluciones* v_devoluciones, char* id_cliente) {
    int i;
    for (i = 0; i < v_devoluciones->n_devoluciones; i++) {
        if (strcmp(v_devoluciones->devoluciones[i].estado, "pendiente") == 0) {
            printf("Id pedido: %s\n", v_devoluciones->devoluciones[i].id_pedido);
            printf("Id producto: %s\n", v_devoluciones->devoluciones[i].id_producto);
            printf("Fecha devolución: %02d/%02d/%d\n", v_devoluciones->devoluciones[i].fecha_devolucion.dia,
                   v_devoluciones->devoluciones[i].fecha_devolucion.mes,
                   v_devoluciones->devoluciones[i].fecha_devolucion.anio);
            printf("Motivo: %s\n", v_devoluciones->devoluciones[i].motivo);
            printf("Estado: %s\n", v_devoluciones->devoluciones[i].estado);
            printf("Fecha aceptación: %02d/%02d/%d\n", v_devoluciones->devoluciones[i].fecha_aceptacion.dia,
                   v_devoluciones->devoluciones[i].fecha_aceptacion.mes,
                   v_devoluciones->devoluciones[i].fecha_aceptacion.anio);
            printf("Fecha caducidad: %02d/%02d/%d\n", v_devoluciones->devoluciones[i].fecha_caducidad.dia,
                   v_devoluciones->devoluciones[i].fecha_caducidad.mes,
                   v_devoluciones->devoluciones[i].fecha_caducidad.anio);
        }
    }
}

