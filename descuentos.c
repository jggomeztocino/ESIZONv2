#include "descuentos.h"
#include "utilidades.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

/*
    Los campos, separados por guiones, son los que se describen a continuación:
    o Identificador del código promocional o cheque regalo (Id_cod), 10 caracteres máximo.
    o Descripción del descuento (Descrip), 50 caracteres máximo.
    o Tipo de descuento (Tipo): «codpro» (código promocional) o «cheqreg» (cheque regalo)
    o Estado (Estado): «activo» o «inactivo»
    o Importe del descuento en euros (Importe)
    o Aplicabilidad (Aplicable): «todos» (si es aplicable a todos los productos) o «esizon» (si sólo es aplicable a los gestionados por ESIZON.

    Ejemplo de línea de descuento:
    black001-Black Friday-codpro-activo-10-esizon
    che001-cheque regalo nivel 1-cheqreg-activo-5-todos

    Es decir:
    id_codigo-descripcion-tipo-estado-importe-aplicable

    Primero deberá inicializar el puntero de clientes para alojar un solo cliente y su tamaño a 0.
    Luego, abrir el archivo en modo lectura y leer cada línea, separando los campos por el carácter '-'.
    Si el vector, definido en el puntero de clientes, no tiene espacio suficiente, deberá incrementar su tamaño en 1 unidad.
 */



void cargar_descuentos(VectorDescuentos* v_descuentos)
{
    FILE* f = fopen("../data/Descuentos.txt", "r");
    if (f == NULL) {
        perror("\nError al abrir el archivo de descuentos\n");
        return;
    }
    v_descuentos->descuentos = (Descuento*)malloc(sizeof(Descuento));
    v_descuentos->n_descuentos = 0;
    while (fscanf(f, "%10[^-]-%50[^-]-%7[^-]-%7[^-]-%f-%7[^-]\n",
                  v_descuentos->descuentos[v_descuentos->n_descuentos].id_codigo,
                  v_descuentos->descuentos[v_descuentos->n_descuentos].descripcion,
                  v_descuentos->descuentos[v_descuentos->n_descuentos].tipo,
                  v_descuentos->descuentos[v_descuentos->n_descuentos].estado,
                  &v_descuentos->descuentos[v_descuentos->n_descuentos].importe,
                  v_descuentos->descuentos[v_descuentos->n_descuentos].aplicable) == 6) {
        v_descuentos->n_descuentos++;
        Descuento* temp = (Descuento*)realloc(v_descuentos->descuentos, (v_descuentos->n_descuentos + 1) * sizeof(Descuento));
        if(temp == NULL) {
            perror("\nError al reservar memoria\n");
        }
        v_descuentos->descuentos=temp;
    }
    fclose(f);
}

void guardar_descuentos(VectorDescuentos* v_descuentos)
{
    FILE* f = fopen("../data/Descuentos.txt", "w");
    if (f == NULL) {
        return;
    }
    int i;
    for (i = 0; i < v_descuentos->n_descuentos; i++) {
        fprintf(f, "%s-%s-%s-%s-%.2f-%s\n",
                v_descuentos->descuentos[i].id_codigo,
                v_descuentos->descuentos[i].descripcion,
                v_descuentos->descuentos[i].tipo,
                v_descuentos->descuentos[i].estado,
                v_descuentos->descuentos[i].importe,
                v_descuentos->descuentos[i].aplicable);
    }
    fclose(f);
    free(v_descuentos->descuentos);
    v_descuentos->n_descuentos = 0;
}

