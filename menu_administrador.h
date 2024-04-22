#ifndef MENU_ADMINISTRADOR_H
#define MENU_ADMINISTRADOR_H

#include "utilidades.h"
#include "adminprov.h"
#include "cliente.h"
#include "productos.h"
#include "adminprov.h"
#include "categoria.h"
#include "transportista.h"

void modificarIdEmpresa(AdminProv *admin);

void modificarNombre(AdminProv *admin);

void modificarEmail(AdminProv *admin);

void modificarContrasena(AdminProv *admin);

void perfilAdministrador(AdminProv* admin);

void gestionClientes();

void gestionProveedores();

void gestionProductos();

void gestionCategorias();

void gestionPedidos();

void gestionTransportistas();

void gestionDescuentos();

void gestionDevoluciones();

void mostrarMenuAdministrador(AdminProv* admin);

#endif //MENU_ADMINISTRADOR_H
