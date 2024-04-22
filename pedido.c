#include "stdio.h"
#include <string.h>
#include <malloc.h>
#include "stdlib.h"
#include "pedido.h"

// Funciones para cargar y guardar los pedidos (al estilo de cliente.c)
/*
    Los campos, separados por guiones, son los que se describen a continuación:
    o Identificador del pedido (Id_pedido), 7 dígitos.
    o Fecha del pedido (día, mes y año)
    o Identificador del cliente que realiza el pedido (Id_cliente), 7 dígitos.
    o Lugar de entrega (Lugar): «domicilio» o «locker»
    o Identificador de Locker (id_locker), 10 caracteres máximo. [Solo si el lugar de entrega es locker]
    o Identificador del código promocional o cheque regalo (id_descuento), 10 caracteres máximo. [Solo si el cliente ha introducido un código promocional o cheque regalo]

    Ejemplo de línea de pedido con todos los campos completos:
    0000001-01/01/2021-0000001-2-0000000001-0000000001

    Ejemplo de línea de pedido con solo los campos obligatorios (dejando un espacio en blanco en los campos correspondientes):
    0000002-01/01/2021-0000001-1- -

    En general, el formato de la línea de pedido es el siguiente:
    id_pedido-fecha_pedido-id_cliente-lugar-id_locker-id_descuento

    Primero deberá inicializar el puntero de pedidos para alojar un solo pedido y su tamaño a 0.
    Luego, abrir el archivo en modo lectura y leer cada línea, separando los campos por el carácter '-'.
    Si el vector, definido en el puntero de pedidos, no tiene espacio suficiente, deberá incrementar su tamaño en 1 unidad.

    Para los campos que tengan un espacio en blanco, deberá asignar el carácter de espacio en blanco " ".
    Para los campos que no tengan un espacio en blanco, deberá copiar el contenido de la cadena leída en el campo correspondiente.
*/
//EJemplo : Primer caso a domicilio con cheque regalo (no aplica codigo locker) y segundo caso entrega a locker sin cheque regalo
//0000001-02/02/2024-0000001-domicilio- -che001
//0000002-03/02/2024-0000002-locker-Lock001-
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

// Funciones para cargar y guardar los productos de un pedido (al estilo de cliente.c)
/*
    Los campos, separados por guiones, son los que se describen a continuación:
    o Identificador del pedido (id_pedido), 7 dígitos.
    o Identificador del producto (id_producto), 7 dígitos.
    o Número de unidades (num_unidades)
    o Fecha prevista de entrega (día, mes y año).
    o Importe del producto en euros (importe). Importante que quede constancia del importe al que compra un cliente un producto si la empresa modifica posteriormente su importe.
    o Estado del pedido: «enPreparación», «enviado», «enReparto», «enLocker», «entregado», «devuelto» o «transportista».
    o Identificador del transportista (id_transportista), 4 dígitos. (Solo si el estado es distinto de «enPreparación»)
    o Identificador del locker (id_locker), 10 caracteres máximo. (Solo si el estado es «enLocker»
    o Código del locker (cod_locker). (Solo si el estado es «enLocker»)
    o Fecha de entrega/devolución por el transportista (Solo si el estado es <<entregado>> o <<devuelto>>)

    Ejemplo de línea de producto pedido con todos los campos completos:
    0000001-0000001-1-01/01/2021-10.50-1-0001-0000000001-0000000001-01/01/2021

    Ejemplo de línea de producto pedido con solo los campos obligatorios (dejando un espacio en blanco en los campos correspondientes):
    0000002-0000001-1-01/01/2021-10.50-1- - - -

    En general, el formato de la línea de pedido es el siguiente:
    id_pedido-id_producto-num_unidades-fecha_prevista_entrega-importe-estado-id_transportista-id_locker-cod_locker-fecha_entrega_devolucion

    Primero deberá inicializar el puntero de producto pedidos para alojar un solo producto pedido y su tamaño a 0.
    Luego, abrir el archivo en modo lectura y leer cada línea, separando los campos por el carácter '-'.
    Si el vector, definido en el puntero de productos pedidos, no tiene espacio suficiente, deberá incrementar su tamaño en 1 unidad.

    Para los campos que tengan un espacio en blanco, deberá asignar el carácter de espacio en blanco " ".
    Para los campos que no tengan un espacio en blanco, deberá copiar el contenido de la cadena leída en el campo correspondiente.
*/