void cargar_descuentos_clientes(VectorDescuentosClientes* v_descuentosclientes)
{
    FILE* f = fopen("../data/DescuentosClientes.txt", "r");
    if (f == NULL) {
        perror("\nError al abrir el archivo descuentos cliente\n");
        return;
    }
    v_descuentosclientes->descuentosClientes = (DescuentoCliente*)malloc(sizeof(DescuentoCliente));
    v_descuentosclientes->n_descuentosclientes = 0;
    while (fscanf(f, "%7[^-]-%10[^-]-%d/%d/%d-%d/%d/%d-%d\n",
                  v_descuentosclientes->descuentosClientes[v_descuentosclientes->n_descuentosclientes].id_cliente,
                  v_descuentosclientes->descuentosClientes[v_descuentosclientes->n_descuentosclientes].id_codigo,
                  &v_descuentosclientes->descuentosClientes[v_descuentosclientes->n_descuentosclientes].fecha_asignacion.dia,
                  &v_descuentosclientes->descuentosClientes[v_descuentosclientes->n_descuentosclientes].fecha_asignacion.mes,
                  &v_descuentosclientes->descuentosClientes[v_descuentosclientes->n_descuentosclientes].fecha_asignacion.anio,
                  &v_descuentosclientes->descuentosClientes[v_descuentosclientes->n_descuentosclientes].fecha_caducidad.dia,
                  &v_descuentosclientes->descuentosClientes[v_descuentosclientes->n_descuentosclientes].fecha_caducidad.mes,
                  &v_descuentosclientes->descuentosClientes[v_descuentosclientes->n_descuentosclientes].fecha_caducidad.anio,
                  &v_descuentosclientes->descuentosClientes[v_descuentosclientes->n_descuentosclientes].estado) == 9) {
        v_descuentosclientes->n_descuentosclientes++;
        DescuentoCliente* temp = (DescuentoCliente*)realloc(v_descuentosclientes->descuentosClientes, (v_descuentosclientes->n_descuentosclientes + 1) * sizeof(DescuentoCliente));
        if(temp == NULL) {
            perror("\nError al reservar memoria\n");
            return;
        }
        v_descuentosclientes->descuentosClientes = temp;
    }
    fclose(f);
}


void guardar_descuentos_clientes(VectorDescuentosClientes* v_descuentosclientes)
{
    FILE* f = fopen("../data/DescuentosClientes.txt", "w");
    if (f == NULL) {
        return;
    }
    int i;
    for (i = 0; i < v_descuentosclientes->n_descuentosclientes; i++) {
        fprintf(f, "%s-%s-%d/%d/%d-%d/%d/%d\n",
                v_descuentosclientes->descuentosClientes[i].id_cliente,
                v_descuentosclientes->descuentosClientes[i].id_codigo,
                v_descuentosclientes->descuentosClientes[i].fecha_asignacion.dia,
                v_descuentosclientes->descuentosClientes[i].fecha_asignacion.mes,
                v_descuentosclientes->descuentosClientes[i].fecha_asignacion.anio,
                v_descuentosclientes->descuentosClientes[i].fecha_caducidad.dia,
                v_descuentosclientes->descuentosClientes[i].fecha_caducidad.mes,
                v_descuentosclientes->descuentosClientes[i].fecha_caducidad.anio);
    }
    fclose(f);
    free(v_descuentosclientes->descuentosClientes);
    v_descuentosclientes->n_descuentosclientes = 0;
}

void listar_descuento(Descuento* descuento)
{
    printf("--------------------------------------\n");
    printf("Código: %s\n", descuento->id_codigo);
    printf("Descripción: %s\n", descuento->descripcion);
    printf("Tipo: %s\n", descuento->tipo);
    printf("Importe: %.2f\n", descuento->importe);
    printf("Aplicable: %s\n", descuento->aplicable);
    printf("--------------------------------------\n");
}

void listar_descuentos(VectorDescuentos* v_descuentos)
{
    int i;
    for (i = 0; i < v_descuentos->n_descuentos; i++) {
        listar_descuento(&v_descuentos->descuentos[i]);
    }
}

void listar_descuento_cliente(DescuentoCliente* descuento_cliente, Descuento* descuento)
{
    // Descuento: id_codigo, descripcion, tipo, importe, aplicable
    // DescuentoCliente: fecha_asignacion, fecha_caducidad, estado
    printf("========================================\n");
    listar_descuento(descuento);
    printf("Fecha asignación: %02d/%02d/%d\n", descuento_cliente->fecha_asignacion.dia, descuento_cliente->fecha_asignacion.mes, descuento_cliente->fecha_asignacion.anio);
    printf("Fecha caducidad: %02d/%02d/%d\n", descuento_cliente->fecha_caducidad.dia, descuento_cliente->fecha_caducidad.mes, descuento_cliente->fecha_caducidad.anio);
    printf("Estado: %s\n", descuento_cliente->estado ? "Aplicado" : "No aplicado"); // "Aplicado" si el estado es 1 y "No aplicado" si el estado es 0.
}

