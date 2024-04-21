#include "stdio.h"
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#include "transportista.h"
//Ejemplo:
//0001-Rafael Guitierrez- rafael@gutitrans.com-rf001-GutiTrans-Cádiz
//0002-Pepe Tinoco-pepe@itranspo.com-pp001-TransPo-Cádiz
void cargar_transportistas(VectorTransportistas* transportistas) {
    // Abrir archivo de transportistas para lectura
    FILE* f = fopen("../data/Transportistas.txt", "r");
    if (f == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    // Inicializar la memoria para almacenar los transportistas
    transportistas->transportistas = (Transportista*)malloc(sizeof(Transportista));
    if (transportistas->transportistas == NULL) {
        perror("Error al reservar memoria inicial");
        fclose(f);
        return;
    }
    transportistas->size = 0;

    Transportista* temp;
    int n_transportistas_actual = 0;

    // Leer los datos de los transportistas del archivo
    while (fscanf(f, "%4[^-]-%20[^-]-%30[^-]-%15[^-]-%20[^-]-%20[^-]\n",
                  transportistas->transportistas[n_transportistas_actual].id_transportista,
                  transportistas->transportistas[n_transportistas_actual].nombre,
                  transportistas->transportistas[n_transportistas_actual].email,
                  transportistas->transportistas[n_transportistas_actual].contrasena,
                  transportistas->transportistas[n_transportistas_actual].nombre_empresa,
                  transportistas->transportistas[n_transportistas_actual].ciudad) == 6) {

        n_transportistas_actual++;
        temp = (Transportista*)realloc(transportistas->transportistas, (n_transportistas_actual + 1) * sizeof(Transportista));
        if (temp == NULL) {
            perror("Error al reservar memoria durante la lectura");
            free(transportistas->transportistas);
            fclose(f);
            return;
        }
        transportistas->transportistas = temp;
    }

    // Actualizar la cantidad de transportistas después de la lectura completa
    transportistas->size = n_transportistas_actual;
    fclose(f);
}

void guardar_transportistas(VectorTransportistas* transportistas)
{
    FILE* f = fopen("../data/Transportistas.txt", "w");
    if (f == NULL) {
        return;
    }
    int i;
    for (i = 0; i < transportistas->size; i++) {
        fprintf(f, "%s-%s-%s-%s-%s-%s\n",
                transportistas->transportistas[i].id_transportista,
                transportistas->transportistas[i].nombre,
                transportistas->transportistas[i].email,
                transportistas->transportistas[i].contrasena,
                transportistas->transportistas[i].nombre_empresa,
                transportistas->transportistas[i].ciudad);
    }
    fclose(f);
    free(transportistas->transportistas);
    transportistas->size = 0;
}

Transportista* buscar_transportista_id(VectorTransportistas* transportistas, char* id_transportista)
{
    int i;
    for (i = 0; i < transportistas->size; i++) {
        if (strcmp(transportistas->transportistas[i].id_transportista, id_transportista) == 0) {
            return &transportistas->transportistas[i];
        }
    }
    return NULL;
}

Transportista* buscar_transportista_email(VectorTransportistas* transportistas, char* email)
{
    int i;
    for (i = 0; i < transportistas->size; i++) {
        if (strcmp(transportistas->transportistas[i].email, email) == 0) {
            return &transportistas->transportistas[i];
        }
    }
    return NULL;
}

void listar_transportista(Transportista* transportista)
{
    printf(
        "---------------------------\n"
        "Nombre:     %s\n"
        "Email:  %s\n"
        "Empresa:  %s\n"
        "Ciudad:  %s\n",
        transportista->nombre,
        transportista->email,
        transportista->nombre_empresa,
        transportista->ciudad);
}

//Funcion de listar para los productos pedidos asignados a un transportista en un pedido
void listar_productos_asignados_pedido(VectorProductosPedido* v_productos_pedido, char* id_pedido, char* id_transportista)
{
    int i;
    for (i = 0; i < v_productos_pedido->size; i++) {
        if (strcmp(v_productos_pedido->productos_pedido[i].id_pedido, id_pedido) == 0 &&
            strcmp(v_productos_pedido->productos_pedido[i].id_transportista, id_transportista) == 0) {
            printf("========================================\n");
            printf("ID Pedido: %s\n", v_productos_pedido->productos_pedido[i].id_pedido);
            printf("ID Producto: %s\n", v_productos_pedido->productos_pedido[i].id_producto);
            printf("Unidades: %u\n", v_productos_pedido->productos_pedido[i].num_unidades);
            printf("Fecha prevista de entrega: %d/%d/%d\n", v_productos_pedido->productos_pedido[i].fecha_prevista_entrega.dia,
                   v_productos_pedido->productos_pedido[i].fecha_prevista_entrega.mes,
                   v_productos_pedido->productos_pedido[i].fecha_prevista_entrega.anio);
            printf("Importe: %.2f\n", v_productos_pedido->productos_pedido[i].importe);
            printf("Estado: %u\n", v_productos_pedido->productos_pedido[i].estado);
            printf("ID Locker: %s\n", v_productos_pedido->productos_pedido[i].id_locker);
            printf("Codigo Locker: %s\n", v_productos_pedido->productos_pedido[i].cod_locker);
            printf("Fecha de entrega o devolución: %d/%d/%d\n", v_productos_pedido->productos_pedido[i].fecha_entrega_devolucion.dia,
                   v_productos_pedido->productos_pedido[i].fecha_entrega_devolucion.mes,
                   v_productos_pedido->productos_pedido[i].fecha_entrega_devolucion.anio);
        }
    }
}

//Funcion de listar productos pedidos asignados a un transportista
void listar_productos_asignados(VectorPedidos* v_pedidos, VectorProductosPedido* v_productos_pedido, char* id_transportista)
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
            printf("ID Locker: %s\n", v_productos_pedido->productos_pedido[i].id_locker);
            printf("Codigo Locker: %s\n", v_productos_pedido->productos_pedido[i].cod_locker);
            printf("Fecha de entrega o devolución: %d/%d/%d\n", v_productos_pedido->productos_pedido[i].fecha_entrega_devolucion.dia,
                   v_productos_pedido->productos_pedido[i].fecha_entrega_devolucion.mes,
                   v_productos_pedido->productos_pedido[i].fecha_entrega_devolucion.anio);
        }
    }
}