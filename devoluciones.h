
#ifndef DEVOLUCIONES_H_
#define DEVOLUCIONES_H_


// #include "pedido.h"
 #include "fecha.h"

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

    * @brief Función que da de alta una devolución
    * @param id_pedido ID del pedido
    * @param id_producto ID del producto
    * @param fecha_devolucion Fecha de la devolución
    * @param v_devoluciones Vector de devoluciones
    * @return void

*/

void alta_devolucion(char* id_pedido, char* id_producto, Fecha* fecha_devolucion, VectorDevoluciones* v_devoluciones);


void baja_devolucion(char* id_pedido, char* id_producto, VectorDevoluciones* v_devoluciones);
/**
 * Función que solicita los datos de una devolución
 * @param cliente
 * @param v_pedidos
 * @param v_productos_pedido
 * @param v_devoluciones
 */
//void realizar_devolucion(Cliente *cliente, VectorPedidos v_pedidos, VectorProductosPedido v_productos_pedido, VectorDevoluciones v_devoluciones);

Devolucion* buscar_devolucion(char* id_pedido, char* id_producto, VectorDevoluciones* v_devoluciones);
/**

    * @brief Función que lista una devolución
    * @param devolucion Devolución a listar
    * @return void
    
*/
void listar_devolucion(Devolucion* devolucion);
/**

    * @brief Función que lista todas las devoluciones
    * @param v_devoluciones Vector de devoluciones
    * @return void
    

*/
void listar_devoluciones(VectorDevoluciones* v_devoluciones);
/**
    
        * @brief Función que lista las devoluciones de un cliente
        * @param v_devoluciones Vector de devoluciones
        * @param id_cliente ID del cliente
        * @return unsigned Número de devoluciones del cliente
        


*/
unsigned listar_devoluciones_cliente(VectorDevoluciones* v_devoluciones, char* id_cliente);
/**
    
        * @brief Función que modifica una devolución
        * @param devolucion Devolución a modificar
        * @return Devolucion* Puntero a la devolución modificada
        

*/
Devolucion* modificar_devolucion(Devolucion* devolucion);

#endif//DEVOLUCIONES_H_