unsigned listar_descuentos_cliente(VectorDescuentosClientes* v_descuentosclientes, VectorDescuentos* v_descuentos, char* id_cliente)
{
    unsigned n_descuentos = 0;
    int i;
    for (i = 0; i < v_descuentosclientes->n_descuentosclientes; i++) {
        if (strcmp(v_descuentosclientes->descuentosClientes[i].id_cliente, id_cliente) == 0) {
            int j;
            for (j = 0; j < v_descuentos->n_descuentos; j++) {
                if (strcmp(v_descuentosclientes->descuentosClientes[i].id_codigo, v_descuentos->descuentos[j].id_codigo) == 0) {
                    n_descuentos++;
                    listar_descuento_cliente(&v_descuentosclientes->descuentosClientes[i], &v_descuentos->descuentos[j]);
                }
            }
            printf("========================================\n");
        }
    }
    return n_descuentos;
}


Descuento* buscar_descuento_id(VectorDescuentos* v_descuentos, char* id_codigo)
{
    int i;
    for (i = 0; i < v_descuentos->n_descuentos; i++) {
        if (strcmp(v_descuentos->descuentos[i].id_codigo, id_codigo) == 0) {
            return &v_descuentos->descuentos[i];
        }
    }
    return NULL;
}


DescuentoCliente* buscar_descuentocliente(VectorDescuentosClientes* v_descuentosclientes, char* id_cliente, char* id_codigo){

    int i;
    for (i = 0; i < v_descuentosclientes->n_descuentosclientes; i++) {
        if (strcmp(v_descuentosclientes->descuentosClientes[i].id_cliente, id_cliente) == 0 && strcmp(v_descuentosclientes->descuentosClientes[i].id_codigo, id_codigo) == 0) {
            return &v_descuentosclientes->descuentosClientes[i];
        }
    }
    return NULL;
}


/*float aplicar_descuento_a_importe(VectorDescuentosClientes *v_descuentos_cliente, VectorDescuentos *v_descuentos, char *id_cliente, char *id_descuento, float importe)
{

    DescuentoCliente *descuento_cliente = obtener_descuento_cliente(v_descuentos_cliente, id_cliente, id_descuento);
    if (descuento_cliente == NULL)
    {
        printf("Descuento no encontrado\n");
        return importe;
    }
    Descuento *descuento = obtener_descuento(v_descuentos, id_descuento);
    if (descuento == NULL)
    {
        printf("Descuento no encontrado\n");
        return importe;
    }
    if (strcmp(descuento->estado, "inactivo") == 0)
    {
        printf("Descuento inactivo\n");
        return importe;
    }
    // Comprobar si se ha utilizado ya el descuento o no
    if (descuento_cliente->estado == 1)
    {
        printf("Descuento ya utilizado\n");
        return importe;
    }
    Fecha fecha_actual;
    fecha_actual = obtener_fecha_actual();
    if (comparar_fechas(fecha_actual, descuento_cliente->fecha_caducidad) > 0)
    {
        printf("Descuento caducado\n");
        return importe;
    }
    importe -= descuento->importe;
    descuento_cliente->estado = 1;
    if (importe < 0)
        importe = 0;
    return importe;
}*/

int descuento_valido(DescuentoCliente *descuento_cliente, char* id_cliente)
{
    if (descuento_cliente == NULL)
    {
        return 0;
    }
    if(strcmp(descuento_cliente->id_cliente, id_cliente) != 0)
    {
        return 0;
    }
    if (descuento_cliente->estado == 1)
    {
        return 0;
    }
    Fecha fecha_actual;
    fecha_actual = obtener_fecha_actual();
    if (comparar_fechas(fecha_actual, descuento_cliente->fecha_caducidad) > 0)
    {
        return 0;
    }
    return 1;
}

