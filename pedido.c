#include "stdio.h"
#include <string.h>
#include <malloc.h>
#include "stdlib.h"
#include "pedido.h"
#include "transportista.h"

void cargar_pedidos(VectorPedidos *v_pedidos) {
    FILE *f = fopen("../data/Pedidos.txt", "r");
    if (f == NULL) {
        perror("Error al abrir el archivo de pedidos");
        return;
    }

    char linea[100];
    Pedido *temp;
    while (fgets(linea, sizeof(linea), f) != NULL) {
        temp = (Pedido *)realloc(v_pedidos->pedidos, (v_pedidos->size + 1) * sizeof(Pedido));
        if (temp == NULL) {
            perror("Error al reservar memoria para los pedidos");
            free(v_pedidos->pedidos);
            fclose(f);
            return;
        }
        v_pedidos->pedidos = temp;

        char *token = strtok(linea, "-");
        strcpy(v_pedidos->pedidos[v_pedidos->size].id_pedido, token);

        token = strtok(NULL, "-");
        sscanf(token, "%d/%d/%d", &v_pedidos->pedidos[v_pedidos->size].fecha.dia,
               &v_pedidos->pedidos[v_pedidos->size].fecha.mes,
               &v_pedidos->pedidos[v_pedidos->size].fecha.anio);

        token = strtok(NULL, "-");
        strcpy(v_pedidos->pedidos[v_pedidos->size].id_cliente, token);

        token = strtok(NULL, "-");
        v_pedidos->pedidos[v_pedidos->size].lugar = atoi(token);

        token = strtok(NULL, "-");
        if (v_pedidos->pedidos[v_pedidos->size].lugar == 2) {
            strcpy(v_pedidos->pedidos[v_pedidos->size].id_locker, token);
        } else {
            strcpy(v_pedidos->pedidos[v_pedidos->size].id_locker, " ");
        }

        token = strtok(NULL, "-");
        if (token && strlen(token) > 0) {
            strcpy(v_pedidos->pedidos[v_pedidos->size].id_descuento, token);
        } else {
            strcpy(v_pedidos->pedidos[v_pedidos->size].id_descuento, " ");
        }

        v_pedidos->size++;
    }

    fclose(f);
}

void guardar_pedidos(VectorPedidos *v_pedidos)
{
    FILE *f = fopen("../data/Pedidos.txt", "w");
    if (f == NULL)
    {
        perror("Error al abrir el archivo de pedidos\n");
        return;
    }

    int i;
    for (i = 0; i < v_pedidos->size; i++)
    {
        fprintf(f, "%s-%02d/%02d/%d-%s-%d-%s-%s\n", v_pedidos->pedidos[i].id_pedido, v_pedidos->pedidos[i].fecha.dia, v_pedidos->pedidos[i].fecha.mes, v_pedidos->pedidos[i].fecha.anio, v_pedidos->pedidos[i].id_cliente, v_pedidos->pedidos[i].lugar, v_pedidos->pedidos[i].id_locker, v_pedidos->pedidos[i].id_descuento);
    }

    fclose(f);
    free(v_pedidos->pedidos);
}