//Ejemplo:
//0000001-000001-1-07/03/2024-340-enPreparación
//0000001-000002-1-03/02/2024-45-entregado-0001
//0000002-000001-2-08/02/2024-45-enLocker-0002-Lock001-134697-08/02/2024
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
            v_productos_pedido->productos_pedido = (ProductoPedido *)realloc(v_productos_pedido->productos_pedido,
                                                                             (v_productos_pedido->size + 1) *
                                                                                 sizeof(ProductoPedido));
            if (v_productos_pedido->productos_pedido == NULL)
            {
                perror("Error al reservar memoria para los productos de pedido\n");
                free(v_productos_pedido->productos_pedido);
                return;
            }
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
            //strcpy(v_productos_pedido->productos_pedido[v_productos_pedido->size].cod_locker, token);
            // Rehacer con el nuevo tipo de dato TODO
        }
        else
        {
            //strcpy(v_productos_pedido->productos_pedido[v_productos_pedido->size].cod_locker, " ");
            // Rehacer con el nuevo tipo de dato TODO
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
    for (i = 0; i < v_productos_pedido->size; i++)
    {
        // fprintf(f, "%s-%s-%d-%02d/%02d/%d-%.2f-%d-%s-%s-%s-%02d/%02d/%d\n", v_productos_pedido->productos_pedido[i].id_pedido, v_productos_pedido->productos_pedido[i].id_producto, v_productos_pedido->productos_pedido[i].num_unidades, v_productos_pedido->productos_pedido[i].fecha_prevista_entrega.dia, v_productos_pedido->productos_pedido[i].fecha_prevista_entrega.mes, v_productos_pedido->productos_pedido[i].fecha_prevista_entrega.anio, v_productos_pedido->productos_pedido[i].importe, v_productos_pedido->productos_pedido[i].estado, v_productos_pedido->productos_pedido[i].id_transportista, v_productos_pedido->productos_pedido[i].id_locker, v_productos_pedido->productos_pedido[i].cod_locker, v_productos_pedido->productos_pedido[i].fecha_entrega_devolucion.dia, v_productos_pedido->productos_pedido[i].fecha_entrega_devolucion.mes, v_productos_pedido->productos_pedido[i].fecha_entrega_devolucion.anio);
        // Rehacer con el nuevo tipo de dato TODO
    }

    fclose(f);
    free(v_productos_pedido->productos_pedido);
}

Pedido *buscar_pedido_por_id(VectorPedidos *v_pedidos, char *id_pedido)
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

void listar_pedidos_cliente(VectorPedidos *v_pedidos, char *id_cliente)
{
    int i;
    for (i = 0; i < v_pedidos->size; i++)
    {
        if (strcmp(v_pedidos->pedidos[i].id_cliente, id_cliente) == 0)
        {
            printf("Pedido: %s\n", v_pedidos->pedidos[i].id_pedido);
            printf("Fecha: %02d/%02d/%d\n", v_pedidos->pedidos[i].fecha.dia, v_pedidos->pedidos[i].fecha.mes, v_pedidos->pedidos[i].fecha.anio);
            printf("Cliente: %s\n", v_pedidos->pedidos[i].id_cliente);
            printf("Lugar: %s\n", v_pedidos->pedidos[i].lugar == 1 ? "domicilio" : "locker");
            if (v_pedidos->pedidos[i].lugar == 2)
            {
                printf("Locker: %s\n", v_pedidos->pedidos[i].id_locker);
            }
            printf("Descuento: %s\n", v_pedidos->pedidos[i].id_descuento);
            printf("\n");
        }
    }
}

