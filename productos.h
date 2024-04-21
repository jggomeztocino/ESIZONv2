#ifndef _PRODUCTOS_H_
#define _PRODUCTOS_H_

#include "utilidades.h"
#include "categoria.h"
#include "adminprov.h"
typedef struct{
	char id_producto[8];
    char nombre[16];
	char descripcion[51];
	char id_categoria[5];
	char id_gestor[5]; // Deberá coincidir con el identificador de la empresa administradora o proveedora del producto
	unsigned stock;
	unsigned entrega;
	float importe;
} Producto;

// Estructura para almacenar un vector de productos junto a su tamaño
typedef struct{
	Producto* productos;
	unsigned size;
} VectorProductos;



void cargar_productos(VectorProductos* v_productos);

void guardar_productos(VectorProductos* v_productos);

Producto* alta_producto(VectorProductos* v_productos, VectorCategorias* v_categorias, VectorAdminProv* v_adminprov);

void baja_producto(VectorProductos* v_productos, char* id_producto);

Producto* buscar_producto_id(VectorProductos* v_productos, char* id_producto);

void listar_producto(Producto* producto);

Producto* modificar_producto(Producto* producto, VectorCategorias* v_categorias, VectorAdminProv * v_adminprov);

void listar_productos(VectorProductos* v_productos);

void listar_productos_categoria(VectorProductos* v_productos, int id_categoria);

unsigned listar_productos_nombre(VectorProductos* v_productos, char* nombre);

void listar_productos_gestor(VectorProductos* v_productos, char* id_gestor);

#endif//ESIZON_PRODUCTOS_H_