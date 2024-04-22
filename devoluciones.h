
#ifndef DEVOLUCIONES_H_
#define DEVOLUCIONES_H_


#include "pedido.h"
#include "fecha.h"
#include "productos.h"
#include "cliente.h"


typedef struct
{
    char id_pedido[8];      // 7 dígitos + '\0'
    char id_producto[8];    // 7 dígitos + '\0'
    Fecha fecha_devolucion; // Fecha en que se realizó la devolución
    char motivo[51];        // Motivo de la devolución
    char estado[9];         // Estado de la devolución («pendiente» (de aceptación), «aceptado», «denegado», «enviado» (por cliente) o «recibido»)
    Fecha fecha_aceptacion; // Fecha en que se aceptó la devolución
    Fecha fecha_caducidad;  // Fecha de caducidad de la devolución
} Devolucion;

// Estructura para definir un vector de devoluciones junto a su tamaño
typedef struct {
    Devolucion* devoluciones;
    unsigned n_devoluciones;
} VectorDevoluciones;

/**
 * @brief Carga las devoluciones desde un archivo de texto.
 * El archivo de texto tiene el siguiente formato:
 * id_pedido-id_producto-fecha_devolucion-motivo-estado-fecha_aceptacion-fecha_caducidad
 * @param v_devoluciones Un puntero al vector de devoluciones.
 * @pre El puntero v_devoluciones no debe ser nulo.
 * @post Las devoluciones se cargan en el vector de devoluciones.
 * @return void
 */
void cargar_devoluciones(VectorDevoluciones* v_devoluciones);
/**
 * @brief Guarda las devoluciones en un archivo de texto.
 * El archivo de texto tiene el siguiente formato:
 * id_pedido-id_producto-fecha_devolucion-motivo-estado-fecha_aceptacion-fecha_caducidad
 * @param v_devoluciones Un puntero al vector de devoluciones.
 * @pre El puntero v_devoluciones no debe ser nulo.
 * @post Las devoluciones se guardan en un archivo de texto.
 * @return void
 */
void guardar_devoluciones(VectorDevoluciones* v_devoluciones);

/**
 * @brief Función que busca una devolución por su id.
 * @param v_pedidos
 * @param v_devoluciones
 * @param id_cliente
 * @pre El puntero v_devoluciones no debe ser nulo.
 * @post Se muestra por pantalla la devolución encontrada.
 */
 void mostrar_devoluciones_pendientes(VectorPedidos *v_pedidos, VectorDevoluciones *v_devoluciones, char *id_cliente);


void alta_devolucion(VectorDevoluciones* v_devoluciones, Pedido* pedido, char* id_producto, char* motivo);
/*
 * Función que permite modificar el estado de una devolución
 * 1. Pendiente
 * 2. Aceptado
 * 3. Denegado
 * 4. Enviado
 * 5. Recibido
 */
void modificar_estado_devolucion(VectorDevoluciones* v_devoluciones, char* id_devolucion, unsigned nuevo_estado);
/**
 * Función que solicita los datos de una devolución
 * @param cliente
 * @param v_pedidos
 * @param v_productos_pedido
 * @param v_devoluciones
 */
void realizar_devolucion(Cliente *cliente, VectorPedidos v_pedidos, VectorProductosPedido v_productos_pedido, VectorDevoluciones v_devoluciones);

#endif//DEVOLUCIONES_H_