//listar productos de un pedido
void listar_productos_pedido(VectorProductosPedido *v_productos_pedido, char *id_pedido)
{
    int i;
    for (i = 0; i < v_productos_pedido->size; i++)
    {
        if (strcmp(v_productos_pedido->productos_pedido[i].id_pedido, id_pedido) == 0)
        {
            printf("Producto: %s\n", v_productos_pedido->productos_pedido[i].id_producto);
            printf("Unidades: %d\n", v_productos_pedido->productos_pedido[i].num_unidades);
            printf("Fecha prevista de entrega: %02d/%02d/%d\n", v_productos_pedido->productos_pedido[i].fecha_prevista_entrega.dia, v_productos_pedido->productos_pedido[i].fecha_prevista_entrega.mes, v_productos_pedido->productos_pedido[i].fecha_prevista_entrega.anio);
            printf("Importe: %.2f\n", v_productos_pedido->productos_pedido[i].importe);
            printf("Estado: %d\n", v_productos_pedido->productos_pedido[i].estado);
            if (v_productos_pedido->productos_pedido[i].estado != 1)
            {
                printf("Transportista: %s\n", v_productos_pedido->productos_pedido[i].id_transportista);
            }
            if (v_productos_pedido->productos_pedido[i].estado == 4)
            {
                printf("Locker: %s\n", v_productos_pedido->productos_pedido[i].id_locker);
                // printf("Código locker: %s\n", v_productos_pedido->productos_pedido[i].cod_locker);
                // Rehacer con el nuevo tipo de dato TODO
            }
            if (v_productos_pedido->productos_pedido[i].estado == 5 || v_productos_pedido->productos_pedido[i].estado == 6)
            {
                printf("Fecha de entrega/devolución: %02d/%02d/%d\n", v_productos_pedido->productos_pedido[i].fecha_entrega_devolucion.dia, v_productos_pedido->productos_pedido[i].fecha_entrega_devolucion.mes, v_productos_pedido->productos_pedido[i].fecha_entrega_devolucion.anio);
            }
            printf("\n");
        }
    }
}

//Funcion que lista los pedidos de un cliente marcados en locker
void listar_pedidos_locker_decliente(VectorPedidos *v_pedidos, char *id_cliente)
{
    int i;
    for (i = 0; i < v_pedidos->size; i++)
    {
        if (strcmp(v_pedidos->pedidos[i].id_cliente, id_cliente) == 0 && v_pedidos->pedidos[i].lugar == 2)
        {
            printf("Pedido: %s\n", v_pedidos->pedidos[i].id_pedido);
            printf("Fecha: %02d/%02d/%d\n", v_pedidos->pedidos[i].fecha.dia, v_pedidos->pedidos[i].fecha.mes, v_pedidos->pedidos[i].fecha.anio);
            printf("Cliente: %s\n", v_pedidos->pedidos[i].id_cliente);
            printf("Lugar: locker\n");
            printf("Locker: %s\n", v_pedidos->pedidos[i].id_locker);
            printf("Descuento: %s\n", v_pedidos->pedidos[i].id_descuento);
            printf("\n");
        }
    }
}

//Funcion que comprueba si un producto pertenece a un pedido
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

//FUncion que devuelve un producto pedido que se busca mediante , id del pedido , id del producto ,transportista asignado y estado de enReparto
ProductoPedido *buscar_producto_pedido(VectorProductosPedido *v_productos_pedido, char *id_pedido, char *id_producto, char *id_transportista)
{
    int i;
    for (i = 0; i < v_productos_pedido->size; i++)
    {
        if (strcmp(v_productos_pedido->productos_pedido[i].id_pedido, id_pedido) == 0 && strcmp(v_productos_pedido->productos_pedido[i].id_producto, id_producto) == 0 && strcmp(v_productos_pedido->productos_pedido[i].id_transportista, id_transportista) == 0 && v_productos_pedido->productos_pedido[i].estado == 3)
        {
            return &v_productos_pedido->productos_pedido[i];
        }
    }

    return NULL;
}

//Funcion que dado un id_locker y un n_compartimento devuelve el producto pedido
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