Descuento* modificar_descuento(Descuento* descuento)
{
    char descripcion[51];
    char estado[8];
    float importe;
    char aplicable[8];
    unsigned opcion = 0;

    do{
        printf("1. Descripción: %s\n", descuento->descripcion);
        printf("2. Estado: %s\n", descuento->estado);
        printf("3. Importe: %.2f\n", descuento->importe);
        printf("4. Aplicable: %s\n", descuento->aplicable);
        printf("5. Salir\n");

        leer_unsigned("Introduce una opción: ", &opcion);
        switch(opcion){
            case 1:
                leer_cadena("Introduce la descripción: ", descripcion, 51);
                break;
            case 2:
                leer_cadena("Introduce el estado: ", estado, 8);
                break;
            case 3:
                leer_real("Introduce el importe: ", &importe);
                break;
            case 4:
                leer_cadena("Introduce el aplicable: ", aplicable, 8);
                break;
            case 5:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no válida\n");
                break;
        }

    }while(opcion != 5);

    strcpy(descuento->descripcion, descripcion);
    strcpy(descuento->estado, estado);
    descuento->importe = importe;
    strcpy(descuento->aplicable, aplicable);

    return descuento;
}

void listar_clientes_descuento_usado(VectorClientes* v_clientes, VectorDescuentosClientes* v_descuentosclientes, char* id_codigo)
{
    Cliente* cliente;

    int i;
    for (i = 0; i < v_descuentosclientes->n_descuentosclientes; i++) {
        if (strcmp(v_descuentosclientes->descuentosClientes[i].id_codigo, id_codigo) == 0 && v_descuentosclientes->descuentosClientes[i].estado == 1) {
            cliente = buscar_cliente_por_id(v_clientes, v_descuentosclientes->descuentosClientes[i].id_cliente);
            if (cliente != NULL) {
                listar_cliente(cliente);
            }
        }
    }
}

void listar_clientes_descuento(VectorClientes* v_clientes, VectorDescuentosClientes* v_descuentosclientes, char* id_codigo)
{
    Cliente* cliente;

    int i;
    for (i = 0; i < v_descuentosclientes->n_descuentosclientes; i++) {
        if (strcmp(v_descuentosclientes->descuentosClientes[i].id_codigo, id_codigo) == 0) {
            cliente = buscar_cliente_por_id(v_clientes, v_descuentosclientes->descuentosClientes[i].id_cliente);
            if (cliente != NULL) {
                listar_cliente(cliente);
            }
        }
    }
}