void cargar_productos_pedido(VectorProductosPedido *v_productos_pedido)
{
    FILE *f = fopen("productos_pedido.txt", "r");
    if (f == NULL)
    {
        perror("Error al abrir el archivo de productos de pedido\n");
        return;
    }

    char linea[100];
    while (fgets(linea, 100, f) != NULL)
    {
        // Si el vector no tiene ningún producto pedido, se reserva memoria para un solo producto pedido
        if (v_productos_pedido->size == 0)
        {
            v_productos_pedido->productos_pedido = (ProductoPedido *)malloc(sizeof(ProductoPedido));
        }
        else // Si ya hay productos pedidos, se reserva memoria para un producto pedido más
        {
            ProductoPedido * temp = (ProductoPedido *)realloc(v_productos_pedido->productos_pedido, (v_productos_pedido->size + 1) * sizeof(ProductoPedido));
            if (temp == NULL)
            {
                perror("Error al reservar memoria para los productos de pedido\n");
                return;
            }
            v_productos_pedido->productos_pedido = temp;
        }

        // Se obtiene el primer token de la línea
        char *token = strtok(linea, "-");
        // Se copia el token en el campo id_pedido del producto pedido
        strcpy(v_productos_pedido->productos_pedido[v_productos_pedido->size].id_pedido, token);

        // Se obtiene el siguiente token
        token = strtok(NULL, "-");
        // Se copia el token en el campo id_producto del producto pedido
        strcpy(v_productos_pedido->productos_pedido[v_productos_pedido->size].id_producto, token);

        // Se obtiene el siguiente token
        token = strtok(NULL, "-");
        // Se convierte el token a entero y se asigna al campo num_unidades del producto pedido
        v_productos_pedido->productos_pedido[v_productos_pedido->size].num_unidades = atoi(token);

        // Se obtiene el siguiente token
        token = strtok(NULL, "-");
        // Se obtiene la fecha prevista de entrega
        sscanf(token, "%d/%d/%d",
               &v_productos_pedido->productos_pedido[v_productos_pedido->size].fecha_prevista_entrega.dia,
               &v_productos_pedido->productos_pedido[v_productos_pedido->size].fecha_prevista_entrega.mes,
               &v_productos_pedido->productos_pedido[v_productos_pedido->size].fecha_prevista_entrega.anio);

        // Se obtiene el siguiente token
        token = strtok(NULL, "-");
        // Se convierte el token a float y se asigna al campo importe del producto pedido
        v_productos_pedido->productos_pedido[v_productos_pedido->size].importe = atof(token);

        // Se obtiene el siguiente token
        token = strtok(NULL, "-");
        // Se convierte el token a entero y se asigna al campo estado del producto pedido
        v_productos_pedido->productos_pedido[v_productos_pedido->size].estado = atoi(token);

        // Se obtiene el siguiente token
        token = strtok(NULL, "-");
        // Si el estado es distinto de «enPreparación», se copia el token en el campo id_transportista del producto pedido
        if (v_productos_pedido->productos_pedido[v_productos_pedido->size].estado != 1)
        {
            strcpy(v_productos_pedido->productos_pedido[v_productos_pedido->size].id_transportista, token);
        }
        else
        {
            strcpy(v_productos_pedido->productos_pedido[v_productos_pedido->size].id_transportista, " ");
        }

        // Se obtiene el siguiente token
        token = strtok(NULL, "-");
        // Si el estado es «enLocker», se copia el token en el campo id_locker del producto pedido
        if (v_productos_pedido->productos_pedido[v_productos_pedido->size].estado == 4)
        {
            strcpy(v_productos_pedido->productos_pedido[v_productos_pedido->size].id_locker, token);
        }
        else
        {
            strcpy(v_productos_pedido->productos_pedido[v_productos_pedido->size].id_locker, " ");
        }

        // Se obtiene el siguiente token
        token = strtok(NULL, "-");
        // Si el estado es «enLocker», se copia el token en el campo cod_locker del producto pedido
        if (v_productos_pedido->productos_pedido[v_productos_pedido->size].estado == 4)
        {
            v_productos_pedido->productos_pedido[v_productos_pedido->size].cod_locker = atoi(token);
        }
        else
        {
            v_productos_pedido->productos_pedido[v_productos_pedido->size].cod_locker = 0;
        }

        // Se obtiene el siguiente token
        token = strtok(NULL, "-");
        // Si el estado es «entregado» o «devuelto», se obtiene la fecha de entrega/devolución
        if (v_productos_pedido->productos_pedido[v_productos_pedido->size].estado == 5 ||
            v_productos_pedido->productos_pedido[v_productos_pedido->size].estado == 6)
        {
            sscanf(token, "%d/%d/%d",
                   &v_productos_pedido->productos_pedido[v_productos_pedido->size].fecha_entrega_devolucion.dia,
                   &v_productos_pedido->productos_pedido[v_productos_pedido->size].fecha_entrega_devolucion.mes,
                   &v_productos_pedido->productos_pedido[v_productos_pedido->size].fecha_entrega_devolucion.anio);
        }
    }
}

