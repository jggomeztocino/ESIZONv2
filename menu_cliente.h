
#ifndef MENU_CLIENTE_H_
#define MENU_CLIENTE_H_

#include "cliente.h"
#include "productos.h"
#include "pedido.h"
#include "descuentos.h"
#include "devoluciones.h"
#include "utilidades.h"
#include "locker.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "fecha.h"

/**
    * @brief Muestra el menú de opciones para el cliente
    * @param cliente Puntero a la estructura Cliente
*/
void menu_cliente(Cliente *cliente);
#endif//MENU_CLIENTE_H_