Descuento* alta_descuento(VectorDescuentos* v_descuentos, VectorDescuentosClientes* v_descuentoscliente, VectorClientes* v_clientes)
{
    /*
     * 2. Alta de descuento
    a. En este caso, el ID es el propio código del descuento, por lo que el sistema solicitará al administrador que introduzca el ID.
    b. El sistema solicitará al administrador que introduzca la descripción del descuento.
    c. El sistema solicitará al administrador que introduzca el tipo de descuento (promocional [codpro] o cheque regalo [cheqreg]).
    d. El sistema solicitará al administrador que indique el estado del descuento (activo o inactivo).
    e. El sistema solicitará al administrador que introduzca el importe del descuento.
    f. El sistema solicitará al administrador que introduzca aplicable a todos los clientes (S/N) (Sí: Todos, No: ESIZON).
    Nota: En el caso de que el descuento sea un código promocional y esté indicado para todos, se asignará a todos los clientes.
     */
    char id_codigo[11];
    char descripcion[51];
    char tipo[8];
    char estado[9];
    float importe;
    char aplicable[8];

    leer_cadena("Introduce el ID del descuento: ", id_codigo, 11);
    leer_cadena("Introduce la descripción del descuento: ", descripcion, 51);
    printf("Selecciona el tipo de descuento:\n");
    printf("1. Código promocional\n");
    printf("2. Cheque regalo\n");
    unsigned opcion;
    leer_unsigned("Introduce una opción: ", &opcion);
    do{
        switch(opcion) {
            case 1:
                strcpy(tipo, "codpro");
                break;
            case 2:
                strcpy(tipo, "cheqreg");
                break;
            default:
                printf("Opción no válida\n");
                break;
        }
    }while(opcion != 1 && opcion != 2);
    printf("Selecciona el estado del descuento:\n");
    printf("1. Activo\n");
    printf("2. Inactivo\n");
    leer_unsigned("Introduce una opción: ", &opcion);
    do {
        switch (opcion) {
            case 1:
                strcpy(estado, "activo");
                break;
            case 2:
                strcpy(estado, "inactivo");
                break;
            default:
                printf("Opción no válida\n");
                break;
        }
    } while (opcion != 1 && opcion != 2);
    leer_real("Introduce el importe del descuento: ", &importe);
    printf("¿Es aplicable a todos los clientes?\n");
    printf("1. Sí\n");
    printf("2. No\n");
    leer_unsigned("Introduce una opción: ", &opcion);
    do {
        switch (opcion) {
            case 1:
                strcpy(aplicable, "todos");
                break;
            case 2:
                strcpy(aplicable, "esizon");
                break;
            default:
                printf("Opción no válida\n");
                break;
        }
    } while (opcion != 1 && opcion != 2);

    // Creamos una zona de memoria temp para el nuevo descuento con el tamaño incrementado en 1
    Descuento* temp_descuento = (Descuento*)malloc((v_descuentos->n_descuentos + 1) * sizeof(Descuento));
    if (temp_descuento == NULL) {
        perror("\nError al reservar memoria\n");
        return NULL;
    }
    v_descuentos->descuentos = temp_descuento;

    // Inicializamos la nueva posición
    strcpy(v_descuentos->descuentos[v_descuentos->n_descuentos].id_codigo, id_codigo);
    strcpy(v_descuentos->descuentos[v_descuentos->n_descuentos].descripcion, descripcion);
    strcpy(v_descuentos->descuentos[v_descuentos->n_descuentos].tipo, tipo);
    strcpy(v_descuentos->descuentos[v_descuentos->n_descuentos].estado, estado);
    v_descuentos->descuentos[v_descuentos->n_descuentos].importe = importe;
    strcpy(v_descuentos->descuentos[v_descuentos->n_descuentos].aplicable, aplicable);

    // Incrementamos el tamaño del vector
    v_descuentos->n_descuentos++;

    if(strcmp(tipo, "codpro") == 0 && strcmp(aplicable, "todos") == 0)
    {
        Fecha fecha_actual = obtener_fecha_actual();
        Fecha fecha_caducidad = fecha_actual;
        fecha_caducidad.mes += 1;
        DescuentoCliente* temp_descuentocliente = (DescuentoCliente*)malloc((v_descuentoscliente->n_descuentosclientes + v_clientes->size) * sizeof(DescuentoCliente));
        if(temp_descuentocliente == NULL)
        {
            perror("\nError al reservar memoria\n");
            return NULL;
        }
        v_descuentoscliente->descuentosClientes = temp_descuentocliente;
        int i;
        for (i = 0; i < v_clientes->size; i++) {
            strcpy(v_descuentoscliente->descuentosClientes[v_descuentoscliente->n_descuentosclientes].id_cliente, v_clientes->clientes[i].id_cliente);
            strcpy(v_descuentoscliente->descuentosClientes[v_descuentoscliente->n_descuentosclientes].id_codigo, id_codigo);
            v_descuentoscliente->descuentosClientes[v_descuentoscliente->n_descuentosclientes].fecha_asignacion = fecha_actual;
            v_descuentoscliente->descuentosClientes[v_descuentoscliente->n_descuentosclientes].fecha_caducidad = fecha_caducidad;
            v_descuentoscliente->descuentosClientes[v_descuentoscliente->n_descuentosclientes].estado = 0;
        }
        v_descuentoscliente->n_descuentosclientes += v_clientes->size;
    }

    return &v_descuentos->descuentos[v_descuentos->n_descuentos - 1];
}

