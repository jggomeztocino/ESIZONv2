#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "menu_administrador.h"

// Funcion para modificar el ID de la empresa del administrador
void modificarIdEmpresa(AdminProv *admin) {
    char nuevoId[5];
    leer_cadena("Ingrese el nuevo ID de Empresa", nuevoId, sizeof(nuevoId));
    strcpy(admin->id_empresa, nuevoId);
    printf("ID de Empresa actualizado con exito.\n");
}

// Funcion para modificar el nombre del administrador
void modificarNombre(AdminProv *admin) {
    char nuevoNombre[21];
    leer_cadena("Ingrese el nuevo nombre", nuevoNombre, sizeof(nuevoNombre));
    strcpy(admin->nombre, nuevoNombre);
    printf("Nombre actualizado con exito.\n");
}

// Funcion para modificar el email del administrador
void modificarEmail(AdminProv *admin) {
    char nuevoEmail[31];
    leer_cadena("Ingrese el nuevo email", nuevoEmail, sizeof(nuevoEmail));
    strcpy(admin->email, nuevoEmail);
    printf("Email actualizado con exito.\n");
}

// Funcion para modificar la contrasena del administrador
void modificarContrasena(AdminProv *admin) {
    char nuevaContrasena[16];
    leer_cadena("Ingrese la nueva contrasena", nuevaContrasena, sizeof(nuevaContrasena));
    strcpy(admin->contrasena, nuevaContrasena);
    printf("Contrasena actualizada con exito.\n");
}

// Funcion para mostrar y modificar el perfil del administrador
void perfilAdministrador(AdminProv* admin) {
    int opcion;

    // Menu para modificar los datos del perfil
    do {
        printf("\nPerfil Administrador\n");
        printf("ID Empresa: %s\n", admin->id_empresa);
        printf("Nombre: %s\n", admin->nombre);
        printf("Email: %s\n", admin->email);
        printf("Contrasena: %s\n", admin->contrasena);


        printf("\nModificar perfil:\n");
        printf("1. ID Empresa\n");
        printf("2. Nombre\n");
        printf("3. Email\n");
        printf("4. Contrasena\n");
        printf("5. Volver\n");
        leer_entero("Seleccione una opcion para modificar", &opcion);

        switch (opcion) {
            case 1:
                modificarIdEmpresa(admin);
                break;
            case 2:
                modificarNombre(admin);
                break;
            case 3:
                modificarEmail(admin);
                break;
            case 4:
                modificarContrasena(admin);
                break;
            case 5:
                printf("Volviendo...\n");
                break;
            default:
                printf("Opcion no valida, por favor intente de nuevo.\n");
        }
    } while (opcion != 5);
}

/*
 * Mediante esta opción el administrador podrá acceder a la información de los clientes dados de alta en la plataforma.
 * Mediante el menú correspondiente podrá realizar altas, bajas, búsquedas, listados y modificaciones de clientes.
 * Se hará uso de las funciones definidas en el módulo de cliente
 */