// Funcion para realizar un pedido,
void realizar_pedido(Cliente *cliente, VectorPedidos v_pedidos, VectorProductosPedido v_productos_pedido, VectorLockers v_lockers, VectorCompartimentos v_compartimentos, VectorDescuentos v_descuentos, VectorDescuentosClientes v_descuentos_cliente, VectorProductos v_productos)
{

    // Crear un pedido temporal
    Pedido pedido_temp;
    float importe = 0;
    unsigned num_unidades;
    int i;
    char id_pedido[8];
    unsigned opcion_lugar;
    sprintf(id_pedido, "%07d", atoi(v_pedidos.pedidos[v_pedidos.size - 1].id_pedido) + 1);

    strcpy(pedido_temp.id_pedido, id_pedido);
    // Obtener la fecha actual
    pedido_temp.fecha = obtener_fecha_actual();
    // Copiar el id del cliente
    strcpy(pedido_temp.id_cliente, cliente->id_cliente);

    // Crear un vector de producos pedido temporal e inicializar su tamaño a 0 y su puntero a NULL
    VectorProductosPedido v_productos_pedido_temp;
    v_productos_pedido_temp.size = 0;
    v_productos_pedido_temp.productos_pedido = NULL;

    // Crear un producto pedido temporal
    ProductoPedido producto_pedido_temp;
    strcpy(producto_pedido_temp.id_pedido, id_pedido);

    // Preguntar si desea entrega del pedido a domicilio o en un locker
    do
    {
        printf("1. Domicilio\n");
        printf("2. Locker\n");
        leer_unsigned("Introduce una opcion valida", &opcion_lugar);
    } while (opcion_lugar != 1 && opcion_lugar != 2);

    // Inicializar el lugar del pedido
    pedido_temp.lugar = opcion_lugar;



    // Pedirle al cliente que introduzca el id del producto
    do
    {
        // Listar los productos
        listado_productos();

        char id_producto[8];
        leer_cadena("Introduce el id del producto: ", id_producto, 8);
        // Comprobar que el producto existe
        Producto *producto = buscar_producto_id(&v_productos, id_producto);
        if (producto == NULL)
        {
            printf("Producto no encontrado\n");
        }
        else
        { // Si el producto existe pedirle el numero de unidades
            leer_unsigned("Introduce el numero de unidades: ", &num_unidades);
            if (num_unidades < producto->stock)
            {
                printf("No hay suficiente stock\n");
            }
            else
            { // Si hay suficiente stock rellenar los datos del producto pedido temporal
                // Rellenar los datos de un producto pedido temporal
                strcpy(producto_pedido_temp.id_producto, id_producto);
                producto_pedido_temp.num_unidades = num_unidades;
                producto_pedido_temp.importe = producto->importe * num_unidades;
                producto_pedido_temp.estado = 1;
                strcpy(producto_pedido_temp.id_transportista, " ");
                //SI la entrega es a domicilio
                if (pedido_temp.lugar == 1 ) {
                    strcpy(producto_pedido_temp.id_locker, " ");
                    producto_pedido_temp.cod_locker = 0;
                }else{
                    // Si la entrega es en un locker mostrar los lockers y solicitar que introduzca el id del locker
                    listar_todo_lockers(&v_lockers);
                    char id_locker[11];
                    leer_cadena("Introduce el id del locker: ", id_locker, 11);
                    // Comprobar que el locker existe
                    Locker *locker = buscar_locker_id(&v_lockers, id_locker);
                    if (locker == NULL)
                    {
                        printf("Locker no encontrado\n");
                        continue;
                    }
                    // Comprobar que el locker tiene compartimentos libres
                    if (locker->num_compartimentos_total == locker->num_compartimentos_ocupados)
                    {
                        printf("Locker lleno\n");
                        continue;
                    }
                    // Rellenar los datos del producto pedido temporal
                    strcpy(producto_pedido_temp.id_locker, id_locker);
                    producto_pedido_temp.cod_locker = 0;
                    // Seleccionar un compartimento del locker, asignamdo la informacion al compartimento locker que lo haga de forma automatica , recorriendo el vector de compartimentos


                    for (i = 0; i < v_compartimentos.size; i++)
                    {
                        if (strcmp(v_compartimentos.compartimentos[i].id_locker, id_locker) == 0 && v_compartimentos.compartimentos[i].estado == 0)
                        {
                            strcpy(v_compartimentos.compartimentos[i].id_locker, id_locker);
                            v_compartimentos.compartimentos[i].n_compartimento = v_compartimentos.compartimentos[i].n_compartimento;
                            v_compartimentos.compartimentos[i].cod_locker = 0;
                            v_compartimentos.compartimentos[i].estado = 1;
                            v_compartimentos.compartimentos[i].fecha_ocupacion = obtener_fecha_actual();
                            v_compartimentos.compartimentos[i].fecha_caducidad = crearFecha(0, 0, 0);

                            break;
                        }

                    }


                }
                producto_pedido_temp.fecha_entrega_devolucion = crearFecha(0, 0, 0);
                // suma las fechas para calcular la fecha prevista de entrega
                producto_pedido_temp.fecha_prevista_entrega = crearFecha(producto->entrega + pedido_temp.fecha.dia, pedido_temp.fecha.mes, pedido_temp.fecha.anio);
                // Aumentar el numero de productos en el vector de productos pedido temporal
                v_productos_pedido_temp.size++;

                // Incluir el producto pedido temporal en la ultima posicion del vector de productos pedido temporal y actualizar el importe de ese producto pedido temporal
                // COmprueba que se haya podido realizar la reserva de memoria



                ProductoPedido *temp = (ProductoPedido *)realloc(v_productos_pedido_temp.productos_pedido, v_productos_pedido_temp.size * sizeof(ProductoPedido));
                if (temp == NULL)
                {
                    perror("Error al reservar memoria");
                    return;
                }

                v_productos_pedido_temp.productos_pedido = temp;
                v_productos_pedido_temp.productos_pedido[v_productos_pedido_temp.size - 1] = producto_pedido_temp;
                importe += producto_pedido_temp.importe;

            }

            // Preguntar si quiere añadir otro producto
            char respuesta;
            printf("¿Desea añadir otro producto? (s/n): ");
            leer_caracter("Introduce una opcion valida", &respuesta);
            if (respuesta == 'n' || respuesta == 'N')
            {
                break;
            }
        }
    } while (1); // Se han terminado de añadir productos

    // Mostrar el importe total y  el numero de productos solicitados (size del vector temporal)

    printf("Importe total: %.2f\n", importe);
    printf("Numero de productos: %u\n", v_productos_pedido_temp.size); // Productos diferentes

    // Preguntar si desea aplicar un descuento
    char respuesta;
    printf("¿Desea aplicar un descuento? (s/n): ");
    leer_caracter("Introduce una opcion valida", &respuesta);
    if (respuesta == 's' || respuesta == 'S')
    {
        // Mostrar los descuentos del cliente EN CONCRETO
        mostrar_descuentos_cliente(&v_descuentos_cliente, &v_descuentos, cliente->id_cliente);
        // Pedirle al cliente que introduzca el id del descuento
        char id_descuento[11];
        do
        {
            respuesta = 'n';
            leer_cadena("Introduce el id del descuento: ", id_descuento, 11);
            float aux = importe;
            importe = aplicar_descuento_a_importe(&v_descuentos_cliente, &v_descuentos, cliente->id_cliente, id_descuento, importe);
            if (aux == importe)
            {
                printf("No se ha podido aplicar el descuento\n");
                leer_caracter("¿Desea aplicar otro descuento? (s/n): \n ", &respuesta);
            }
            else
            {
                printf("Descuento aplicado\n");
                // Imprimir un desglose del importe formateado
                printf("Importe sin descuento: %.2f\n", aux);
                printf("Descuento aplicado: %.2f\n", importe);
                // Copiar el id del descuento en el pedido temporal
                strcpy(pedido_temp.id_descuento, id_descuento);
                break;
            }

        } while (respuesta == 's' || respuesta == 'S');
    }
    else
    {
        // Si no se aplica descuento copiar un string vacio en el id del descuento del pedido temporal
        strcpy(pedido_temp.id_descuento, " ");
    }

    // Restar el importe a la cartera del cliente indicando que se está procediendo al pago , en caso de no tener suficiente saldo mostrar un mensaje
    if (cliente->cartera < importe)
    {
        printf("No tiene suficiente saldo\n");
        printf("Pedido cancelado \n");
    }
    else
    {
        //Incluir el pedido temporal en el vector de pedidos e incrementar el tamaño del vector
        Pedido *temp = (Pedido *)realloc(v_pedidos.pedidos, (v_pedidos.size + 1) * sizeof(Pedido));
        if (temp == NULL)
        {
            perror("Error al reservar memoria");
            return;
        }
        v_pedidos.pedidos = temp;
        v_pedidos.pedidos[v_pedidos.size] = pedido_temp;
        v_pedidos.size++;

        //Incluir el vector de productos pedido temporal en el vector de productos pedido e incrementar el tamaño del vector
        ProductoPedido *temp2 = (ProductoPedido *)realloc(v_productos_pedido.productos_pedido, (v_productos_pedido.size + v_productos_pedido_temp.size) * sizeof(ProductoPedido));
        if (temp2 == NULL)
        {
            perror("Error al reservar memoria");
            return;
        }
        v_productos_pedido.productos_pedido = temp2;

        for (i = 0; i < v_productos_pedido_temp.size; i++)
        {
            v_productos_pedido.productos_pedido[v_productos_pedido.size + i] = v_productos_pedido_temp.productos_pedido[i];
            //Actualiza el stock de los productos
            Producto *producto = buscar_producto_id(&v_productos, v_productos_pedido_temp.productos_pedido[i].id_producto);
            producto->stock -= v_productos_pedido_temp.productos_pedido[i].num_unidades;
        }
        v_productos_pedido.size += v_productos_pedido_temp.size;
        // Actualizar la cartera del cliente
        cliente->cartera -= importe;
        printf("Se ha procedido al pago\n");

    }
}