void guardar_productos_pedido(VectorProductosPedido *v_productos_pedido)
{
    FILE *f = fopen("productos_pedido.txt", "w");
    if (f == NULL)
    {
        perror("Error al abrir el archivo de productos de pedido\n");
        return;
    }

    int i;

    // Guardar sustituyendo los valores nulos por espacios en blanco
    for (i = 0; i < v_productos_pedido->size; i++)
    {
        // Construiremos la línea dato por dato, y luego introduciremos la línea en el archivo, y si algún dato es nulo (a la inversa de lo que se especifica en la carga), lo sustituiremos por un espacio en blanco
        char linea[100];

        // ID del pedido
        if (strlen(v_productos_pedido->productos_pedido[i].id_pedido) > 0)
        {
            sprintf(linea, "%s-", v_productos_pedido->productos_pedido[i].id_pedido);
        }
        else
        {
            sprintf(linea, " -");
        }

        // ID del producto
        if (strlen(v_productos_pedido->productos_pedido[i].id_producto) > 0)
        {
            sprintf(linea, "%s%s-", linea, v_productos_pedido->productos_pedido[i].id_producto);
        }
        else
        {
            sprintf(linea, "%s -", linea);
        }

        // Número de unidades
        sprintf(linea, "%s%d-", linea, v_productos_pedido->productos_pedido[i].num_unidades);

        // Fecha prevista de entrega
        sprintf(linea, "%s%02d/%02d/%d-", linea, v_productos_pedido->productos_pedido[i].fecha_prevista_entrega.dia, v_productos_pedido->productos_pedido[i].fecha_prevista_entrega.mes, v_productos_pedido->productos_pedido[i].fecha_prevista_entrega.anio);

        // Importe
        sprintf(linea, "%s%.2f-", linea, v_productos_pedido->productos_pedido[i].importe);

        // Estado
        sprintf(linea, "%s%d-", linea, v_productos_pedido->productos_pedido[i].estado);

        // ID del transportista
        if (strlen(v_productos_pedido->productos_pedido[i].id_transportista) > 0)
        {
            sprintf(linea, "%s%s-", linea, v_productos_pedido->productos_pedido[i].id_transportista);
        }
        else
        {
            sprintf(linea, "%s -", linea);
        }

        // ID del locker
        if (strlen(v_productos_pedido->productos_pedido[i].id_locker) > 0)
        {
            sprintf(linea, "%s%s-", linea, v_productos_pedido->productos_pedido[i].id_locker);
        }
        else
        {
            sprintf(linea, "%s -", linea);
        }

        // Código del locker
        if(v_productos_pedido->productos_pedido[i].cod_locker > 0)
        {
            sprintf(linea, "%s%u-", linea, v_productos_pedido->productos_pedido[i].cod_locker);
        }
        else
        {
            sprintf(linea, "%s -", linea);
        }

        // Fecha de entrega/devolución
        if (v_productos_pedido->productos_pedido[i].estado == 5 || v_productos_pedido->productos_pedido[i].estado == 6)
        {
            sprintf(linea, "%s%02d/%02d/%d\n", linea, v_productos_pedido->productos_pedido[i].fecha_entrega_devolucion.dia, v_productos_pedido->productos_pedido[i].fecha_entrega_devolucion.mes, v_productos_pedido->productos_pedido[i].fecha_entrega_devolucion.anio);
        }
        else
        {
            sprintf(linea, "%s -\n", linea);
        }

        fprintf(f, "%s", linea);
    }

    fclose(f);
    free(v_productos_pedido->productos_pedido);
}

Pedido* buscar_pedido_por_id(VectorPedidos *v_pedidos, char *id_pedido)
{
    int i;
    for (i = 0; i < v_pedidos->size; i++)
    {
        if (strcmp(v_pedidos->pedidos[i].id_pedido, id_pedido) == 0)
        {
            return &v_pedidos->pedidos[i];
        }
    }

    return NULL;
}

void listar_pedido(Pedido *pedido)
{
    printf("========================================\n");
    printf("Pedido: %s\n", pedido->id_pedido);
    printf("Fecha: %02d/%02d/%d\n", pedido->fecha.dia, pedido->fecha.mes, pedido->fecha.anio);
    printf("Cliente: %s\n", pedido->id_cliente);
    printf("Lugar: %s\n", pedido->lugar == 1 ? "domicilio" : "locker");
    if (pedido->lugar == 2)
    {
        printf("Locker: %s\n", pedido->id_locker);
    }
    printf("Descuento: %s\n", pedido->id_descuento);
    printf("========================================\n");
}

void listar_pedidos(VectorPedidos *v_pedidos)
{
    int i;
    for (i = 0; i < v_pedidos->size; i++)
    {
        listar_pedido(&v_pedidos->pedidos[i]);
    }
}

unsigned listar_pedidos_cliente(VectorPedidos *v_pedidos, char *id_cliente)
{
    unsigned pedidos_cliente = 0;
    int i;
    for (i = 0; i < v_pedidos->size; i++)
    {
        if (strcmp(v_pedidos->pedidos[i].id_cliente, id_cliente) == 0)
        {
            pedidos_cliente++;
            listar_pedido(&v_pedidos->pedidos[i]);
        }
    }
    return pedidos_cliente;
}

void listar_producto_pedido(ProductoPedido *producto_pedido)
{
    printf("========================================\n");
    printf("ID Pedido: %s\n", producto_pedido->id_pedido);
    printf("ID Producto: %s\n", producto_pedido->id_producto);
    printf("Unidades: %u\n", producto_pedido->num_unidades);
    printf("Fecha prevista de entrega: %d/%d/%d\n", producto_pedido->fecha_prevista_entrega.dia,
           producto_pedido->fecha_prevista_entrega.mes,
           producto_pedido->fecha_prevista_entrega.anio);
    printf("Importe: %.2f\n", producto_pedido->importe);
    printf("Estado: %u\n", producto_pedido->estado);
    printf("ID Transportista: %s\n", producto_pedido->id_transportista);
    printf("ID Locker: %s\n", producto_pedido->id_locker);
    printf("Codigo Locker: %u\n", producto_pedido->cod_locker);
    printf("Fecha de entrega o devolución: %d/%d/%d\n", producto_pedido->fecha_entrega_devolucion.dia,
           producto_pedido->fecha_entrega_devolucion.mes,
           producto_pedido->fecha_entrega_devolucion.anio);
    printf("========================================\n");
}

