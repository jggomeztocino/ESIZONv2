#include <stdio.h>
#include <string.h>
#include "menu_administrador.h"

// Funcion para mostrar y modificar el perfil del administrador
void perfilAdministrador(AdminProv* admin) {
    unsigned opcion;

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
        leer_unsigned("Seleccione una opcion para modificar", &opcion);

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
    unsigned opcion;
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
        leer_unsigned("Seleccione una opcion", &opcion);

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
    unsigned opcion;
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
        leer_unsigned("Seleccione una opcion", &opcion);

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

/*
 *  Categorías
    Mediante esta opción el administrador podrá acceder a la información de las categorías
    dadas de alta en la plataforma. Mediante el menú correspondiente podrá realizar altas,
    bajas, búsquedas, listados y modificaciones de categorías. Además, podrá generar listados de
    productos por categoría.

    Para ello deberá hacer uso de las funciones de gestión de categorías y productos.

    Las opciones a mostrar son:
    1. Búsqueda de categoría
    2. Alta de categoría
    3. Baja de categoría
    4. Modificación de categoría
    5. Listado de categorías
    6. Listado de productos por categoría
    7. Volver

    1. Búsqueda de categoría
    El sistema solicitará al administrador que introduzca el ID de la categoría a buscar.
    - Si la categoría existe, se mostrará la información de la categoría y se preguntará si se desea modificar.
    - Si la categoría no existe, se mostrará un mensaje indicando que la categoría no existe.

    2. Alta de categoría
    - El ID será generado automáticamente por el sistema. Para ello, se deberá buscar el último ID existente en el vector,
    transformarlo a entero, incrementarlo en 1 y convertirlo de nuevo a cadena de caracteres.
    - El sistema solicitará al administrador que introduzca la descripción de la categoría. Si la descripción ya existe,

    3. Baja de categoría
    El sistema solicitará al administrador que introduzca el ID de la categoría a eliminar.
    - Si la categoría existe, se mostrará la información de la categoría y se pedirá confirmación para eliminarla.
    o Además, se eliminarán todos los productos asociados a dicha categoría.
    - Si la categoría no existe, se mostrará un mensaje indicando que la categoría no existe y se indicará la posibilidad de listar las categorías.

    4. Modificación de categoría
    El sistema solicitará al administrador que introduzca el ID de la categoría a modificar.
    - Si la categoría existe, se mostrará la información de la categoría y se permitirá modificar la descripción.
    - Si la categoría no existe, se mostrará un mensaje indicando que la categoría no existe y se indicará la posibilidad de listar las categorías.

   5. Listado de categorías
    Se mostrará un listado con la información de todas las categorías dadas de alta en el sistema.

    6. Listado de productos por categoría
    El sistema solicitará al administrador que introduzca el ID de la categoría a buscar.
    - Si la categoría existe, se mostrará un listado con la información de todos los productos pertenecientes a dicha categoría.
    - Si la categoría no existe, se mostrará un mensaje indicando que la categoría no existe y se indicará la posibilidad de listar las categorías.

    7. Volver
    Volverá al menú principal de administrador.
 */

void gestionCategorias()
{
    // Carga de las categorias
    VectorCategorias v_categorias;
    cargar_categorias(&v_categorias);

    // Carga de los productos
    VectorProductos v_productos;
    cargar_productos(&v_productos);

    unsigned opcion = 0;
    char id_categoria[5];
    char respuesta[2];
    unsigned dependencias;
    do{
        printf("\nGESTIÓN DE CATEGORÍAS\n");
        printf("1. Búsqueda de categoría\n");
        printf("2. Alta de categoría\n");
        printf("3. Baja de categoría\n");
        printf("4. Modificación de categoría\n");
        printf("5. Listado de categorías\n");
        printf("6. Listado de productos por categoría\n");
        printf("7. Volver\n");
        leer_unsigned("Seleccione una opción", &opcion);

        switch (opcion) {
            case 1:
                printf("\nBÚSQUEDA DE CATEGORÍA\n");
                leer_cadena("Ingrese el ID de la categoría a buscar", id_categoria, 5);
                Categoria *categoria = buscar_categoria_id(&v_categorias, id_categoria);
                if (categoria != NULL) {
                    listar_categoria(categoria);
                    leer_cadena("Desea modificar esta categoría? (s/n)", respuesta, sizeof(respuesta));
                    if ((strcmp(respuesta, "s") == 0)||(strcmp(respuesta, "S") == 0)) {
                        listar_categoria(modificar_categoria(categoria));
                    }
                } else {
                    printf("Categoría no encontrada.\n");
                }
                break;
            case 2:
                printf("\nALTA DE CATEGORÍA\n");
                alta_categoria(&v_categorias);
                break;
            case 3:
                printf("\nBAJA DE CATEGORÍA\n");
                leer_cadena("Ingrese el ID de la categoría a eliminar", id_categoria, 5);
                printf("Analizando dependencias de productos...\n");
                dependencias = listar_productos_categoria(&v_productos, id_categoria);
                if(dependencias == 0) {
                    printf("No hay productos asociados a esta categoría.\n");
                } else {
                    printf("Estos productos serán eliminados si continúa con la baja de la categoría.\n");
                }
                leer_cadena("Desea continuar con la baja de la categoría? (S/N)", respuesta, sizeof(respuesta));
                if ((strcmp(respuesta, "s") == 0)||(strcmp(respuesta, "S") == 0)) {
                    if(dependencias > 0) {
                        eliminar_productos_categoria(&v_productos, id_categoria);
                    }
                    baja_categoria(&v_categorias, id_categoria);
                }
                break;
            case 4:
                printf("\nMODIFICACIÓN DE CATEGORÍA\n");
                leer_cadena("Ingrese el ID de la categoría a modificar", id_categoria, 5);
                Categoria *categoria_modificar = buscar_categoria_id(&v_categorias, id_categoria);
                if (categoria_modificar != NULL) {
                    listar_categoria(modificar_categoria(categoria_modificar));
                } else {
                    printf("Categoría no encontrada.\n");
                }
                break;
            case 5:
                printf("\nLISTADO DE CATEGORÍAS\n");
                listar_categorias(&v_categorias);
                break;
            case 6:
                printf("\nLISTADO DE PRODUCTOS POR CATEGORÍA\n");
                leer_cadena("Ingrese el ID de la categoría de la que listar los productos", id_categoria, 5);
                if (listar_productos_categoria(&v_productos, id_categoria) == 0) {
                    printf("Categoría no encontrada.\n");
                }
                break;
            case 7:
                printf("Volviendo al menú principal...\n");
                break;
            default:
                printf("Opción no válida, por favor intente de nuevo.\n");
                break;
        }
    }while(opcion != 7);

    guardar_categorias(&v_categorias);
    guardar_productos(&v_productos);
}

/*
 *  f ) Pedidos
    Mediante esta opción el administrador podrá acceder a la información de los pedidos dados de
    alta en la plataforma.
    • Mediante el menú correspondiente podrá realizar altas, bajas, búsquedas, listados y
    modificaciones de pedidos.
    • En los listados habrá que contemplar la posibilidad de listarlos según su estado. Esto es
    necesario para poder localizar rápidamente los pedidos cuya fecha de entrega sea próxima
    y que, por tanto, deben ser procesados con mayor prioridad.
    • Otras opciones permitidas será la asignación de transportistas a los productos pedidos en
    función de la dirección del cliente y ciudad de reparto.
    • Así como llevar a cabo la asignación de lockers a los pedidos en base a la localidad de
    entrega y ubicación del locker.

    Para ello deberá hacer uso de las funciones de pedidos, lockers y transportistas.

    Las opciones a mostrar son:
    1. Búsqueda de pedido
    2. Alta de pedido
    3. Baja de pedido
    4. Modificación de pedido
    5. Listado de pedidos
    6. Listado de pedidos por estado (ordenados por fecha de entrega)
    7. Volver

    Para listar un pedido, se mostrará la información del pedido, junto a todos los productos que pertenecen a dicho pedido.

    1. Búsqueda de pedido
    a. El sistema solicitará al administrador que introduzca el ID del pedido a buscar.
    b. Si el pedido existe, se lista el pedido y se preguntará si se desea modificar.
    c. Si el pedido no existe, se mostrará un mensaje indicando que el pedido no existe.

    2. Alta de pedido
    a. El ID será generado automáticamente por el sistema. Para ello, se deberá buscar el último ID existente en el vector, transformarlo a entero, incrementarlo en 1 y convertirlo de nuevo a cadena de caracteres.
    b. Se registra la fecha del sistema como fecha de pedido.
    c. El sistema solicitará al administrador que introduzca el ID del cliente que realiza el pedido.
    d. El sistema comprueba si el cliente existe. Si no existe, se mostrará un mensaje indicando que el cliente no existe y se dará la opción de dar de alta al cliente.
    e. El sistema solicitará al administrador que introduzca el lugar de entrega del pedido (1: domicilio, 2: locker).
    f. Si el lugar de entrega es un locker, se solicitará al administrador que introduzca el ID del locker.
    g. El sistema comprobará si el locker existe. Si no existe, se informará del error y dará la opción de listar según la localidad.
    h. El sistema preguntará si se desea aplicar un descuento al pedido. Si la respuesta es afirmativa, se solicitará el ID del descuento.
    i. El sistema comprueba si el descuento existe. Si no existe, se mostrará un mensaje indicando que el descuento no existe, dando la posibilidad a introducir de nuevo otro código.
    j. El sistema preguntará preguntará indefinidamente si se desea añadir productos al pedido, hasta que el usuario indique lo contrario.
        Para cada producto:
        1. Se solicitará el ID del producto.
        2. Se solicitará el número de unidades.
        3. Se solicitará la fecha prevista de entrega (por defecto, la fecha de entrega será 1 semana después de la fecha de pedido).
        4. Se especificará el importe total del producto en el pedido, consultando su valor en el vector de productos correspondiente.
        5. Automáticamente, se asignará el estado del producto en el pedido como «enPreparación».
        6. Se solicitará el ID del transportista asignado al producto.
        7. El sistema comprobará si el transportista existe. Si no existe, se mostrará un mensaje indicando que el transportista no existe y dara la opción de listar los transportistas.
        8. Si el lugar de entrega es un locker, se asigna el mismo ID de locker especificado para el pedido.

    3. Baja de pedido
    a. El sistema solicitará al administrador que introduzca el ID del pedido a eliminar.
    b. Si el pedido existe, se mostrará la información del pedido y se pedirá confirmación para eliminarlo.
    c. Si el pedido no existe, se mostrará un mensaje indicando que el pedido no existe.

    4. Modificación de pedido
    a. El sistema solicitará al administrador que introduzca el ID del pedido a modificar.
    b. Si el pedido existe, se mostrará la información del pedido y se permitirá modificar la información del pedido (siguiendo la misma metodología que el alta).
    c. Si el pedido no existe, se mostrará un mensaje indicando que el pedido no existe.

    5. Listado de pedidos
    a. Se mostrará un listado con la información de todos los pedidos dados de alta en el sistema, junto a la información de los productos que pertenecen a cada pedido.

    6. Listado de pedidos por estado
    a. Se mostrará un listado con la información de todos los pedidos dados de alta en el sistema, ordenados por fecha de entrega ascendentemente (fecha más próxima primero) y estado (enPreparación primero).

    7. Volver
    a. Volverá al menú principal de administrador.
 */

void gestionPedidos()
{
    // Carga de los pedidos
    VectorPedidos v_pedidos;
    cargar_pedidos(&v_pedidos);

    // Carga de los productos
    VectorProductos v_productos;
    cargar_productos(&v_productos);

    // Carga de los productos pedidos
    VectorProductosPedido v_productos_pedidos;
    cargar_productos_pedido(&v_productos_pedidos);

    // Carga de los transportistas
    VectorTransportistas v_transportistas;
    cargar_transportistas(&v_transportistas);

    // Carga de los clientes
    VectorClientes v_clientes;
    cargar_clientes(&v_clientes);

    // Carga de los lockers
    VectorLockers v_lockers;
    cargar_lockers(&v_lockers);

    // Carga de los descuentos
    VectorDescuentos v_descuentos;
    cargar_descuentos(&v_descuentos);

    // Carga los descuentos de los clientes
    VectorDescuentosClientes v_descuentos_cliente;
    cargar_descuentos_clientes(&v_descuentos_cliente);

    unsigned opcion = 0;
    unsigned opcion_busqueda = 0;
    char id_pedido[8];
    char id_cliente[8];
    char id_producto[8];
    char respuesta;

    Pedido* pedido;
    ProductoPedido *producto_pedido;
    Cliente* cliente;

    do{
        printf("\nGESTIÓN DE PEDIDOS\n");
        printf("1. Búsqueda de pedido\n");
        printf("2. Alta de pedido\n");
        printf("3. Baja de pedido\n");
        printf("4. Modificación de pedido\n");
        printf("5. Listado de pedidos\n");
        printf("6. Listado de pedidos por estado\n");
        printf("7. Volver\n");
        leer_unsigned("Seleccione una opción", &opcion);

        switch (opcion) {
            case 1:
                printf("\nBÚSQUEDA DE PEDIDO\n");
                printf("1. Buscar por ID\n");
                printf("2. Buscar por ID de cliente\n");
                leer_unsigned("Seleccione una opción", &opcion_busqueda);
                if(opcion_busqueda ==1)
                {
                    leer_cadena("Ingrese el ID del pedido a buscar", id_pedido, 8);
                    pedido = buscar_pedido_por_id(&v_pedidos, id_pedido);
                }
                else if(opcion_busqueda == 2)
                {
                    leer_cadena("Ingrese el ID del cliente a buscar", id_cliente, 8);
                    if(buscar_cliente_por_id(&v_clientes, id_cliente) == NULL)
                    {
                        printf("Cliente no encontrado.\n");
                        break;
                    }
                    if(listar_pedidos_cliente(&v_pedidos, id_cliente) == 0)
                    {
                        printf("El cliente no tiene pedidos asociados.\n");
                    }else{
                        leer_cadena("Seleccione el ID del pedido a listar individualmente (de los listados por pantalla)", id_pedido, 8);
                        pedido = buscar_pedido_por_id(&v_pedidos, id_pedido);
                    }
                }
                else
                {
                    printf("Opción no válida.\n");
                    break;
                }
                if (pedido != NULL) {
                    strcpy(id_pedido, pedido->id_pedido);
                    printf("Pedido encontrado\n");
                    listar_pedido(pedido);
                    listar_productos_pedido(&v_productos_pedidos, id_pedido);
                    leer_caracter("Desea modificar este pedido? (S/N)", &respuesta);
                    if (respuesta == 'S' || respuesta == 's') {
                        modificar_pedido(pedido, &v_productos_pedidos, &v_clientes, &v_lockers);
                        printf("Mostrando los productos del pedido...\n");
                        listar_productos_pedido(&v_productos_pedidos, id_pedido);
                        printf("¿Desea modificar algún producto del pedido? (S/N)\n");
                        leer_caracter("Seleccione una opción", &respuesta);
                        if(respuesta == 'S' || respuesta == 's')
                        {
                            while(respuesta != 'N' && respuesta != 'n')
                            {
                                listar_productos_pedido(&v_productos_pedidos, id_pedido);
                                leer_cadena("Ingrese el ID del producto a modificar", id_producto, 8);
                                producto_pedido = buscar_producto_pedido(&v_productos_pedidos, id_pedido, id_producto);
                                if(producto_pedido != NULL)
                                {
                                    printf("Por cuestiones de integridad, solo se permite dar de baja un producto de un producto no enviado o iniciar una devolución de un producto entregado.\n");
                                    printf("¿Qué desea hacer con el producto?\n");
                                    printf("1. Eliminar el producto\n");
                                    printf("2. Iniciar devolución\n");
                                    leer_unsigned("Seleccione una opción", &opcion);
                                    if(opcion == 1)
                                    {
                                        eliminar_producto_pedido(id_pedido, id_producto, &v_productos_pedidos);
                                    }
                                    else if(opcion == 2) {
                                        iniciar_devolucion(id_pedido, id_producto, &v_productos_pedidos);
                                    }
                                }
                                else
                                {
                                    printf("Producto no encontrado.\n");
                                }
                                leer_caracter("¿Desea modificar otro producto del pedido? (S/N)", &respuesta);
                            }
                        }
                    }
                } else {
                    printf("Pedido no encontrado.\n");
                }
                break;
            case 2:
                printf("\nALTA DE PEDIDO\n");
                leer_cadena("Ingrese el ID del cliente que realiza el pedido", id_cliente, 8);
                cliente = buscar_cliente_por_id(&v_clientes, id_cliente);
                if(cliente == NULL)
                {
                    printf("Cliente no encontrado.\n");
                    break;
                }
                realizar_pedido(cliente, &v_pedidos, &v_productos_pedidos, &v_lockers, &v_descuentos, &v_descuentos_cliente, &v_productos);
                break;
            case 3:
                printf("\nBAJA DE PEDIDO\n");
                leer_cadena("Ingrese el ID del pedido a eliminar", id_pedido, 8);
                pedido = buscar_pedido_por_id(&v_pedidos, id_pedido);
                if(pedido != NULL)
                {
                    listar_pedido(pedido);
                    leer_caracter("Desea eliminar este pedido? (S/N)", &respuesta);
                    if(respuesta == 'S' || respuesta == 's')
                    {
                        eliminar_pedido(id_pedido, &v_pedidos, &v_productos_pedidos);
                    }
                }
                else
                {
                    printf("Pedido no encontrado.\n");
                }
                break;
            case 4:
                printf("\nMODIFICACIÓN DE PEDIDO\n");
                leer_cadena("Ingrese el ID del pedido a modificar", id_pedido, 8);
                pedido = buscar_pedido_por_id(&v_pedidos, id_pedido);
                if(pedido != NULL)
                {
                    listar_pedido(pedido);
                    modificar_pedido(pedido, &v_productos_pedidos, &v_clientes, &v_lockers);
                }
                else
                {
                    printf("Pedido no encontrado.\n");
                }
                break;
            case 5:
                printf("\nLISTADO DE PEDIDOS\n");
                listar_pedidos(&v_pedidos);
                break;
            case 6:
                printf("\nLISTADO DE PEDIDOS POR ESTADO\n");
                listar_todos_productos_pedidos(&v_productos_pedidos);
                break;
            case 7:
                printf("Volviendo al menú principal...\n");
                break;
            default:
                printf("Opción no válida, por favor intente de nuevo.\n");
                break;
        }

    } while (opcion != 7);

    guardar_pedidos(&v_pedidos);
    guardar_productos(&v_productos);
    guardar_productos_pedido(&v_productos_pedidos);
    guardar_transportistas(&v_transportistas);
    guardar_clientes(&v_clientes);
    guardar_lockers(&v_lockers);
    guardar_descuentos(&v_descuentos);
    guardar_descuentos_clientes(&v_descuentos_cliente);
}

/*
 *  g) Transportistas
    Mediante esta opción el administrador podrá acceder a la información de todos los
    transportistas dados de alta en la plataforma. Mediante el menú correspondiente podrá realizar
    altas, bajas, búsquedas, listados y modificaciones de transportistas.

    Para ello deberá hacer uso de las funciones de gestión de transportistas.

    Las opciones a mostrar son:
    1. Búsqueda de transportista
    2. Alta de transportista
    3. Baja de transportista
    4. Modificación de transportista
    5. Listado de transportistas
    6. Lista de transportistas por ciudad
    7. Volver

    1. Búsqueda de transportista
    a. El sistema solicitará al administrador que introduzca el ID del transportista a buscar.
    b. Si el transportista existe, se mostrará la información del transportista y se preguntará si se desea modificar.
    c. Si el transportista no existe, se mostrará un mensaje indicando que el transportista no existe.

    2. Alta de transportista
    a. El ID será generado automáticamente por el sistema. Para ello, se deberá buscar el último ID existente en el vector, transformarlo a entero, incrementarlo en 1 y convertirlo de nuevo a cadena de caracteres.
    b. El sistema solicitará al administrador que introduzca el nombre del transportista.
    c. El sistema solicitará al administrador que introduzca el email del transportista.
    d. El sistema solicitará al administrador que introduzca la contraseña del transportista.
    e. El sistema solicitará al administrador que introduzca el nombre de la empresa de transporte.
    f. El sistema solicitará al administrador que introduzca la ciudad de operación.

    3. Baja de transportista
    a. El sistema solicitará al administrador que introduzca el ID del transportista a eliminar.
    b. Si el transportista existe, se mostrará la información del transportista y se pedirá confirmación para eliminarlo.
    c. Si existen pedidos asociados al transportista y alguno de ellos está en estado <<enviado>> o <<transportista>> se mostrará un mensaje indicando que no se puede eliminar el transportista.
    d. Si el transportista no existe, se mostrará un mensaje indicando que el transportista no existe.

    4. Modificación de transportista
    a. El sistema solicitará al administrador que introduzca el ID del transportista a modificar.
    b. Si el transportista existe, se mostrará la información del transportista y se permitirá modificar la información del transportista.
    c. Si el transportista no existe, se mostrará un mensaje indicando que el transportista no existe.

    5. Listado de transportistas
    a. Se mostrará un listado con la información de todos los transportistas dados de alta en el sistema.

    6. Lista de transportistas por ciudad
    a. Se mostrará un listado con la información de todos los transportistas que operan en una ciudad dada.

    7. Volver
    a. Volverá al menú principal de administrador.
 */
void gestionTransportistas()
{
    // Carga de los transportistas
    VectorTransportistas v_transportistas;
    cargar_transportistas(&v_transportistas);

    // Carga de los productos pedidos
    VectorProductosPedido v_productospedidos;
    cargar_productos_pedido(&v_productospedidos);

    unsigned opcion = 0;
    unsigned opcion_busqueda = 0;
    char id_transportista[5];
    char email_transportista[31];
    char ciudad[16];
    char respuesta[2];
    Transportista* transportista;

    do{
        printf("\nGESTIÓN DE TRANSPORTISTAS\n");
        printf("1. Búsqueda de transportista\n");
        printf("2. Alta de transportista\n");
        printf("3. Baja de transportista\n");
        printf("4. Modificación de transportista\n");
        printf("5. Listado de transportistas\n");
        printf("6. Lista de transportistas por ciudad\n");
        printf("7. Volver\n");

        leer_unsigned("Seleccione una opción", &opcion);

        switch (opcion) {
            case 1:
                printf("\nBÚSQUEDA DE TRANSPORTISTA\n");
                printf("1. Buscar por ID\n");
                printf("2. Buscar por email\n");
                leer_unsigned("Seleccione una opción", &opcion_busqueda);
                if(opcion_busqueda ==1)
                {
                    leer_cadena("Ingrese el ID del transportista a buscar", id_transportista, 5);
                    transportista = buscar_transportista_id(&v_transportistas, id_transportista);
                }
                else if(opcion_busqueda == 2)
                {
                    leer_cadena("Ingrese el email del transportista a buscar", email_transportista, 31);
                    transportista = buscar_transportista_email(&v_transportistas, email_transportista);
                }
                else
                {
                    printf("Opción no válida.\n");
                    break;
                }
                if (transportista != NULL) {
                    printf("Transportista encontrado:\n");
                    listar_transportista(transportista);
                    leer_cadena("Desea modificar este transportista? (S/N)", respuesta, sizeof(respuesta));
                    if ((strcmp(respuesta, "s") == 0) || (strcmp(respuesta, "S") == 0)) {
                        listar_transportista(modificar_transportista(transportista));
                    }
                } else {
                    printf("Transportista no encontrado.\n");
                }
                break;
            case 2:
                printf("\nALTA DE TRANSPORTISTA\n");
                alta_transportista(&v_transportistas);
                break;
            case 3:
                printf("\nBAJA DE TRANSPORTISTA\n");
                // Solicitar el ID o email del transportista a eliminar
                printf("1. Buscar por ID\n");
                printf("2. Buscar por email\n");
                leer_unsigned("Seleccione una opción", &opcion_busqueda);
                if(opcion_busqueda == 1)
                {
                    leer_cadena("Ingrese el ID del transportista a eliminar", id_transportista, 5);
                    transportista = buscar_transportista_id(&v_transportistas, id_transportista);
                }
                else if(opcion_busqueda == 2)
                {
                    leer_cadena("Ingrese el email del transportista a eliminar", email_transportista, 31);
                    transportista = buscar_transportista_email(&v_transportistas, email_transportista);
                }
                else
                {
                    printf("Opción no válida.\n");
                    break;
                }
                if (transportista != NULL) {
                    printf("Transportista encontrado:\n");
                    listar_transportista(transportista);
                    printf("Analizando dependencias de pedidos...\n");
                    if (listar_productos_transportista(&v_productospedidos, id_transportista) == 0) {
                        baja_transportista(&v_transportistas, id_transportista);
                    } else {
                        printf("El transportista tiene los anteriores pedidos asignados, por lo que no puede eliminarse.\n");
                    }
                }
                break;
            case 4:
                printf("\nMODIFICACIÓN DE TRANSPORTISTA\n");
                leer_cadena("Ingrese el ID del transportista a modificar", id_transportista, 5);
                Transportista *transportista_modificar = buscar_transportista_id(&v_transportistas, id_transportista);
                if (transportista_modificar != NULL) {
                    printf("Transportista encontrado:\n");
                    listar_transportista(modificar_transportista(transportista_modificar));
                } else {
                    printf("Transportista no encontrado.\n");
                }
                break;
            case 5:
                printf("\nLISTADO DE TRANSPORTISTAS\n");
                listar_transportistas(&v_transportistas);
                break;
            case 6:
                printf("\nLISTA DE TRANSPORTISTAS POR CIUDAD\n");
                leer_cadena("Ingrese la ciudad de la que listar los transportistas", ciudad, 16);
                listar_transportistas_ciudad(&v_transportistas, ciudad);
                break;
            case 7:
                printf("Volviendo al menú principal...\n");
                break;
            default:
                printf("Opción no válida, por favor intente de nuevo.\n");
                break;
        }
    }while(opcion != 7);

    // Guardar los transportistas
    guardar_transportistas(&v_transportistas);

    // Guardar los productos pedidos
    guardar_productos_pedido(&v_productospedidos);
}

/*
 * h) Descuentos
    Mediante esta opción el administrador podrá acceder a la información de todos los códigos
    promocionales y/o cheques regalo dados de alta en la plataforma.
    • Mediante el menú correspondiente podrá realizar altas, bajas, búsquedas, listados y
    modificaciones de estos descuentos.
    • Además también podrá generar los listados de clientes que tienen asignado algún cheque
    regalo/código promocional, así como los listados de clientes que han hecho uso de algún
    cheque regalo/código promocional.
    • Por supuesto podrá asignar a un cliente determinado un cheque regalo.
    • En el caso de la creación de un nuevo código promocional, éste deberá ser asignado a todos
    los clientes.

    Para ello deberá hacer uso de las funciones de gestión de descuentos.

    Las opciones a mostrar son:
    1. Búsqueda de descuento
    2. Alta de descuento
    3. Baja de descuento
    4. Modificación de descuento
    5. Listado de descuentos
    6. Listado de clientes con descuentos
    7. Listado de clientes que han usado descuentos
    8. Asignar descuento a cliente
    9. Volver

    1. Búsqueda de descuento
    a. El sistema solicitará al administrador que introduzca el ID del descuento a buscar.
    b. Si el descuento existe, se mostrará la información del descuento y se preguntará si se desea modificar.
    c. Si el descuento no existe, se mostrará un mensaje indicando que el descuento no existe.

    2. Alta de descuento
    a. En este caso, el ID es el propio código del descuento, por lo que el sistema solicitará al administrador que introduzca el ID.
    b. El sistema solicitará al administrador que introduzca la descripción del descuento.
    c. El sistema solicitará al administrador que introduzca el tipo de descuento (promocional [codpro] o cheque regalo [cheqreg]).
    d. El sistema solicitará al administrador que indique el estado del descuento (activo o inactivo).
    e. El sistema solicitará al administrador que introduzca el importe del descuento.
    f. El sistema solicitará al administrador que introduzca aplicable a todos los clientes (S/N) (Sí: Todos, No: ESIZON).
    Nota: En el caso de que el descuento sea un código promocional y esté indicado para todos, se asignará a todos los clientes.

    3. Baja de descuento
    a. El sistema solicitará al administrador que introduzca el ID del descuento a eliminar.
    b. Si el descuento existe, se mostrará la información del descuento y se pedirá confirmación para eliminarlo.
    c. Si existen clientes asociados al descuento, se eliminará la asociación.

    4. Modificación de descuento
    a. El sistema solicitará al administrador que introduzca el ID del descuento a modificar.
    b. Si el descuento existe, se mostrará la información del descuento y se permitirá modificar la información del descuento.
    c. Si el descuento no existe, se mostrará un mensaje indicando que el descuento no existe.

    5. Listado de descuentos
    a. Se mostrará un listado con la información de todos los descuentos dados de alta en el sistema.

    6. Listado de clientes con descuentos
    a. Se mostrará un listado con la información de todos los clientes que tienen asignado algún descuento.

    7. Listado de clientes que han usado descuentos
    a. Se mostrará un listado con la información de todos los clientes que han hecho uso de algún descuento.

    8. Asignar descuento a cliente
    a. El sistema solicitará al administrador que introduzca el ID del cliente al que asignar el descuento.
    b. El sistema solicitará al administrador que introduzca el ID del descuento a asignar.
    c. El sistema comprobará si el descuento existe. Si no existe, se mostrará un mensaje indicando que el descuento no existe.
    d. El sistema comprobará si el cliente existe. Si no existe, se mostrará un mensaje indicando que el cliente no existe.

    9. Volver
    a. Volverá al menú principal de administrador.
 */

void gestionDescuentos()
{
    unsigned opcion = 0;
    char respuesta;
    unsigned opcion_busqueda = 0;

    // Carga de los descuentos
    VectorDescuentos v_descuentos;
    cargar_descuentos(&v_descuentos);

    // Carga de los descuentos de los clientes
    VectorDescuentosClientes v_descuentos_cliente;
    cargar_descuentos_clientes(&v_descuentos_cliente);

    // Carga de los clientes
    VectorClientes v_clientes;
    cargar_clientes(&v_clientes);

    char id_descuento[5];
    char id_cliente[8];

    Descuento* descuento;
    Cliente* cliente;

    do{
        printf("\nGESTIÓN DE DESCUENTOS\n");
        printf("1. Búsqueda de descuento\n");
        printf("2. Alta de descuento\n");
        printf("3. Baja de descuento\n");
        printf("4. Modificación de descuento\n");
        printf("5. Listado de descuentos\n");
        printf("6. Listado de clientes con descuentos\n");
        printf("7. Listado de clientes que han usado descuentos\n");
        printf("8. Asignar descuento a cliente\n");
        printf("9. Volver\n");
        leer_unsigned("Seleccione una opción", &opcion);

        switch (opcion) {
            case 1:
                printf("\nBÚSQUEDA DE DESCUENTO\n");

                leer_cadena("Ingrese el ID del descuento a buscar", id_descuento, 5);
                descuento = buscar_descuento_id(&v_descuentos, id_descuento);
                if(descuento == NULL)
                {
                    printf("Descuento no encontrado.\n");
                }
                else{
                    listar_descuento(descuento);

                    printf("\nOpciones:\n");
                    printf("1. Modificar descuento\n");
                    printf("2. Listar los clientes con el descuento asignado.\n");
                    printf("3. Volver\n");
                    leer_unsigned("Seleccione una opción", &opcion_busqueda);

                    switch(opcion_busqueda)
                    {
                        case 1:
                            modificar_descuento(descuento);
                            break;
                        case 2:
                            listar_clientes_descuento(&v_clientes, &v_descuentos_cliente, id_descuento);
                            break;
                        case 3:
                            printf("Volviendo al menú principal...\n");
                            break;
                        default:
                            printf("Opción no válida.\n");
                            break;
                    }
                }
                break;
            case 2:
                printf("\nALTA DE DESCUENTO\n");
                alta_descuento(&v_descuentos, &v_descuentos_cliente, &v_clientes);
                break;
            case 3:
                printf("\nBAJA DE DESCUENTO\n");
                leer_cadena("Ingrese el ID del descuento a eliminar", id_descuento, 5);
                descuento = buscar_descuento_id(&v_descuentos, id_descuento);
                if(descuento != NULL)
                {
                    listar_descuento(descuento);
                    printf("¿Desea eliminar el descuento? (Todos los clientes que tuvieran asociado dicho descuento, lo perderán) [S/N]\n");
                    leer_caracter("Seleccione una opción", &respuesta);
                    if(respuesta == 'S' || respuesta == 's')
                    {
                        baja_descuento(id_descuento, &v_descuentos, &v_descuentos_cliente);
                    }
                }
                else
                {
                    printf("Descuento no encontrado.\n");
                }
                break;
            case 4:
                printf("\nMODIFICACIÓN DE DESCUENTO\n");
                leer_cadena("Ingrese el ID del descuento a modificar", id_descuento, 5);
                descuento = buscar_descuento_id(&v_descuentos, id_descuento);
                if(descuento != NULL)
                {
                    listar_descuento(modificar_descuento(descuento));
                }
                else
                {
                    printf("Descuento no encontrado.\n");
                }
                break;
            case 5:
                printf("\nLISTADO DE DESCUENTOS\n");
                listar_descuentos(&v_descuentos);
                break;
            case 6:
                printf("\nLISTADO DE CLIENTES CON DESCUENTOS\n");
                leer_cadena("Ingrese el ID del descuento a listar los clientes", id_descuento, 5);
                listar_clientes_descuento(&v_clientes, &v_descuentos_cliente, id_descuento);
                break;
            case 7:
                printf("\nLISTADO DE CLIENTES QUE HAN USADO DESCUENTOS\n");
                listar_clientes_descuento_usado(&v_clientes, &v_descuentos_cliente, id_descuento);
                break;
            case 8:
                printf("\nASIGNAR DESCUENTO A CLIENTE\n");
                leer_cadena("Ingrese el ID del descuento a asignar", id_descuento, 5);
                descuento = buscar_descuento_id(&v_descuentos, id_descuento);
                if(descuento == NULL)
                {
                    printf("Descuento no encontrado.\n");
                    break;
                }
                leer_cadena("Ingrese el ID del cliente al que asignar el descuento", id_cliente, 8);
                cliente = buscar_cliente_por_id(&v_clientes, id_cliente);
                if(cliente == NULL)
                {
                    printf("Cliente no encontrado.\n");
                    break;
                }
                asignar_descuento_cliente(id_descuento, id_cliente, &v_descuentos_cliente);
                break;
            case 9:
                printf("Volviendo al menú principal...\n");
                break;
            default:
                printf("Opción no válida, por favor intente de nuevo.\n");
                break;
        }
    }while(opcion != 9);
}

/*
 * i)   Devoluciones
        Mediante esta opción el administrador podrá acceder a la información de todas las
        devoluciones de productos.
        • Mediante el menú correspondiente podrá realizar altas de devoluciones (aunque lo
        habitual es que sean generadas por los clientes se permite esta opción por si el
        cliente tuviera algún problema y no pudiera realizarla), bajas, búsquedas, listados y
        modificaciones de devoluciones.
        • Entre las modificaciones de los pedidos el administrador tendrá la posibilidad de consultar
        todos las devoluciones, solicitadas por un cliente, que se encuentran pendientes de
        aceptación, así como modificar el estado de éstas para aceptarlas o no. Si la devolución es
        aceptada se debe actualizar la fecha de aceptación y la fecha de caducidad de la devolución.
        • También se permitirá modificar el estado a «recibido» en el momento que reciba el
        producto. Hay que tener en cuenta que en este último caso se debe actualizar el stock
        del producto recibido.

        Para ello deberá hacer uso de las funciones de gestión de devoluciones.

        Las opciones a mostrar son:
        1. Búsqueda de devolución
        2. Alta de devolución
        3. Baja de devolución
        4. Modificación de devolución
        5. Listado de devoluciones
        6. Listado de devoluciones por cliente
        7. Volver

        1. Búsqueda de devolución
        a. El sistema solicitará al administrador que introduzca el ID de la devolución a buscar.
        b. Si la devolución existe, se mostrará la información de la devolución y se preguntará si se desea modificar.
        c. Si la devolución no existe, se mostrará un mensaje indicando que la devolución no existe.

        2. Alta de devolución
        a. El ID será generado automáticamente por el sistema. Para ello, se deberá buscar el último ID existente en el vector, transformarlo a entero, incrementarlo en 1 y convertirlo de nuevo a cadena de caracteres.
        b. El sistema solicitará al administrador que introduzca el ID del pedido al que pertenece la devolución.
        c. El sistema solicitará al administrador que introduzca el ID del producto a devolver.
        d. El sistema solicitará al administrador que introduzca el motivo de la devolución.

        3. Baja de devolución
        a. El sistema solicitará al administrador que introduzca el ID de la devolución a eliminar.
        b. Si la devolución existe, se mostrará la información de la devolución y se pedirá confirmación para eliminarla.
        c. Si la devolución no existe, se mostrará un mensaje indicando que la devolución no existe.

        4. Modificación de devolución
        a. Solo se podrá modificar el estado de la devolución.

        5. Listado de devoluciones
        a. Se mostrará un listado con la información de todas las devoluciones dadas de alta en el sistema.

        6. Listado de devoluciones por cliente
        a. Se mostrará un listado con la información de todas las devoluciones de un cliente dado.

        7. Volver
 */

void gestionDevoluciones()
{
    // Carga de las devoluciones
    VectorDevoluciones v_devoluciones;
    cargar_devoluciones(&v_devoluciones);

    // Carga de los productos pedidos
    VectorProductosPedido v_productospedidos;
    cargar_productos_pedido(&v_productospedidos);

    // Carga de los clientes
    VectorClientes v_clientes;
    cargar_clientes(&v_clientes);


    unsigned opcion = 0;
    char id_pedido[8];
    char id_producto[8];
    char id_cliente[8];
    char respuesta;
    Fecha fecha_actual;

    Devolucion* devolucion;
    ProductoPedido* producto_pedido;

    do{
        printf("\nGESTIÓN DE DEVOLUCIONES\n");
        printf("1. Búsqueda de devolución\n");
        printf("2. Alta de devolución\n");
        printf("3. Baja de devolución\n");
        printf("4. Modificación de devolución\n");
        printf("5. Listado de devoluciones\n");
        printf("6. Listado de devoluciones por cliente\n");
        printf("7. Volver\n");
        leer_unsigned("Seleccione una opción", &opcion);

        switch(opcion)
        {
            case 1:
                printf("\nBÚSQUEDA DE DEVOLUCIÓN\n");
                leer_cadena("Ingrese el ID de la devolución a buscar", id_pedido, 8);
                leer_cadena("Ingrese el ID del producto a buscar", id_producto, 8);
                devolucion = buscar_devolucion(id_pedido, id_producto, &v_devoluciones);
                if(devolucion != NULL)
                {
                    printf("Devolución encontrada\n");
                    listar_devolucion(devolucion);
                    leer_caracter("Desea modificar esta devolución? (S/N)", &respuesta);
                    if(respuesta == 'S' || respuesta == 's')
                    {
                        modificar_devolucion(devolucion);
                    }
                }
                else
                {
                    printf("Devolución no encontrada.\n");
                }
                break;
            case 2:
                printf("\nALTA DE DEVOLUCIÓN\n");
                leer_cadena("Ingrese el ID del pedido al que pertenece la devolución", id_pedido, 8);
                leer_cadena("Ingrese el ID del producto a devolver", id_producto, 8);
                producto_pedido = buscar_producto_pedido(&v_productospedidos, id_pedido, id_producto);
                if(producto_pedido == NULL)
                {
                    printf("Producto o pedido no encontrado.\n");
                }
                fecha_actual = obtener_fecha_actual();
                alta_devolucion(id_pedido, id_producto, &fecha_actual, &v_devoluciones);
                break;
            case 3:
                printf("\nBAJA DE DEVOLUCIÓN\n");
                leer_cadena("Ingrese el ID de la devolución a eliminar", id_pedido, 8);
                leer_cadena("Ingrese el ID del producto a eliminar", id_producto, 8);
                devolucion = buscar_devolucion(id_pedido, id_producto, &v_devoluciones);
                if(devolucion != NULL)
                {
                    listar_devolucion(devolucion);
                    leer_caracter("Desea eliminar esta devolución? (S/N)", &respuesta);
                    if(respuesta == 'S' || respuesta == 's')
                    {
                        if(strcmp(devolucion->estado, "enviada") != 0 || strcmp(devolucion->estado, "aceptada") != 0)
                        {
                            baja_devolucion(id_pedido, id_producto, &v_devoluciones);
                        }
                        else
                        {
                            printf("No se puede eliminar una devolución que no esté pendiente o aceptada.\n");
                        }
                    }
                }
                else
                {
                    printf("Devolución no encontrada.\n");
                }
                break;
            case 4:
                printf("\nMODIFICACIÓN DE DEVOLUCIÓN\n");
                leer_cadena("Ingrese el ID de la devolución a modificar", id_pedido, 8);
                leer_cadena("Ingrese el ID del producto a modificar", id_producto, 8);
                devolucion = buscar_devolucion(id_pedido, id_producto, &v_devoluciones);
                if(devolucion != NULL)
                {
                    listar_devolucion(modificar_devolucion(devolucion));
                }
                else
                {
                    printf("Devolución no encontrada.\n");
                }
                break;
            case 5:
                printf("\nLISTADO DE DEVOLUCIONES\n");
                listar_devoluciones(&v_devoluciones);
                break;
            case 6:
                printf("\nLISTADO DE DEVOLUCIONES POR CLIENTE\n");
                leer_cadena("Ingrese el ID del cliente a listar las devoluciones", id_cliente, 8);
                if(buscar_cliente_por_id(&v_clientes, id_cliente) == NULL)
                {
                    printf("Cliente no encontrado.\n");
                    break;
                }
                listar_devoluciones_cliente(&v_devoluciones, id_cliente);
                break;
            case 7:
                printf("Volviendo al menú principal...\n");
                break;
            default:
                printf("Opción no válida, por favor intente de nuevo.\n");
                break;
        }
    }while(opcion != 7);

    guardar_devoluciones(&v_devoluciones);
    guardar_productos_pedido(&v_productospedidos);
    guardar_clientes(&v_clientes);

}

void mostrarMenuAdministrador(AdminProv *admin) {
    unsigned opcion;
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
        leer_unsigned("Seleccione una opcion", &opcion);

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
                gestionCategorias();
                break;
            case 6:
                gestionPedidos();
                break;
            case 7:
                gestionTransportistas();
                break;
            case 8:
                gestionDescuentos();
                break;
            case 9:
                gestionDevoluciones();
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

