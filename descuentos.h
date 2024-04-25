#ifndef DESCUENTOS_H_
#define DESCUENTOS_H_
#include "cliente.h"
#include "fecha.h"

// Estructura para almacenar la información de los distintos códigos promocionales de
//descuentos y cheques regalo a emplear en la compra de productos.
typedef struct {
    char id_codigo[11]; // 10 caracteres + '\0'
    char descripcion[51]; // Descripción del descuento
    char tipo[8]; // "codpro" o "cheqreg"
    char estado[9]; // "activo" o "inactivo"
    float importe; // Importe del descuento
    char aplicable[8]; // "todos" o "esizon"
} Descuento;

// Estructura para definir un vector de descuentos junto a su tamaño
typedef struct {
    Descuento* descuentos;
    unsigned n_descuentos;
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
    unsigned estado;             // 1 (Aplicado) o 0 (No aplicado)
} DescuentoCliente;

// Estructura para definir un vector de descuentos de clientes junto a su tamaño
typedef struct {
    DescuentoCliente* descuentosClientes;
    unsigned n_descuentosclientes;
} VectorDescuentosClientes;

/**
 * @brief Carga los descuentos desde un archivo de texto.
 * El archivo de texto tiene el siguiente formato:
 * id_codigo-descripcion-tipo-estado-importe-aplicable
 * @param v_descuentos Un puntero al vector de descuentos.
 * @pre El puntero v_descuentos no debe ser nulo.
 * @post Los descuentos se cargan en el vector de descuentos.
 * @return void
 */
void cargar_descuentos(VectorDescuentos* v_descuentos);
/**
 * @brief Guarda los descuentos en un archivo de texto.
 * El archivo de texto tiene el siguiente formato:
 * id_codigo-descripcion-tipo-estado-importe-aplicable
 * @param v_descuentos Un puntero al vector de descuentos.
 * @pre El puntero v_descuentos no debe ser nulo.
 * @post Los descuentos se guardan en un archivo de texto.
 * @return void
 */
void guardar_descuentos(VectorDescuentos* v_descuentos);

/**
 * @brief cargar descuentos de clientes desde un archivo de texto.
 * El archivo de texto tiene el siguiente formato:
 * id_cliente-id_codigo-fecha_asignacion-fecha_caducidad-estado
 * @param v_descuentosclientes Un puntero al vector de descuentos de clientes.
 * @pre El puntero v_descuentosclientes no debe ser nulo.
 * @post Los descuentos de clientes se cargan en el vector de descuentos de clientes.
 * @return void
 */
 void cargar_descuentos_clientes(VectorDescuentosClientes* v_descuentosclientes);
/**
 * @brief Guarda los descuentos de clientes en un archivo de texto.
 * El archivo de texto tiene el siguiente formato:
 * id_cliente-id_codigo-fecha_asignacion-fecha_caducidad-estado
 * @param v_descuentosclientes Un puntero al vector de descuentos de clientes.
 * @pre El puntero v_descuentosclientes no debe ser nulo.
 * @post Los descuentos de clientes se guardan en un archivo de texto.
 * @return void
 */

void guardar_descuentos_clientes(VectorDescuentosClientes* v_descuentosclientes);

/**
 * @brief Muestra los descuentos de un cliente.
 * @param v_descuentosclientes Un puntero al vector de descuentos de clientes.
 * @param v_descuentos Un puntero al vector de descuentos.
 * @param id_cliente El identificador del cliente.
 * @pre Los punteros v_descuentosclientes y v_descuentos no deben ser nulos.
 * @post Muestra los descuentos de un cliente.
 * @return void
 */
unsigned listar_descuentos_cliente(VectorDescuentosClientes* v_descuentosclientes, VectorDescuentos* v_descuentos, char* id_cliente);