void listar_productos_pedido(VectorProductosPedido *v_productos_pedido, char *id_pedido)
{
    int i;
    for(i = 0; i < v_productos_pedido->size; i++){
        if(strcmp(v_productos_pedido->productos_pedido[i].id_pedido, id_pedido) == 0){
            listar_producto_pedido(&v_productos_pedido->productos_pedido[i]);
        }
    }
}

unsigned listar_productos_transportista(VectorProductosPedido *v_productos_pedido, char *id_transportista)
{
    unsigned n_productos = 0;
    int i;
    for (i = 0; i < v_productos_pedido->size; i++)
    {
        if (strcmp(v_productos_pedido->productos_pedido[i].id_transportista, id_transportista) == 0)
        {
            listar_producto_pedido(&v_productos_pedido->productos_pedido[i]);
            n_productos++;
        }
    }
    return n_productos;
}

/*void listar_productos_asignados_pedido(VectorProductosPedido* v_productos_pedido, char* id_pedido, char* id_transportista)
{
    int i;
    for (i = 0; i < v_productos_pedido->size; i++) {
        if (strcmp(v_productos_pedido->productos_pedido[i].id_pedido, id_pedido) == 0 &&
            strcmp(v_productos_pedido->productos_pedido[i].id_transportista, id_transportista) == 0) {
            listar_producto_pedido(&v_productos_pedido->productos_pedido[i]);
        }
    }
}*/

int pertenece_pedido(VectorProductosPedido *v_productos_pedido, char *id_pedido, char *id_producto)
{
    int i;
    for (i = 0; i < v_productos_pedido->size; i++)
    {
        if (strcmp(v_productos_pedido->productos_pedido[i].id_pedido, id_pedido) == 0 && strcmp(v_productos_pedido->productos_pedido[i].id_producto, id_producto) == 0)
        {
            return 1;
        }
    }
    return 0;
}

ProductoPedido *buscar_producto_pedido(VectorProductosPedido *v_productos_pedido, char *id_pedido, char *id_producto)
{
    int i;
    for (i = 0; i < v_productos_pedido->size; i++)
    {
        if (strcmp(v_productos_pedido->productos_pedido[i].id_pedido, id_pedido) == 0 && strcmp(v_productos_pedido->productos_pedido[i].id_producto, id_producto) == 0)
        {
            return &v_productos_pedido->productos_pedido[i];
        }
    }
    return NULL;
}

ProductoPedido *buscar_producto_pedido_por_compartimento(VectorProductosPedido *v_productos_pedido, char *id_locker, unsigned n_compartimento)
{
    int i;
    for (i = 0; i < v_productos_pedido->size; i++)
    {
        if (strcmp(v_productos_pedido->productos_pedido[i].id_locker, id_locker) == 0 && v_productos_pedido->productos_pedido[i].cod_locker == n_compartimento)
        {
            return &v_productos_pedido->productos_pedido[i];
        }
    }

    return NULL;
}

