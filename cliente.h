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

void cargar_clientes(VectorClientes* v_clientes);

void guardar_clientes(VectorClientes* v_clientes);

void listar_cliente(Cliente* cliente);

void modificar_cliente(Cliente* cliente);

Cliente* buscar_cliente_por_id(VectorClientes* v_clientes, char* id_cliente);

Cliente* buscar_cliente_por_email(VectorClientes* v_clientes, char* email);

void listar_clientes(VectorClientes* v_clientes);

void eliminar_cliente(VectorClientes* v_clientes, char* id_cliente);

void alta_cliente(VectorClientes* v_clientes);

#endif