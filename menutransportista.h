#ifndef ESIZON_MENUTRANSPORTISTA_H
#define ESIZON_MENUTRANSPORTISTA_H


#include "productos.h"
#include "pedido.h"
#include "locker.h"
#include "transportista.h"
#include "utilidades.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "fecha.h"

/**
 * @brief Muestra el menú de opciones para el transportista
 * @param transportista Puntero a la estructura Transportista
 */
void mostrar_menu_transportista(Transportista *transportista);

#endif //ESIZON_MENUTRANSPORTISTA_H