/**
 * @brief Devuelve un descuento a partir de su ID.
 * @param v_descuentos Un puntero al vector de descuentos.
 * @param id_codigo El identificador del descuento.
 * @pre El puntero v_descuentos no debe ser nulo.
 * @post Devuelve un descuento a partir de su ID.
 * @return Un puntero al descuento.
 */
Descuento* buscar_descuento_id(VectorDescuentos* v_descuentos, char* id_codigo);
/**
 * @brief Devuelve un descuento de cliente a partir de su ID.
 * @param v_descuentosclientes Un puntero al vector de descuentos de clientes.
 * @param id_cliente El identificador del cliente.
 * @param id_codigo El identificador del descuento.
 * @pre El puntero v_descuentosclientes no debe ser nulo.
 * @post Devuelve un descuento de cliente a partir de su ID.
 * @return Un puntero al descuento de cliente.
 */
DescuentoCliente * buscar_descuentocliente(VectorDescuentosClientes* v_descuentosclientes, char* id_cliente, char* id_codigo);

/** 
 * @brief Función que verifica si un descuento es válido.
    * @param descuento_cliente Un puntero al descuento de cliente.
    * @param id_cliente El identificador del cliente.
    * @pre El puntero descuento_cliente no debe ser nulo.
    * @post Verifica si un descuento es válido.
    * @return 1 si el descuento es válido, 0 en caso contrario.

*/
int descuento_valido(DescuentoCliente *descuento_cliente, char* id_cliente);
/**
    * @brief Función que lista un descuento.
    * @param descuento El descuento a listar.
    * @return void
    

*/
void listar_descuento(Descuento* descuento);
/**

    * @brief Función que lista todos los descuentos.
    * @param v_descuentos Vector de descuentos
    * @return void
*/
void listar_descuentos(VectorDescuentos* v_descuentos);
/**
    *@brief Funcion que modifica un descuento
    * @param descuento Un puntero al descuento a modificar
    * @return Descuento* Puntero al descuento modificado


*/
Descuento* modificar_descuento(Descuento* descuento);

void listar_clientes_descuento(VectorClientes* v_clientes, VectorDescuentosClientes* v_descuentosclientes, char* id_codigo);
/**
    * @brief Función que da de alta un descuento
    * @param v_clientes Vector de clientes
    * @param v_descuentos Vector de descuentos
    * @param v_descuentoscliente Vector de descuentos de clientes
    

*/
Descuento* alta_descuento(VectorDescuentos* v_descuentos, VectorDescuentosClientes* v_descuentoscliente, VectorClientes* v_clientes);
/**

    * @brief Función que da de baja un descuento
    * @param id_descuento ID del descuento
    * @param v_descuentos Vector de descuentos
    * @param v_descuentoscliente Vector de descuentos de clientes
    


*/
void baja_descuento(char* id_descuento, VectorDescuentos* v_descuentos, VectorDescuentosClientes* v_descuentoscliente);
/**
    *@brief funcion que da de baja un descuento cliente
    * @param v_descuentoscliente Vector de descuentos de clientes
    * @param id_cliente ID del cliente
    * @param id_codigo ID del descuento
*/
void baja_descuentocliente(VectorDescuentosClientes* v_descuentoscliente, char* id_cliente, char* id_codigo);
/**
    * @brief Lista los clientes que han un descuento
    * @param v_clientes Vector de clientes
    * @param v_descuentosclientes Vector de descuentos de clientes
    * @param id_codigo Código del descuento
    

*/
void listar_clientes_descuento_usado(VectorClientes* v_clientes, VectorDescuentosClientes* v_descuentosclientes, char* id_codigo);

/**
    * @brief Función que asigna un descuento a un cliente
    * @param id_descuento ID del descuento
    * @param id_cliente ID del cliente
    * @param v_descuentos_cliente Vector de descuentos de clientes
    

*/
void asignar_descuento_cliente(char* id_descuento, char* id_cliente, VectorDescuentosClientes *v_descuentos_cliente);

#endif//DESCUENTOS_H_