// Modularización de realizar pedido en subfunciones para facilitar la lectura del código y mantenimiento, además la optimización de la memoria y de código
float nuevo_producto_pedido(Pedido* pedido, VectorProductos* v_productos, VectorProductosPedido* v_productos_pedido)
{
    ProductoPedido* temp = (ProductoPedido *)realloc(v_productos_pedido->productos_pedido, (v_productos_pedido->size + 1) * sizeof(ProductoPedido));
    if (temp == NULL)
    {
        perror("Error al reservar memoria");
        return 0.0f;
    }
    v_productos_pedido->productos_pedido = temp;

    char id_producto[8];
    unsigned num_unidades;
    Fecha fecha_prevista_entrega;
    float importe;
    unsigned estado;
    char id_transportista[8];
    char id_locker[11];
    unsigned cod_locker;
    Fecha fecha_entrega_devolucion;

    char respuesta;

    Producto* producto;

    strcpy(v_productos_pedido->productos_pedido[v_productos_pedido->size].id_pedido, pedido->id_pedido);

    leer_cadena("Introduce el ID del producto: ", id_producto, 8);
    producto = buscar_producto_id(v_productos, id_producto);
    if (producto == NULL)
    {
        printf("Producto no encontrado\n");
        printf("\n¿Desea listar los productos disponibles (S/N): ");
        leer_caracter("Introduce una opción valida", &respuesta);
        if(respuesta == 's' || respuesta == 'S')
        {
            listar_productos(v_productos);
            printf("\n¿Desea introducir el ID del producto de nuevo (S/N): ");
            leer_caracter("Introduce una opción valida", &respuesta);
        }
        if(respuesta == 'n' || respuesta == 'N')
        {
            return 0.0f;
        }
        leer_cadena("Introduce el ID del producto: ", id_producto, 8);
        producto = buscar_producto_id(v_productos, id_producto);
        if (producto == NULL)
        {
            printf("Producto no encontrado\n");
            return 0.0f;
        }
        else{
            printf("Producto encontrado\n");
            listar_producto(producto);
        }
    }

    leer_unsigned("Introduce el número de unidades: ", &num_unidades);
    if (num_unidades > producto->stock)
    {
        printf("No hay suficiente stock\n");
        printf("Stock disponible: %u\n", producto->stock);
        printf("\n¿Desea introducir el número de unidades de nuevo (S/N): ");
        leer_caracter("Introduce una opción valida", &respuesta);
        if(respuesta == 's' || respuesta == 'S')
        {
            leer_unsigned("Introduce el número de unidades: ", &num_unidades);
            if (num_unidades > producto->stock)
            {
                printf("No hay suficiente stock\n");
                return 0.0f;
            }
        }
        else
        {
            return 0.0f;
        }
    }

    fecha_prevista_entrega = pedido->fecha;
    fecha_prevista_entrega.dia += producto->entrega;

    importe = producto->importe * num_unidades;

    estado = 1;

    strcpy(id_transportista, " ");

    strcpy(id_locker, pedido->id_locker);

    cod_locker = 0;

    fecha_entrega_devolucion = crearFecha(0, 0, 0);

    strcpy(v_productos_pedido->productos_pedido[v_productos_pedido->size].id_producto, id_producto);
    v_productos_pedido->productos_pedido[v_productos_pedido->size].num_unidades = num_unidades;
    v_productos_pedido->productos_pedido[v_productos_pedido->size].fecha_prevista_entrega = fecha_prevista_entrega;
    v_productos_pedido->productos_pedido[v_productos_pedido->size].importe = importe;
    v_productos_pedido->productos_pedido[v_productos_pedido->size].estado = estado;
    strcpy(v_productos_pedido->productos_pedido[v_productos_pedido->size].id_transportista, id_transportista);
    strcpy(v_productos_pedido->productos_pedido[v_productos_pedido->size].id_locker, id_locker);
    v_productos_pedido->productos_pedido[v_productos_pedido->size].cod_locker = cod_locker;
    v_productos_pedido->productos_pedido[v_productos_pedido->size].fecha_entrega_devolucion = fecha_entrega_devolucion;

    v_productos_pedido->size++;

    return importe;
}

Pedido* nuevo_pedido(VectorPedidos *v_pedidos, Cliente* cliente, VectorLockers* v_lockers, VectorDescuentos* v_descuentos, VectorDescuentosClientes* v_descuentos_cliente)
{
    Pedido *temp = (Pedido *)realloc(v_pedidos->pedidos, (v_pedidos->size + 1) * sizeof(Pedido));
    if (temp == NULL)
    {
        perror("Error al reservar memoria");
        return NULL;
    }
    v_pedidos->pedidos = temp;

    // El ID del pedido se genera automáticamente, accediendo al ID del último pedido, transformándolo a entero y sumándole 1, y luego se convierte a string de nuevo
    char id_pedido[8];
    sprintf(id_pedido, "%07d", atoi(v_pedidos->pedidos[v_pedidos->size - 1].id_pedido) + 1);

    // Obtenemos la fecha actual
    Fecha fecha = obtener_fecha_actual();

    // Copiamos el ID del cliente
    char id_cliente[8];
    strcpy(id_cliente, cliente->id_cliente);

    // Preguntamos si desea entrega del pedido a domicilio o en un locker
    unsigned lugar;
    do
    {
        printf("1. Domicilio\n");
        printf("2. Locker\n");
        leer_unsigned("Introduce una opcion valida", &lugar);
    } while (lugar != 1 && lugar != 2);

    char id_locker[11];

    // Si la entrega es en un locker, mostramos los lockers y solicitamos que introduzca el ID del locker
    if (lugar == 2)
    {
        listar_todo_lockers(v_lockers);
        leer_cadena("Introduce el ID del locker: ", id_locker, 11);
        Locker* locker = buscar_locker_id(v_lockers, id_locker);
        if (locker == NULL)
        {
            strcpy(id_locker, " ");
            printf("Locker no encontrado\n");
        }
        else
        {
            strcpy(id_locker, locker->id_locker);
            printf("Locker asignado\n");
            listar_locker(locker);
        }
    }

    char id_descuento[11];

    // Preguntamos si desea aplicar un descuento
    char respuesta;
    printf("¿Desea aplicar un descuento? (s/n): ");
    leer_caracter("Introduce una opcion valida", &respuesta);

    // Si desea aplicar un descuento, mostramos los descuentos del cliente y solicitamos que introduzca el ID del descuento
    if (respuesta == 's' || respuesta == 'S')
    {
        DescuentoCliente* descuento_cliente;
        listar_descuentos_cliente(v_descuentos_cliente, v_descuentos, cliente->id_cliente);
        leer_cadena("Introduce el ID del descuento: ", id_descuento, 11);
        descuento_cliente = buscar_descuentocliente(v_descuentos_cliente, cliente->id_cliente, id_descuento);
        if (descuento_cliente == NULL)
        {
            strcpy(id_descuento, " ");
            printf("Descuento no encontrado\n");
        }
        else if(descuento_valido(descuento_cliente, cliente->id_cliente))
        {
            strcpy(id_descuento, descuento_cliente->id_codigo);
            descuento_cliente->estado = 1;
            printf("Descuento aplicado\n");
        }
        else
        {
            printf("Descuento no aplicable\n");
        }
    }

    strcpy(v_pedidos->pedidos[v_pedidos->size].id_pedido, id_pedido);
    v_pedidos->pedidos[v_pedidos->size].fecha = fecha;
    strcpy(v_pedidos->pedidos[v_pedidos->size].id_cliente, id_cliente);
    v_pedidos->pedidos[v_pedidos->size].lugar = lugar;
    strcpy(v_pedidos->pedidos[v_pedidos->size].id_locker, id_locker);
    strcpy(v_pedidos->pedidos[v_pedidos->size].id_descuento, id_descuento);

    v_pedidos->size++;

    return &v_pedidos->pedidos[v_pedidos->size - 1];
}

