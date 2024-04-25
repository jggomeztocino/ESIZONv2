#ifndef MENU_ADMINISTRADOR_H
#define MENU_ADMINISTRADOR_H

#include "utilidades.h"
#include "adminprov.h"
#include "cliente.h"
#include "productos.h"
#include "adminprov.h"
#include "categoria.h"
#include "transportista.h"
#include "pedido.h"
#include "descuentos.h"
/**
    * @brief   Muestra el perfil del administrador y permite modificarlo
    * @param admin Puntero a la estructura AdminProv

*/
void perfilAdministrador(AdminProv* admin);
/**
    * @brief Gestiona los clientes
*/
void gestionClientes();
/**
    * @brief Gestiona los proveedores
*/
void gestionProveedores();
/**
    * @brief Gestiona los productos
*/
void gestionProductos();
/**
    * @brief Gestiona las categorías

*/
void gestionCategorias();
/**
    * @brief Gestiona los pedidos


*/
void gestionPedidos();
/**
    * @brief Gestiona los transportistas
*/
void gestionTransportistas();
/**
    * @brief Gestiona los descuentos

*/
void gestionDescuentos();
/**
    * @brief Gestiona las devoluciones

*/
void gestionDevoluciones();
/**
    * @brief Muestra el menú de opciones para el administrador
    * @param admin Puntero a la estructura AdminProv

*/
void mostrarMenuAdministrador(AdminProv *admin);

#endif //MENU_ADMINISTRADOR_H
