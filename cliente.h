#ifndef CLIENTE_H_
#define CLIENTE_H_

typedef struct {
    char id_cliente[8]; // 7 dígitos + '\0'
    char nombre_cliente[21];
    char direccion_cliente[51];
    char poblacion[21];
    char provincia[21];
    char email[31];
    char contrasena[16];
    float cartera; // Monto disponible en la cartera del cliente
} Cliente;

// Vector de clientes
typedef struct {
    Cliente *clientes;
    unsigned size;
} VectorClientes;
/**
 * @brief Carga los clientes desde un archivo de texto.
 * El archivo de texto tiene el siguiente formato:
 * id_cliente-nombre_cliente-direccion_cliente-poblacion-provincia-email-contrasena-cartera
 * @param v_clientes Un puntero al vector de clientes.
 * @pre El puntero v_clientes no debe ser nulo.
 * @post Los clientes se cargan en el vector de clientes.
 * @return void
 */
void cargar_clientes(VectorClientes* v_clientes);
/**
 * @brief Guarda los clientes en un archivo de texto.
 * El archivo de texto tiene el siguiente formato:
 * id_cliente-nombre_cliente-direccion_cliente-poblacion-provincia-email-contrasena-cartera
 * @param v_clientes Un puntero al vector de clientes.
 * @pre El puntero v_clientes no debe ser nulo.
 * @post Los clientes se guardan en un archivo de texto.
 * @return void
 */
void guardar_clientes(VectorClientes* v_clientes);

/**
  Funcion que lista un cliente
 * @param cliente Un puntero al cliente a listar
 * @pre El puntero cliente no debe ser nulo
 * @post Se muestra por pantalla el cliente
 * @return void
 */
void listar_cliente(Cliente* cliente);
/**
  Funcion que modifica un cliente
 * @param cliente Un puntero al cliente a modificar
 * @pre El puntero cliente no debe ser nulo
 * @post Se modifica el cliente
 * @return void
 */
void modificar_cliente(Cliente* cliente);
/**
  Funcion que busca un cliente por su id
 * @param v_clientes Un puntero al vector de clientes
 * @param id_cliente El id del cliente a buscar
 * @pre El puntero v_clientes no debe ser nulo
 * @post Se devuelve el cliente si se encuentra, en caso contrario se devuelve NULL
 * @return Cliente* El cliente encontrado o NULL
 */
Cliente* buscar_cliente_por_id(VectorClientes* v_clientes, char* id_cliente);
/**
  Funcion que busca un cliente por su email
 * @param v_clientes Un puntero al vector de clientes
 * @param email El email del cliente a buscar
 * @pre El puntero v_clientes no debe ser nulo
 * @post Se devuelve el cliente si se encuentra, en caso contrario se devuelve NULL
 * @return Cliente* El cliente encontrado o NULL
 */
Cliente* buscar_cliente_por_email(VectorClientes* v_clientes, char* email);
/**
  Funcion que lista todos los clientes
 * @param v_clientes Un puntero al vector de clientes
 * @pre El puntero v_clientes no debe ser nulo
 * @post Se muestran por pantalla todos los clientes
 * @return void
 */
void listar_clientes(VectorClientes* v_clientes);
/**
  Funcion que eliminar un cliente
    * @param v_clientes Un puntero al vector de clientes
    * @param id_cliente El id del cliente a eliminar
    * @pre El puntero v_clientes no debe ser nulo
    * @post Se elimina el cliente del vector de clientes
    * @return void
 */
void eliminar_cliente(VectorClientes* v_clientes, char* id_cliente);
/**
  Funcion que añade un cliente
 * @param v_clientes Un puntero al vector de clientes
 * @pre El puntero v_clientes no debe ser nulo
 * @post Se añade un cliente al vector de clientes
 * @return void
 */
void alta_cliente(VectorClientes* v_clientes);

#endif