void realizar_pedido
(
        Cliente *cliente,
        VectorPedidos *v_pedidos,
        VectorProductosPedido *v_productos_pedido,
        VectorLockers *v_lockers,
        VectorDescuentos *v_descuentos,
        VectorDescuentosClientes *v_descuentos_cliente,
        VectorProductos *v_productos
)
{
    // Creamos el pedido
    Pedido* pedido = nuevo_pedido(v_pedidos, cliente, v_lockers, v_descuentos, v_descuentos_cliente);

    Descuento* descuento = buscar_descuento_id(v_descuentos, pedido->id_descuento);

    unsigned n_productos = 0;
    char respuesta;
    float importe_total = 0.0f;

    // Especificamos un bucle indefinido para añadir productos al pedido
    while (1) {
        if (n_productos > 0) {
            printf("¿Desea añadir otro producto? (S/N): ");
            leer_caracter("Introduce una opción valida", &respuesta);
        }

        if (n_productos == 0 || respuesta == 'S' || respuesta == 's') {
            importe_total += nuevo_producto_pedido(pedido, v_productos, v_productos_pedido);
            n_productos++;
        } else {
            break;
        }
    }

    if(descuento != NULL)
    {
        importe_total -= descuento->importe;
        if(importe_total < 0.0f)
        {
            importe_total = 0.0f;
        }
    }

    // Mostramos el pedido
    listar_pedido(pedido);
    printf("----------------------------------------\n");
    printf("Número de productos: %u\n", n_productos);
    printf("Productos del pedido:\n");
    listar_productos_pedido(v_productos_pedido, pedido->id_pedido);
    printf("Importe total: %.2f\n", importe_total);

    leer_caracter("¿Desea confirmar el pedido? (S/N):" , &respuesta);

    if((respuesta == 'N' || respuesta == 'n') || cliente->cartera < importe_total) {
        eliminar_pedido(pedido->id_pedido, v_pedidos, v_productos_pedido);
        if(cliente->cartera < importe_total && (respuesta == 'S' || respuesta == 's'))
        {
            printf("No se ha podido realizar el pedido por falta de fondos en la cuenta.\n");
        }
        printf("Pedido cancelado\n");
    }
    else
    {
        cliente->cartera -= importe_total;
        printf("Pedido realizado\n");
    }
}

// True si todos los productos del pedido tienen el estado enPreparacion
int enPreparacion(char* id_pedido, VectorProductosPedido* v_pedidos)
{
    int i;
    for(i = 0; i < v_pedidos->size; i++)
    {
        if(strcmp(v_pedidos->productos_pedido[i].id_pedido, id_pedido) == 0 && v_pedidos->productos_pedido[i].estado != 1)
        {
            return 0;
        }
    }
    return 1;
}

