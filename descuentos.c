#include "descuentos.h"
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

//Ejemplo:
//black001-Black Friday-codpro-activo-10-esizon
//che001-cheque regalo nivel 1-cheqreg-activo-5-todos
void cargar_descuentos(VectorDescuentos* v_descuentos)
{
    FILE* f = fopen("../data/Descuentos.txt", "r");
    if (f == NULL) {
        perror("\nError al abrir el archivo\n");
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
        v_descuentos->descuentos = (Descuento*)realloc(v_descuentos->descuentos, (v_descuentos->n_descuentos + 1) * sizeof(Descuento));
        if(v_descuentos->descuentos == NULL) {
            free(v_descuentos->descuentos);
            perror("\nError al reservar memoria\n");
        }
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

//Ejemplo:
//0000001-black001-25/01/2024-27/03/2024-0
//0000002-che001-01/02/2024-01/06/2024-0
void cargar_descuentos_clientes(VectorDescuentosClientes* v_descuentosclientes)
{
    FILE* f = fopen("../data/descuentos_clientes.txt", "r");
    if (f == NULL) {
        perror("\nError al abrir el archivo\n");
        return;
    }
    v_descuentosclientes->descuentosClientes = (DescuentoCliente*)malloc(sizeof(DescuentoCliente));
    v_descuentosclientes->n_descuentosclientes = 0;
    while (fscanf(f, "%9[^-]-%10[^-]-%d-%d-%d-%d-%d-%d\n",
                  v_descuentosclientes->descuentosClientes[v_descuentosclientes->n_descuentosclientes].id_cliente,
                  v_descuentosclientes->descuentosClientes[v_descuentosclientes->n_descuentosclientes].id_codigo,
                  &v_descuentosclientes->descuentosClientes[v_descuentosclientes->n_descuentosclientes].fecha_asignacion.dia,
                  &v_descuentosclientes->descuentosClientes[v_descuentosclientes->n_descuentosclientes].fecha_asignacion.mes,
                  &v_descuentosclientes->descuentosClientes[v_descuentosclientes->n_descuentosclientes].fecha_asignacion.anio,
                  &v_descuentosclientes->descuentosClientes[v_descuentosclientes->n_descuentosclientes].fecha_caducidad.dia,
                  &v_descuentosclientes->descuentosClientes[v_descuentosclientes->n_descuentosclientes].fecha_caducidad.mes,
                  &v_descuentosclientes->descuentosClientes[v_descuentosclientes->n_descuentosclientes].fecha_caducidad.anio) == 8) {
        v_descuentosclientes->n_descuentosclientes++;
        v_descuentosclientes->descuentosClientes = (DescuentoCliente*)realloc(v_descuentosclientes->descuentosClientes, (v_descuentosclientes->n_descuentosclientes + 1) * sizeof(DescuentoCliente));
        if(v_descuentosclientes->descuentosClientes == NULL) {
            free(v_descuentosclientes->descuentosClientes);
            perror("\nError al reservar memoria\n");
        }
    }
    fclose(f);
}

void guardar_descuentos_clientes(VectorDescuentosClientes* v_descuentosclientes)
{
    FILE* f = fopen("../data/descuentos_clientes.txt", "w");
    if (f == NULL) {
        return;
    }
    int i;
    for (i = 0; i < v_descuentosclientes->n_descuentosclientes; i++) {
        fprintf(f, "%s-%s-%d-%d-%d-%d-%d-%d\n",
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

/*
 * Muestra los descuentos disponibles para un cliente.
 * @param v_descuentosclientes Vector de descuentos de clientes.
 * @param v_descuentos Vector de descuentos.
 * @param id_cliente Identificador del cliente.
 * @return void
 */
void mostrar_descuentos_cliente(VectorDescuentosClientes* v_descuentosclientes, VectorDescuentos* v_descuentos, char* id_cliente)
{
int i;
    for (i = 0; i < v_descuentosclientes->n_descuentosclientes; i++) {
        if (strcmp(v_descuentosclientes->descuentosClientes[i].id_cliente, id_cliente) == 0) {
            int j;
            for (j = 0; j < v_descuentos->n_descuentos; j++) {
                if (strcmp(v_descuentosclientes->descuentosClientes[i].id_codigo, v_descuentos->descuentos[j].id_codigo) == 0) {
                    printf("========================================\n");
                    printf("Código: %s\n", v_descuentos->descuentos[j].id_codigo);
                    printf("Descuento: %s\n", v_descuentos->descuentos[j].descripcion);
                    printf("Tipo: %s\n", v_descuentos->descuentos[j].tipo);
                    printf("Estado: %s\n", v_descuentos->descuentos[j].estado);
                    printf("Importe: %.2f\n", v_descuentos->descuentos[j].importe);
                    printf("Aplicable: %s\n", v_descuentos->descuentos[j].aplicable);
                    printf("Fecha asignación: %02d/%02d/%d\n", v_descuentosclientes->descuentosClientes[i].fecha_asignacion.dia, v_descuentosclientes->descuentosClientes[i].fecha_asignacion.mes, v_descuentosclientes->descuentosClientes[i].fecha_asignacion.anio);
                    printf("Fecha caducidad: %02d/%02d/%d\n", v_descuentosclientes->descuentosClientes[i].fecha_caducidad.dia, v_descuentosclientes->descuentosClientes[i].fecha_caducidad.mes, v_descuentosclientes->descuentosClientes[i].fecha_caducidad.anio);
                    printf("Estado: %s\n", v_descuentosclientes->descuentosClientes[i].estado ? "Aplicado" : "No aplicado"); // "Aplicado" si el estado es 1 y "No aplicado" si el estado es 0.
                }
            }
            printf("========================================\n");
        }
    }
}

/*
 * Devuelve un descuento a partir de su id.
 * @param v_descuentos Vector de descuentos.
 * @param id_codigo Identificador del descuento.
 * @return Descuento* Puntero al descuento.
 */
Descuento* obtener_descuento(VectorDescuentos* v_descuentos, char* id_codigo)
{
    int i;
    for (i = 0; i < v_descuentos->n_descuentos; i++) {
        if (strcmp(v_descuentos->descuentos[i].id_codigo, id_codigo) == 0) {
            return &v_descuentos->descuentos[i];
        }
    }
    return NULL;
}
DescuentoCliente * obtener_descuento_cliente(VectorDescuentosClientes* v_descuentosclientes, char* id_cliente, char* id_codigo){

    int i;
    for (i = 0; i < v_descuentosclientes->n_descuentosclientes; i++) {
        if (strcmp(v_descuentosclientes->descuentosClientes[i].id_cliente, id_cliente) == 0 && strcmp(v_descuentosclientes->descuentosClientes[i].id_codigo, id_codigo) == 0) {
            return &v_descuentosclientes->descuentosClientes[i];
        }
    }
    return NULL;
}