void gestionClientes() {
    VectorClientes v_clientes;
    cargar_clientes(&v_clientes);

    /* Menú con las distintas opciones de gestión de clientes */
    int opcion;
    unsigned int id_cliente;
    unsigned opcion_busqueda;
    do {
        printf("\nGESTION DE CLIENTES\n");
        printf("1. Alta de cliente\n");
        printf("2. Baja de cliente\n");
        printf("3. Buscar cliente\n");
        printf("4. Listar clientes\n");
        printf("5. Modificar cliente\n");
        printf("6. Volver\n");
        leer_entero("Seleccione una opcion", &opcion);

        switch (opcion) {
            case 1:
                alta_cliente(&v_clientes);
                break;
            case 2:
                leer_unsigned("Ingrese el ID del cliente a eliminar", &id_cliente);
                eliminar_cliente(&v_clientes, id_cliente);
                break;
            case 3:
                // Pregunta si se desea buscar por ID o por email
                leer_unsigned("Buscar por:\n1. ID\n2. Email", &opcion_busqueda);
                if (opcion_busqueda == 1) {
                    // Buscar por ID
                    leer_unsigned("Ingrese el ID del cliente a buscar", &id_cliente);
                    Cliente *cliente = buscar_cliente_por_id(&v_clientes, id_cliente);
                    if (cliente != NULL) {
                        listar_cliente(cliente);
                        // Preguntar si se desea modificar el cliente
                        char respuesta[2];
                        leer_cadena("Desea modificar este cliente? (s/n)", respuesta, sizeof(respuesta));
                        if (strcmp(respuesta, "s") == 0) {
                            modificar_cliente(cliente);
                        }
                    } else {
                        printf("Cliente no encontrado.\n");
                    }
                } else if (opcion_busqueda == 2) {
                    // Buscar por email
                    char email[31];
                    leer_cadena("Ingrese el email del cliente a buscar", email, sizeof(email));
                    Cliente *cliente = buscar_cliente_por_email(&v_clientes, email);
                    if (cliente != NULL) {
                        listar_cliente(cliente);
                        // Preguntar si se desea modificar el cliente
                        char respuesta[2];
                        leer_cadena("Desea modificar este cliente? (s/n)", respuesta, sizeof(respuesta));
                        if (strcmp(respuesta, "s") == 0) {
                            modificar_cliente(cliente);
                        }
                    } else {
                        printf("Cliente no encontrado.\n");
                    }
                } else {
                    printf("Opcion no valida, por favor intente de nuevo.\n");
                }
                break;
            case 4:
                listar_clientes(&v_clientes);
                break;
            case 5:
                // Solicitar el ID del cliente a modificar
                leer_unsigned("Ingrese el ID del cliente a modificar", &id_cliente);
                Cliente *cliente_modificar = buscar_cliente_por_id(&v_clientes, id_cliente);
                if (cliente_modificar != NULL) {
                    modificar_cliente(cliente_modificar);
                } else {
                    printf("Cliente no encontrado.\n");
                }
                break;
            case 6:
                printf("Volviendo...\n");
                break;
            default:
                printf("Opcion no valida, por favor intente de nuevo.\n");
        }
    } while (opcion != 6);
    guardar_clientes(&v_clientes);
}

void mostrarMenuAdministrador(AdminProv* admin) {
    int opcion;
    do {
        printf("\nMENU ADMINISTRADOR\n");
        printf("1. Perfil\n");
        printf("2. Clientes\n");
        printf("3. Proveedores\n");
        printf("4. Productos\n");
        printf("5. Categorias\n");
        printf("6. Pedidos\n");
        printf("7. Transportista\n");
        printf("8. Descuentos\n");
        printf("9. Devoluciones\n");
        printf("10. Salir del sistema\n");
        leer_entero("Seleccione una opcion", &opcion);

        switch (opcion) {
            case 1:
                perfilAdministrador(admin);
                break;
            case 2:
                gestionClientes();
                break;
            case 3:
                //gestionProveedores();
                break;
            case 4:
                //gestionProductos(); JAVI
                break;
            case 5:
                //gestionCategorias();
                break;
            case 6:
                //gestionPedidos(); JAVI
                break;
            case 7:
                //gestionTransportistas(); JAVI
                break;
            case 8:
                //gestionDescuentos(); JAVI
                break;
            case 9:
                //gestionDevoluciones();
                break;
            case 10:
                //salirDelSistema();
                break;
            default:
                printf("Opcion no valida, por favor intente de nuevo.\n");
        }
    } while (opcion != 10);
}

int main(){
    setlocale(LC_ALL, "spanish");
    AdminProv admin;
    strcpy(admin.id_empresa, "MERCAD");
    strcpy(admin.nombre, "Juan Perez");
    strcpy(admin.email, "juanitoGolondrina@gmail.com");
    strcpy(admin.contrasena, "securePassword");
    mostrarMenuAdministrador(&admin);
    return 0;
}