Pedido* modificar_pedido(Pedido* pedido, VectorProductosPedido* v_pp, VectorClientes* v_clientes, VectorLockers* v_lockers)
{
    printf("ATENCIÓN: Por cuestiones de integridad logística, únicamente se puede modificar el pedido si todos los productos del pedido no han sido aún enviados.\n");

    unsigned opcion = 0;
    Cliente* cliente;
    Locker* locker;
    char* id_cliente = pedido->id_cliente;
    char id_locker[11];

    if(enPreparacion(pedido->id_pedido, v_pp))
    {
        do{
            printf("1. Lugar de entrega actual: %s\n", pedido->lugar == 1 ? "domicilio" : "locker");
            // Si el lugar es 1, se busca el cliente y se muestra su domicilio
            if (pedido->lugar == 1)
            {
                cliente = buscar_cliente_por_id(v_clientes, id_cliente);
                if (cliente != NULL)
                {
                    printf("2. Domicilio del cliente: %s\n", cliente->direccion_cliente);
                }
            }
                // Si el lugar es 2, se busca el locker y se muestra su información
            else
            {
                locker = buscar_locker_id(v_lockers, pedido->id_locker);
                if (locker != NULL)
                {
                    // 3. Locker: 0000000000. Ubicación - Localidad
                    printf("2. Locker: %s. %s - %s\n", locker->id_locker, locker->ubicacion, locker->localidad);
                }
            }
            printf("3. Salir.\n");

            leer_unsigned("Introduce una opción valida", &opcion);

            switch(opcion)
            {
                case 1:
                    if(pedido->lugar == 1)
                    {
                        if(cliente != NULL)
                        {
                            listar_lockers_localidad(v_lockers, cliente->poblacion);
                            leer_cadena("Introduce el ID del locker: ", id_locker, 11);
                            locker = buscar_locker_id(v_lockers, id_locker);
                            if(locker != NULL)
                            {
                                pedido->lugar = 2;
                                strcpy(pedido->id_locker, id_locker);
                            }
                            else
                            {
                                printf("Locker no encontrado\n");
                            }
                        }
                    }
                    else
                    {
                        pedido->lugar = 1;
                    }
                    break;
                case 2:
                    if(pedido->lugar == 1)
                    {
                        printf("Tenga en cuenta que modificar el domicilio del cliente se reflejará en todos los aspectos del sistema (Perfil, Entregas, etc.). ¿Desea continuar? (S/N) \n");
                        char respuesta;
                        leer_caracter("Introduce una opción valida", &respuesta);
                        if(respuesta == 's' || respuesta == 'S')
                        {
                            cliente = buscar_cliente_por_id(v_clientes, id_cliente);
                            if(cliente != NULL)
                            {
                                leer_cadena("Introduce el nuevo domicilio: ", cliente->direccion_cliente, 100);
                            }
                        }
                    }
                    else
                    {
                        if(cliente != NULL)
                        {
                            listar_lockers_localidad(v_lockers, cliente->poblacion);
                            leer_cadena("Introduce el ID del locker: ", id_locker, 11);
                            locker = buscar_locker_id(v_lockers, id_locker);
                            if(locker != NULL)
                            {
                                strcpy(pedido->id_locker, id_locker);
                            }
                            else
                            {
                                printf("Locker no encontrado\n");
                            }
                        }
                    }
                    break;
                case 3:
                    printf("Saliendo...\n");
                    break;
                default:
                    printf("Opción no válida\n");
                    break;
            }
        }while(opcion != 3);
    }
    else
    {
        printf("No se puede modificar el pedido\n");
        listar_productos_pedido(v_pp, pedido->id_pedido);
    }
    return pedido;
}

void eliminar_producto_pedido(char* id_pedido, char* id_producto, VectorProductosPedido* v_productos_pedido)
{
    int i;
    for(i = 0; i < v_productos_pedido->size; i++)
    {
        if(strcmp(v_productos_pedido->productos_pedido[i].id_pedido, id_pedido) == 0 && strcmp(v_productos_pedido->productos_pedido[i].id_producto, id_producto) == 0)
        {
            break;
        }
    }
    if(i == v_productos_pedido->size)
    {
        printf("Producto no encontrado\n");
        return;
    }
    if(v_productos_pedido->productos_pedido[i].estado != 1)
    {
        printf("No se puede eliminar el producto, ya que ha sido enviado.\n");
        return;
    }
    for(; i < v_productos_pedido->size - 1; i++)
    {
        v_productos_pedido->productos_pedido[i] = v_productos_pedido->productos_pedido[i + 1];
    }

    v_productos_pedido->size--;

    ProductoPedido* temp = (ProductoPedido*)realloc(v_productos_pedido->productos_pedido, v_productos_pedido->size * sizeof(ProductoPedido));
    if(temp == NULL)
    {
        perror("Error al redimensionar el vector\n");
        return;
    }
    v_productos_pedido->productos_pedido = temp;
}