void baja_descuentocliente(VectorDescuentosClientes* v_descuentoscliente, char* id_cliente, char* id_codigo)
{
    int i;
    for (i = 0; i < v_descuentoscliente->n_descuentosclientes; i++) {
        if (strcmp(v_descuentoscliente->descuentosClientes[i].id_cliente, id_cliente) == 0 && strcmp(v_descuentoscliente->descuentosClientes[i].id_codigo, id_codigo) == 0) {
            break;
        }
    }
    if(i == v_descuentoscliente->n_descuentosclientes)
    {
        printf("Descuento no encontrado\n");
        return;
    }
    for (; i < v_descuentoscliente->n_descuentosclientes - 1; i++) {
        v_descuentoscliente->descuentosClientes[i] = v_descuentoscliente->descuentosClientes[i + 1];
    }
    v_descuentoscliente->n_descuentosclientes--;
    DescuentoCliente* temp_descuentocliente = (DescuentoCliente*)malloc(v_descuentoscliente->n_descuentosclientes * sizeof(DescuentoCliente));
    if(temp_descuentocliente == NULL) {
        free(v_descuentoscliente->descuentosClientes);
        perror("\nError al reservar memoria\n");
    }
    v_descuentoscliente->descuentosClientes = temp_descuentocliente;
}

void baja_descuento(char* id_descuento, VectorDescuentos* v_descuentos, VectorDescuentosClientes* v_descuentoscliente)
{
    int i;
    // Dar de baja a todos los descuentos de clientes asociados a este descuento
    for (i = 0; i < v_descuentoscliente->n_descuentosclientes; i++) {
        if (strcmp(v_descuentoscliente->descuentosClientes[i].id_codigo, id_descuento) == 0) {
            baja_descuentocliente(v_descuentoscliente, v_descuentoscliente->descuentosClientes[i].id_cliente, id_descuento);
        }
    }

    // Eliminar el descuento
    for (i = 0; i < v_descuentos->n_descuentos; i++) {
        if (strcmp(v_descuentos->descuentos[i].id_codigo, id_descuento) == 0) {
            break;
        }
    }
    if(i == v_descuentos->n_descuentos)
    {
        printf("Descuento no encontrado\n");
        return;
    }
    for (; i < v_descuentos->n_descuentos - 1; i++) {
        v_descuentos->descuentos[i] = v_descuentos->descuentos[i + 1];
    }
    v_descuentos->n_descuentos--;
    Descuento* temp_descuento = (Descuento*)malloc(v_descuentos->n_descuentos * sizeof(Descuento));
    if(temp_descuento == NULL) {
        free(v_descuentos->descuentos);
        perror("\nError al reservar memoria\n");
    }
    v_descuentos->descuentos = temp_descuento;
}

void asignar_descuento_cliente(char* id_descuento, char* id_cliente, VectorDescuentosClientes *v_descuentos_cliente){
    Fecha fecha_actual = obtener_fecha_actual();
    Fecha fecha_caducidad = fecha_actual;
    fecha_caducidad.mes += 1;
    DescuentoCliente* temp_descuentocliente = (DescuentoCliente*)malloc((v_descuentos_cliente->n_descuentosclientes + 1) * sizeof(DescuentoCliente));
    if(temp_descuentocliente == NULL)
    {
        perror("\nError al reservar memoria\n");
        return;
    }
    v_descuentos_cliente->descuentosClientes = temp_descuentocliente;
    strcpy(v_descuentos_cliente->descuentosClientes[v_descuentos_cliente->n_descuentosclientes].id_cliente, id_cliente);
    strcpy(v_descuentos_cliente->descuentosClientes[v_descuentos_cliente->n_descuentosclientes].id_codigo, id_descuento);
    v_descuentos_cliente->descuentosClientes[v_descuentos_cliente->n_descuentosclientes].fecha_asignacion = fecha_actual;
    v_descuentos_cliente->descuentosClientes[v_descuentos_cliente->n_descuentosclientes].fecha_caducidad = fecha_caducidad;
    v_descuentos_cliente->descuentosClientes[v_descuentos_cliente->n_descuentosclientes].estado = 0;
    v_descuentos_cliente->n_descuentosclientes++;
}