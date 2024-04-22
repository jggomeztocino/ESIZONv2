
#ifndef DEVOLUCIONES_H_
#define DEVOLUCIONES_H_


#include "pedido.h"
#include "fecha.h"
#include "productos.h"

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

// Funciones para cargar y guardar las devoluciones (al estilo de cliente.c)
void cargar_devoluciones(VectorDevoluciones* v_devoluciones);
void guardar_devoluciones(VectorDevoluciones* v_devoluciones);

// Función que muestra las devoluciones con estado pendiente de un cliente.
void mostrar_devoluciones_pendientes(VectorDevoluciones* v_devoluciones, char* id_cliente);

// Función que da de alta una devolución.
void alta_devolucion(VectorDevoluciones* v_devoluciones, char* id_cliente, char* id_pedido, char* id_producto, char* motivo);

/*
 * Función que permite modificar el estado de una devolución
 * 1. Pendiente
 * 2. Aceptado
 * 3. Denegado
 * 4. Enviado
 * 5. Recibido
 */
void modificar_estado_devolucion(VectorDevoluciones* v_devoluciones, char* id_devolucion, unsigned nuevo_estado);


#endif//DEVOLUCIONES_H_