void eliminar_productos_pedido(char* id_pedido, VectorProductosPedido* v_productos_pedido)
{
    int i;
    for(i = 0; i < v_productos_pedido->size; i++)
    {
        if(strcmp(v_productos_pedido->productos_pedido[i].id_pedido, id_pedido) == 0)
        {
            eliminar_producto_pedido(id_pedido, v_productos_pedido->productos_pedido[i].id_producto, v_productos_pedido);
        }
    }
}

void eliminar_pedido(char* id_pedido, VectorPedidos* v_pedidos, VectorProductosPedido* v_productos_pedido)
{
    if(enPreparacion(id_pedido, v_productos_pedido))
    {
        eliminar_productos_pedido(id_pedido, v_productos_pedido);

        int i;
        for(i = 0; i < v_pedidos->size; i++)
        {
            if(strcmp(v_pedidos->pedidos[i].id_pedido, id_pedido) == 0)
            {
                break;
            }
        }

        for(; i < v_pedidos->size - 1; i++)
        {
            v_pedidos->pedidos[i] = v_pedidos->pedidos[i + 1];
        }

        v_pedidos->size--;

        Pedido* temp = (Pedido*)realloc(v_pedidos->pedidos, v_pedidos->size * sizeof(Pedido));
        if(temp == NULL)
        {
            perror("Error al redimensionar el vector\n");
            return;
        }
        v_pedidos->pedidos = temp;
    }
    else
    {
        printf("No se puede eliminar el pedido, ya que hay elementos que han sido enviados.\n");
    }
}

// Mostrar un listado con la información de todos los productos pedidos dados de alta en el sistema, ordenados por fecha de entrega ascendentemente (fecha más próxima primero) y estado (enPreparación primero). Los productos entregados y/o devueltos serán menos prioritarios, siendo el último nivel de prioridad el entregado.
void listar_todos_productos_pedidos(VectorProductosPedido* v_productos_pedido)
{
    int i, j;
    // Creamos un vector temporal, copia del vector original, para ordenar los productos pedidos
    VectorProductosPedido temp;
    temp.size = v_productos_pedido->size;
    temp.productos_pedido = (ProductoPedido*)malloc(temp.size * sizeof(ProductoPedido));
    if(temp.productos_pedido == NULL)
    {
        perror("Error al reservar memoria\n");
        return;
    }
    for(i = 0; i < temp.size; i++)
    {
        temp.productos_pedido[i] = v_productos_pedido->productos_pedido[i];
    }

    // Ahora ordenamos el vector temporal en función de la fecha de entrega (haciendo uso de la función comparar_fechas definida en fecha.h)
    for(i = 0; i < temp.size - 1; i++)
    {
        for(j = 0; j < temp.size - i - 1; j++)
        {
            // Siempre irá antes la fecha de entrega prevista más próxima. En caso de empate, se prioriza el estado enPreparación.
            if(comparar_fechas(temp.productos_pedido[j].fecha_prevista_entrega, temp.productos_pedido[j + 1].fecha_prevista_entrega) == 1 ||
               (comparar_fechas(temp.productos_pedido[j].fecha_prevista_entrega, temp.productos_pedido[j + 1].fecha_prevista_entrega) == 0 &&
                temp.productos_pedido[j].estado == 1 && temp.productos_pedido[j + 1].estado != 1))
            {
                ProductoPedido aux = temp.productos_pedido[j];
                temp.productos_pedido[j] = temp.productos_pedido[j + 1];
                temp.productos_pedido[j + 1] = aux;
            }
            listar_producto_pedido(&temp.productos_pedido[j]);
        }
    }

    free(temp.productos_pedido);
}

unsigned listar_productospedidos_proveedor(char* id_proveedor, VectorProductos* v_productos, VectorProductosPedido* v_productos_pedido)
{
    unsigned n_productos = 0;
    int i, j;
    for(i = 0; i < v_productos_pedido->size; i++)
    {   //Si el producto del producto pediddo pertence al proveedor se muestra
        for(j = 0; j < v_productos->size; j++)
        {
            if(strcmp(v_productos_pedido->productos_pedido[i].id_producto, v_productos->productos[j].id_producto) == 0 && strcmp(v_productos->productos[j].id_gestor, id_proveedor) == 0)
            {
                listar_producto_pedido(&v_productos_pedido->productos_pedido[i]);
                n_productos++;
            }
        }

    }
    return n_productos;
}

void enviar_producto_pedido(ProductoPedido* producto_pedido, VectorTransportistas* v_transportistas)
{
    char id_transportista[8];
    Transportista* transportista = NULL;
    do{
        leer_cadena("Introduce el ID del transportista: ", id_transportista, 8);
        transportista = buscar_transportista_id(v_transportistas, id_transportista);
        if(transportista == NULL)
        {
            printf("Transportista no encontrado\n");
        }
    }while(transportista == NULL);
    producto_pedido->estado = 2;
    strcpy(producto_pedido->id_transportista, id_transportista);
}