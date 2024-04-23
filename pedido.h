#ifndef PEDIDO_H_
#define PEDIDO_H_

#include "fecha.h"
#include "descuentos.h"
#include "productos.h"
#include "locker.h"
#include "pedido.h"
#include "devoluciones.h"
#include "utilidades.h"
#include "cliente.h"


typedef struct{
	char id_pedido[8]; // 7 dígitos + '\0'
	Fecha fecha;
	char id_cliente[8]; // 7 dígitos + '\0'
	unsigned lugar; //: 1: «domicilio», 2: «locker»
	char id_locker[11];
	char id_descuento[11]; // Si aplica
} Pedido;

// Estructura para definir un vector de Pedido junto a su tamaño
typedef struct{
    Pedido* pedidos;
    int size;
} VectorPedidos;

typedef struct
{
    char id_pedido[8];                // 7 dígitos + '\0'
    char id_producto[9];                // 7 dígitos + '\0'
    unsigned num_unidades;               // Número de unidades del producto en el pedido
    Fecha fecha_prevista_entrega;   // Fecha prevista para la entrega
    float importe;                  // Importe total del producto en el pedido
    unsigned estado;                // Estado del producto en el pedido (1: «enPreparacion», 2: «enviado», 3: «enReparto», 4: «enLocker», 5: «entregado», 6: «devuelto», 7: «transportista»)
    char id_transportista[5];       // 4 dígitos + '\0'
    char id_locker[11];           // 10 caracteres + '\0'
    unsigned cod_locker;            // Código del locker (si aplica)
    Fecha fecha_entrega_devolucion; // Fecha de entrega o devolución
} ProductoPedido;

// Estructura para definir un vector de ProductoPedido junto a su tamaño
typedef struct {
    ProductoPedido* productos_pedido;
    int size;
} VectorProductosPedido;

/**
 * @brief Carga los pedidos desde el archivo Pedidos.txt
 *     y los almacena en un vector de pedidos
 * @param v_pedidos Vector de pedidos
 */
 void cargar_pedidos(VectorPedidos* v_pedidos);
/**
* @brief Guarda los pedidos en el archivo Pedidos.txt
* @param v_pedidos Vector de pedidos
*/
void guardar_pedidos(VectorPedidos* v_pedidos);

/**
 * @brief Busca un pedido por su identificador
 *
 * @param v_pedidos Vector de pedidos
 * @param id_pedido Identificador del pedido
 * @return Pedido* Puntero al pedido encontrado o NULL si no se encuentra
 */

Pedido* buscar_pedido_por_id(VectorPedidos* v_pedidos, char* id_pedido);



/**
 * @brief Función que lista los pedidos de un cliente
 *
 * @param v_pedidos Vector de pedidos
 * @param id_cliente Identificador del cliente
 *
 * @return unsigned Número de pedidos del cliente
 */
 unsigned listar_pedidos_cliente(VectorPedidos* v_pedidos, char* id_cliente);

/**
 * @brief Función que lista los productos de un pedido
 *
 * @param v_productos_pedido Vector de productos de pedido
 * @param id_pedido Identificador del pedido
 */
 void listar_productos_pedido(VectorProductosPedido *v_productos_pedido, char *id_pedido);

/**
    Funcion que lista los productos asignados a un pedido
    para un transportista en concreto
    @param v_productos_pedido Vector de productos pedido
    @param id_pedido Identificador del pedido
    @param id_transportista Identificador del transportista

 */
 // void listar_productos_asignados_pedido(VectorProductosPedido* v_productos_pedido, char* id_pedido, char* id_transportista);

//Funcion que lista los pedidos de un cliente que se encuentran en lockers
void listar_pedidos_locker_decliente(VectorPedidos *v_pedidos, char *id_cliente);

/**
 * Función que comprueba si un producto pedido pertenece a un pedido
 * @param v_productos_pedido Vector de productos pedido
 * @param id_pedido Identificador del pedido
 * @param id_producto Identificador del producto
 */
 int pertenece_pedido(VectorProductosPedido *v_productos_pedido, char *id_pedido, char *id_producto);

/**
 * Función que busca un producto pedido por su id_pedido, id_producto
 * @param v_productos_pedido Vector de productos pedido
 * @param id_pedido Identificador del pedido
 * @param id_producto Identificador del producto
 * @return ProductoPedido* Puntero al producto pedido encontrado o NULL si no se encuentra
 */
 ProductoPedido *buscar_producto_pedido(VectorProductosPedido *v_productos_pedido, char *id_pedido, char *id_producto);

/**
 * @brief Función que busca un producto pedido por su compartimento
 *
 * @param v_productos_pedido Vector de productos pedido
 * @param id_locker Identificador del locker
 * @param n_compartimento Número de compartimento
 * @return ProductoPedido* Producto pedido encontrado o NULL si no se encuentra
 */
 ProductoPedido *buscar_producto_pedido_por_compartimento(VectorProductosPedido *v_productos_pedido, char *id_locker, unsigned n_compartimento);


/**
 * @brief Realiza un pedido
 *
 * @param cliente Cliente que realiza el pedido
 * @param v_pedidos Vector de pedidos
 * @param v_productos_pedido Vector de productos pedido
 * @param v_lockers Vector de lockers
 * @param v_compartimentos Vector de compartimentos
 * @param v_descuentos Vector de descuentos
 * @param v_descuentos_cliente Vector de descuentos de cliente
 * @param v_productos Vector de productos
 */
void realizar_pedido(Cliente *cliente, VectorPedidos *v_pedidos, VectorProductosPedido *v_productos_pedido, VectorLockers *v_lockers, VectorDescuentos *v_descuentos, VectorDescuentosClientes *v_descuentos_cliente, VectorProductos *v_productos);
/**
 * @brief Carga los productos de pedido desde el archivo productos_pedido.txt
 * @param v_productos_pedido Vector de productos de pedido
 */
 void cargar_productos_pedido(VectorProductosPedido* v_productos_pedido);
/**
 * @brief Guarda los productos de pedido en el archivo productos_pedido.txt
 *
 * @param v_productos_pedido Vector de productos de pedido
 */
 void guardar_productos_pedido(VectorProductosPedido* v_productos_pedido);

/**
 * @brief Listado de productos de un pedido asignados a un transportista
 * @param v_productos_pedido Vector de productos de pedido
 * @param id_transportista Identificador del transportista
 *
 * @return unsigned Número de productos asignados al transportista
 */
unsigned listar_productos_transportista(VectorProductosPedido* v_productos_pedido, char* id_transportista);

/**
 * @brief Lista un pedido
 * @param pedido Pedido a listar
 */
void listar_pedido(Pedido* pedido);

/**
 * @brief Lista un producto de pedido
 * @param producto_pedido Producto de pedido a listar
 */
void listar_producto_pedido(ProductoPedido* producto_pedido);

/**
 * @brief Modifica un pedido
 * @param Pedido* pedido Pedido a modificar
 *
 * \returns Pedido* Puntero al pedido modificado
 */
Pedido* modificar_pedido(Pedido* pedido);

#endif//PEDIDO_H_
