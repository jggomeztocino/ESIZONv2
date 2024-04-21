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

void gestionClientes() {
    VectorClientes v_clientes;
    cargar_clientes(&v_clientes);

    /* Menú con las distintas opciones de gestión de clientes */
    int opcion;
    char id_cliente[8];
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
                leer_cadena("Ingrese el ID del cliente a eliminar", id_cliente, 8);
                eliminar_cliente(&v_clientes, id_cliente);
                break;
            case 3:
                // Pregunta si se desea buscar por ID o por email
                leer_unsigned("Buscar por:\n1. ID\n2. Email", &opcion_busqueda);
                if (opcion_busqueda == 1) {
                    // Buscar por ID
                    leer_cadena("Ingrese el ID del cliente a buscar", id_cliente, 8);
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
                leer_cadena("Ingrese el ID del cliente a modificar", id_cliente, 8);
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

void gestionProveedores() {
    VectorAdminProv v_adminprov;
    cargar_adminprov(&v_adminprov);

    /* Menú con las distintas opciones de gestión de proveedores */
    int opcion;
    char id_empresa[5];
    unsigned opcion_busqueda;
    do {
        printf("\nGESTIÓN DE PROVEEDORES\n");
        printf("1. Alta de proveedor\n");
        printf("2. Baja de proveedor\n");
        printf("3. Buscar proveedor\n");
        printf("4. Listar proveedores\n");
        printf("5. Modificar proveedor\n");
        printf("6. Volver\n");
        leer_entero("Seleccione una opcion", &opcion);

        switch (opcion) {
            case 1:
                listar_adminprov(alta_proveedor(&v_adminprov));
                break;
            case 2:
                baja_proveedor(&v_adminprov);
                break;
            case 3:
                // Pregunta si se desea buscar por ID o por email
                leer_unsigned("Buscar por:\n1. ID\n2. Email", &opcion_busqueda);
                if (opcion_busqueda == 1) {
                    // Buscar por ID
                    leer_cadena("Ingrese el ID del proveedor a buscar", id_empresa, 5);
                    AdminProv *proveedor = buscar_adminprov_id(&v_adminprov, id_empresa);
                    if (proveedor != NULL) {
                        listar_adminprov(proveedor);
                        // Preguntar si se desea modificar el proveedor
                        char respuesta[2];
                        leer_cadena("Desea modificar este proveedor? (s/n)", respuesta, sizeof(respuesta));
                        if (strcmp(respuesta, "s") == 0) {
                            modificar_proveedor(&v_adminprov);
                        }
                    } else {
                        printf("Proveedor no encontrado.\n");
                    }
                } else if (opcion_busqueda == 2) {
                    // Buscar por email
                    char email[31];
                    leer_cadena("Ingrese el email del proveedor a buscar", email, 30);
                    AdminProv *proveedor = buscar_adminprov_email(&v_adminprov, email);
                    if (proveedor != NULL) {
                        listar_adminprov(proveedor);
                        // Preguntar si se desea modificar el proveedor
                        char respuesta[2];
                        leer_cadena("\n\nDesea modificar este proveedor? (S/N)", respuesta, sizeof(respuesta));
                        if ((strcmp(respuesta, "s") == 0) || (strcmp(respuesta, "S") == 0))
                        {
                            modificar_proveedor(&v_adminprov);
                        }
                    } else {
                        printf("Proveedor no encontrado.\n");
                    }
                } else {
                    printf("Opción no valida, por favor intente de nuevo.\n");
                }
                break;
            case 4:
                listar_provs(&v_adminprov);
                break;
            case 5:
                modificar_proveedor(&v_adminprov);
                break;
            case 6:
                printf("Volviendo...\n");
                break;
            default:
                printf("Opción no valida, por favor intente de nuevo.\n");
        }
    } while (opcion != 6);
    guardar_adminprov(&v_adminprov);
}


void gestionProductos()
{
    // Carga de los productos
    VectorProductos v_productos;
    cargar_productos(&v_productos);

    // Carga de las categorias
    VectorCategorias v_categorias;
    cargar_categorias(&v_categorias);

    // Carga de los administradores-proveedores
    VectorAdminProv v_adminprov;
    cargar_adminprov(&v_adminprov);

    // Variables
    unsigned opcion;
    char id_producto[8];
    char nombre_producto[16];
    unsigned opcion_busqueda;
    Producto *producto;

    do{
        printf("\nGESTION DE PRODUCTOS\n");
        printf("1. Búsqueda de producto\n");
        printf("2. Alta de producto\n");
        printf("3. Baja de producto\n");
        printf("4. Modificación de producto\n");
        printf("5. Listado de productos\n");
        printf("6. Volver\n");

        leer_unsigned("Seleccione una opción", &opcion);

        switch(opcion)
        {
            case 1:
                // Pregunta si se desea buscar por ID o por nombre
                printf("\nBÚSQUEDA DE PRODUCTO\n");
                printf("1. Buscar por ID\n");
                printf("2. Buscar por nombre\n");
                leer_unsigned("Seleccione una opción", &opcion_busqueda);
                if(opcion_busqueda == 1)
                {
                    // Buscar por ID
                    leer_cadena("Ingrese el ID del producto a buscar", id_producto, 8);
                    producto = buscar_producto_id(&v_productos, id_producto);
                    if(producto != NULL)
                    {
                        listar_producto(producto);
                        // Preguntar si se desea modificar el producto
                        char respuesta[2];
                        leer_cadena("Desea modificar este producto? (S/N)", respuesta, sizeof(respuesta));
                        if(strcmp(respuesta, "s") == 0 || strcmp(respuesta, "S") == 0)
                        {
                            printf("\nMODIFICACIÓN DE PRODUCTO\n");
                            modificar_producto(producto,&v_categorias,&v_adminprov);

                        }
                    }
                    else
                    {
                        printf("Producto no encontrado.\n");
                    }
                }
                else if(opcion_busqueda == 2)
                {
                    // Buscar por nombre
                    leer_cadena("Ingrese el nombre del producto a buscar", nombre_producto, 16);
                    if(listar_productos_nombre(&v_productos, nombre_producto) == 0)
                    {
                        printf("Producto no encontrado.\n");
                    }
                    else
                    {
                        leer_cadena("Ingrese el ID del producto a modificar", id_producto, 8);
                        producto = buscar_producto_id(&v_productos, id_producto);
                        if(producto != NULL)
                        {
                            printf("\nMODIFICACIÓN DE PRODUCTO\n");
                            modificar_producto(producto,&v_categorias,&v_adminprov);
                        }
                        else
                        {
                            printf("Producto no encontrado.\n");
                        }
                    }
                }
                else
                {
                    printf("Opción no válida, por favor intente de nuevo.\n");
                }
                break;
            case 2:
                printf("\nALTA DE PRODUCTO\n");
                listar_producto((Producto *)alta_producto(&v_productos, &v_categorias, &v_adminprov));
                break;
            case 3:
                printf("\nBAJA DE PRODUCTO\n");
                printf("1. Buscar por ID\n");
                printf("2. Buscar por nombre\n");
                leer_unsigned("Seleccione una opción", &opcion_busqueda);
                if(opcion_busqueda == 1)
                {
                    // Buscar por ID
                    leer_cadena("Ingrese el ID del producto a buscar", id_producto, 8);
                    producto = buscar_producto_id(&v_productos, id_producto);
                    if(producto != NULL)
                    {
                        listar_producto(producto);
                        // Preguntar si se desea eliminar el producto
                        char respuesta[2];
                        leer_cadena("Desea eliminar este producto? (S/N)", respuesta, sizeof(respuesta));
                        if(strcmp(respuesta, "s") == 0 || strcmp(respuesta, "S") == 0)
                        {
                            baja_producto(&v_productos, id_producto);
                        }
                    }
                    else
                    {
                        printf("Producto no encontrado.\n");
                    }
                }
                else if(opcion_busqueda == 2)
                {
                    // Buscar por nombre
                    leer_cadena("Ingrese el nombre del producto a buscar", nombre_producto, 16);
                    if(listar_productos_nombre(&v_productos, nombre_producto) == 0)
                    {
                        printf("Producto no encontrado.\n");
                    }
                    else
                    {
                        leer_cadena("Ingrese el ID del producto a eliminar", id_producto, 8);
                        producto = buscar_producto_id(&v_productos, id_producto);
                        if(producto != NULL)
                        {
                            baja_producto(&v_productos, id_producto);
                        }
                        else
                        {
                            printf("Producto no encontrado.\n");
                        }
                    }
                }
                else
                {
                    printf("Opción no válida, por favor intente de nuevo.\n");
                }
                break;
            case 4:
                printf("\nMODIFICACIÓN DE PRODUCTO\n");
                printf("1. Buscar por ID\n");
                printf("2. Buscar por nombre\n");
                leer_unsigned("Seleccione una opción", &opcion_busqueda);
                if(opcion_busqueda == 1)
                {
                    // Buscar por ID
                    leer_cadena("Ingrese el ID del producto a buscar", id_producto, 8);
                    producto = buscar_producto_id(&v_productos, id_producto);
                    if(producto != NULL)
                    {
                        listar_producto(producto);
                        // Preguntar si se desea modificar el producto
                        char respuesta[2];
                        leer_cadena("Desea modificar este producto? (S/N)", respuesta, sizeof(respuesta));
                        if(strcmp(respuesta, "s") == 0 || strcmp(respuesta, "S") == 0)
                        {
                            modificar_producto(producto, &v_categorias, &v_adminprov);
                        }
                    }
                    else
                    {
                        printf("Producto no encontrado.\n");
                    }
                }
                else if(opcion_busqueda == 2)
                {
                    // Buscar por nombre
                    leer_cadena("Ingrese el nombre del producto a buscar", nombre_producto, 16);
                    if(listar_productos_nombre(&v_productos, nombre_producto) == 0)
                    {
                        printf("Producto no encontrado.\n");
                    }
                    else
                    {
                        leer_cadena("Ingrese el ID del producto a modificar", id_producto, 8);
                        producto = buscar_producto_id(&v_productos, id_producto);
                        if(producto != NULL)
                        {
                            modificar_producto(producto, &v_categorias, &v_adminprov);
                        }
                        else
                        {
                            printf("Producto no encontrado.\n");
                        }
                    }
                }
                else
                {
                    printf("Opción no válida, por favor intente de nuevo.\n");
                }
                break;
            case 5:
                printf("\nLISTADO DE PRODUCTOS\n");
                listar_productos(&v_productos);
                break;
            case 6:
                printf("Saliendo del menú de gestión de productos...\n");
                break;
            default:
                printf("Opción no válida, por favor intente de nuevo.\n");
                break;
        }
    }while(opcion != 6);

    // Guardar los productos
    guardar_productos(&v_productos);

    // Guardar las categorias
    guardar_categorias(&v_categorias);

    // Guardar los administradores-proveedores
    guardar_adminprov(&v_adminprov);
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
                gestionProveedores();
                break;
            case 4:
                gestionProductos();
                break;
            case 5:
                //gestionCategorias();
                break;
            case 6:
                //gestionPedidos();
                break;
            case 7:
                //gestionTransportistas();
                break;
            case 8:
                //gestionDescuentos();
                break;
            case 9:
                //gestionDevoluciones();
                break;
            case 10:
                printf("Saliendo del menú de Administradores...\n");
                return;
            default:
                printf("Opción no válida, por favor inténtelo de nuevo.\n");
                break;
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

