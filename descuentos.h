#ifndef _DESCUENTOS_H_
#define _DESCUENTOS_H_

#include "fecha.h"

// Estructura para almacenar la información de los distintos códigos promocionales de
//descuentos y cheques regalo a emplear en la compra de productos.
typedef struct {
    char id_codigo[11]; // 10 caracteres + '\0'
    char descripcion[51]; // Descripción del descuento
    char tipo[8]; // "codpro" o "cheqreg"
    char estado[8]; // "activo" o "inactivo"
    float importe; // Importe del descuento
    char aplicable[8]; // "todos" o "esizon"
} Descuento;

// Estructura para definir un vector de descuentos junto a su tamaño
typedef struct {
    Descuento* descuentos;
    int n_descuentos;
} VectorDescuentos;

// Estructura para almacenar la información de los distintos códigos promocionales
// de descuentos y cheques regalo de cada cliente registrado en la plataforma.
// Es decir, los descuentos que tiene cada cliente.
typedef struct
{
    char id_cliente[8];     // 7 dígitos + '\0'
    char id_codigo[11];     // 10 caracteres + '\0'
    Fecha fecha_asignacion; // Fecha en que se asignó el descuento
    Fecha fecha_caducidad;  // Fecha en que caduca el descuento
    int estado;             // 1 (Aplicado) o 0 (No aplicado)
} DescuentoCliente;

// Estructura para definir un vector de descuentos de clientes junto a su tamaño
typedef struct {
    DescuentoCliente* descuentosClientes;
    int n_descuentosclientes;
} VectorDescuentosClientes;

// Funciones para cargar y guardar los descuentos (al estilo de cliente.c)
void cargar_descuentos(VectorDescuentos* v_descuentos);
void guardar_descuentos(VectorDescuentos* v_descuentos);

// Funciones para cargar y guardar los descuentos de los clientes (al estilo de cliente.c)
void cargar_descuentos_clientes(VectorDescuentosClientes* v_descuentosclientes);
void guardar_descuentos_clientes(VectorDescuentosClientes* v_descuentosclientes);

/*
 * Función que muestra los descuentos de un cliente.
 * Itera sobre los descuentos de un cliente y los muestra por pantalla,
 * buscando la información correspondiente en el vector de descuentos.
 */
void mostrar_descuentos_cliente(VectorDescuentosClientes* v_descuentosclientes, VectorDescuentos* v_descuentos, char* id_cliente);

/*
 * Función que devuelve un descuento a partir de su id.
 */
Descuento* obtener_descuento(VectorDescuentos* v_descuentos, char* id_codigo);

DescuentoCliente * obtener_descuento_cliente(VectorDescuentosClientes* v_descuentosclientes, char* id_cliente, char* id_codigo);
#endif//_DESCUENTOS_H_