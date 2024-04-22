#ifndef PRODUCTOS_H_
#define PRODUCTOS_H_

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


/**
 * Carga los productos desde el archivo Productos.txt
 * @param v_productos Puntero a la estructura VectorProductos
 */
void cargar_productos(VectorProductos* v_productos);
/**
 * Guarda los productos en el archivo Productos.txt
 * @param v_productos Puntero a la estructura VectorProductos
 */
void guardar_productos(VectorProductos* v_productos);
/**
 * Añade un producto al vector de productos
 * @param v_productos Puntero a la estructura VectorProductos
 * @param v_categorias Puntero a la estructura VectorCategorias
 * @param v_adminprov Puntero a la estructura VectorAdminProv
 * @return Puntero al producto añadido
 */
Producto* alta_producto(VectorProductos* v_productos, VectorCategorias* v_categorias,  VectorAdminProv* v_adminprov);
/**
 * Elimina un producto del vector de productos
 * @param v_productos Puntero a la estructura VectorProductos
 * @param id_producto ID del producto a eliminar
 */
void baja_producto(VectorProductos* v_productos, char* id_producto);
/**
 * Busca un producto por su ID
 * @param v_productos Puntero a la estructura VectorProductos
 * @param id_producto ID del producto a buscar
 * @return Puntero al producto encontrado o NULL si no se encuentra
 */
Producto* buscar_producto_id(VectorProductos* v_productos, char* id_producto);
/**
    * Muestra los datos de un producto
    * @param producto Puntero al producto a mostrar
    * @return void
 */
void listar_producto(Producto* producto);

Producto* modificar_producto(Producto* producto, VectorCategorias* v_categorias, VectorAdminProv* v_adminprov);
/**
 * Muestra los datos todos los productos
 * @param v_productos Puntero a la estructura VectorProductos
 * @return void
 */
void listar_productos(VectorProductos* v_productos);

/**
 * Busca un producto por su id_categoria
 * @param v_productos Puntero a la estructura VectorProductos
 * @param id_categoria ID de la categoría a buscar
 */
unsigned listar_productos_categoria(VectorProductos* v_productos, char* id_categoria);
/**
 * Busca un producto por su nombre
 * @param v_productos Puntero a la estructura VectorProductos
 * @param nombre Nombre del producto a buscar
 * @return Número de productos encontrados
 */
unsigned listar_productos_nombre(VectorProductos* v_productos, char* nombre);

void listar_productos_gestor(VectorProductos* v_productos, char* id_gestor);
/**
 * Elimina todos los productos de una categoría
 * @param v_productos Puntero a la estructura VectorProductos
 * @param id_categoria ID de la categoría a eliminar
 */
void eliminar_productos_categoria(VectorProductos* v_productos, char* id_categoria);


// Menu que pregunta si se quiere listar los productos por id o categoria
void listado_productos();
#endif //PRODUCTOS_H_