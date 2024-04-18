
#ifndef _PRODUCTOS_H_
#define _PRODUCTOS_H_
#include "utilidades.h"
typedef struct{
	int identificador;
    char nombre[16];
	char descripcion[50];
	int id_categoria;
	int id_gestor;
	int stock;
	int envio;
	int importe;
}productos;


void mostrar_productos_clientes(productos*, int n_productos);
int buscar_pos_producto(productos* v_productos, int n_productos, int id_producto);



#endif//_MENU_CLIENTE_H_