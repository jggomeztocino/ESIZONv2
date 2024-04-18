
#ifndef _MENU_CLIENTE_H_
#define _MENU_CLIENTE_H_

#include "cliente.h"
#include "productos.h"
#include "pedido.h"
#include "descuentos.h"
#include "devoluciones.h"

void menu_cliente(VectorClientes* v_clientes, VectorProductos* v_productos, VectorPedidos* v_pedidos, VectorDescuentos* v_descuentos, VectorDevoluciones* v_devoluciones, VectorDescuentosClientes* v_descuentos_clientes, VectorProductosPedido* v_productos_pedido);

#endif//_MENU_CLIENTE_H_