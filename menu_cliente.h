
#ifndef _MENU_CLIENTE_H_
#define _MENU_CLIENTE_H_

#include "cliente.h"
#include "productos.h"
#include "descuentos.h"
#include "devoluciones.h"
#include "pedido.h"
#include "utilidades.h"


/*Esta funcion recibirá tambien los punteros a los vectores de productos 
, descuentos , pedidos y devoluciones . 

Por el momento se quedará asi para que no dé error de compilación , cuando se añadan los módulos correspondientes 
se incluiran los vectores a esta estructura , por el momento se incluyen los punteros que contendrán las 
direcciones de memoria de los enteros que contienen las ocurrencias de cada estructura en la estructura de tipo n_struct definida en entrada_salida.h


*/
void menu_cliente(Devolucion * v_devoluciones,Cliente * v_clientes,productos *v_productos,Descuento* v_descuentos, DescuentoCliente*v_descuentosclientes, pedidos *v_pedidos,ProductoPedido * v_productospedidos ,int pos_cliente);





#endif//_MENU_CLIENTE_H_