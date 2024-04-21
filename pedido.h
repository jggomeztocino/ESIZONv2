#ifndef _PEDIDO_H_
#define _PEDIDO_H_

#include "fecha.h"
#include "descuentos.h"
#include "productos.h"

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
    char cod_locker[21];            // Código del locker (si aplica)
    Fecha fecha_entrega_devolucion; // Fecha de entrega o devolución
} ProductoPedido;

// Estructura para definir un vector de ProductoPedido junto a su tamaño
typedef struct {
    ProductoPedido* productos_pedido;
    int size;
} VectorProductosPedido;

// Funciones para cargar y guardar los pedidos (al estilo de cliente.c)
void cargar_pedidos(VectorPedidos* v_pedidos);
void guardar_pedidos(VectorPedidos* v_pedidos);

// Búsqueda de un pedido por su identificador
Pedido* buscar_pedido_por_id(VectorPedidos* v_pedidos, char* id_pedido);



// Listado de pedidos de un cliente
void listar_pedidos_cliente(VectorPedidos* v_pedidos, char* id_cliente);

//Listado de productos de un pedido
void listar_productos_pedido(VectorProductosPedido *v_productos_pedido, char *id_pedido);

//Funcion de listar para los productos pedidos asignados a un transportista en un pedido
void listar_productos_asignados_pedido(VectorProductosPedido* v_productos_pedido, char* id_pedido, char* id_transportista);

//Funcion que lista los pedidos de un cliente que se encuentran en lockers
void listar_pedidos_locker_decliente(VectorPedidos *v_pedidos, char *id_cliente);

//Comprueba si un producto pertenece a un pedido
int pertenece_pedido(VectorProductosPedido *v_productos_pedido, char *id_pedido, char *id_producto);

//FUncion que devuelve un producto pedido que se busca mediante , id del pedido , id del producto ,transportista asignado y estado de enReparto
ProductoPedido *buscar_producto_pedido(VectorProductosPedido *v_productos_pedido, char *id_pedido, char *id_producto, char *id_transportista);


// Funciones para cargar y guardar los productos de un pedido (al estilo de cliente.c)
void cargar_productos_pedido(VectorProductosPedido* v_productos_pedido);
void guardar_productos_pedido(VectorProductosPedido* v_productos_pedido);

#endif//_PEDIDO_H_
