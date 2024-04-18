#ifndef _PRODUCTOS_H_
#define _PRODUCTOS_H_

typedef struct{
	char id_producto[8];
    char nombre[16];
	char descripcion[51];
	char id_categoria[5];
	char id_gestor[5];
	unsigned stock;
	unsigned entrega;
	float importe;
} Producto;

// Estructura para almacenar un vector de productos junto a su tamaño
typedef struct{
	Producto* productos;
	unsigned size;
} VectorProductos;

void cargar_productos(VectorProductos* productos);

void guardar_productos(VectorProductos* productos);

Producto* buscar_producto_id(VectorProductos* productos, char* id_producto);

void listar_producto(Producto* producto);

void listar_productos(VectorProductos* productos);

void listar_productos_categoria(VectorProductos* productos, int id_categoria);

void listar_productos_nombre(VectorProductos* productos, char* nombre);

#endif//_MENU_CLIENTE_H_