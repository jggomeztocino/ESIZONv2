#include "stdio.h"
#include <string.h>
#include <malloc.h>
#include "stdlib.h"
#include "devoluciones.h"

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
            strcpy(v_productos_pedido->productos_pedido[v_productos_pedido->size].cod_locker, token);
        }
        else
        {
            strcpy(v_productos_pedido->productos_pedido[v_productos_pedido->size].cod_locker, " ");
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
        fprintf(f, "%s-%s-%d-%02d/%02d/%d-%.2f-%d-%s-%s-%s-%02d/%02d/%d\n", v_productos_pedido->productos_pedido[i].id_pedido, v_productos_pedido->productos_pedido[i].id_producto, v_productos_pedido->productos_pedido[i].num_unidades, v_productos_pedido->productos_pedido[i].fecha_prevista_entrega.dia, v_productos_pedido->productos_pedido[i].fecha_prevista_entrega.mes, v_productos_pedido->productos_pedido[i].fecha_prevista_entrega.anio, v_productos_pedido->productos_pedido[i].importe, v_productos_pedido->productos_pedido[i].estado, v_productos_pedido->productos_pedido[i].id_transportista, v_productos_pedido->productos_pedido[i].id_locker, v_productos_pedido->productos_pedido[i].cod_locker, v_productos_pedido->productos_pedido[i].fecha_entrega_devolucion.dia, v_productos_pedido->productos_pedido[i].fecha_entrega_devolucion.mes, v_productos_pedido->productos_pedido[i].fecha_entrega_devolucion.anio);
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
                printf("Código locker: %s\n", v_productos_pedido->productos_pedido[i].cod_locker);
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
// //Buscar un producto pedido en el compartimento
//buscar_producto_pedido_locker(&v_productos_pedido, locker->id_locker,compartimento->n_compartimento);

ProductoPedido *buscar_producto_pedido_locker(VectorProductosPedido *v_productos_pedido, char *id_locker, unsigned n_compartimento)
{
    int i;
    for (i = 0; i < v_productos_pedido->size; i++)
    {
        if (strcmp(v_productos_pedido->productos_pedido[i].id_locker, id_locker) == 0 && v_productos_pedido->productos_pedido[i].estado == 4)
        {
            return &v_productos_pedido->productos_pedido[i];
        }
    }

    return NULL;
}