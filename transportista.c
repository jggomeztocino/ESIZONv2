#include "stdio.h"
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#include "transportista.h"
//Ejemplo:
//0001-Rafael Guitierrez- rafael@gutitrans.com-rf001-GutiTrans-Cádiz
//0002-Pepe Tinoco-pepe@itranspo.com-pp001-TransPo-Cádiz
void cargar_transportistas(VectorTransportistas* v_transportistas) {
    // Abrir archivo de transportistas para lectura
    FILE* f = fopen("../data/Transportistas.txt", "r");
    if (f == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    // Inicializar la memoria para almacenar los transportistas
    v_transportistas->transportistas = (Transportista*)malloc(sizeof(Transportista));
    if (v_transportistas->transportistas == NULL) {
        perror("Error al reservar memoria inicial");
        fclose(f);
        return;
    }
    v_transportistas->size = 0;

    Transportista* temp;
    unsigned n_transportistas_actual = 0;

    // Leer los datos de los transportistas del archivo
    while (fscanf(f, "%4[^-]-%20[^-]-%30[^-]-%15[^-]-%20[^-]-%20[^-]\n",
                  v_transportistas->transportistas[n_transportistas_actual].id_transportista,
                  v_transportistas->transportistas[n_transportistas_actual].nombre,
                  v_transportistas->transportistas[n_transportistas_actual].email,
                  v_transportistas->transportistas[n_transportistas_actual].contrasena,
                  v_transportistas->transportistas[n_transportistas_actual].nombre_empresa,
                  v_transportistas->transportistas[n_transportistas_actual].ciudad) == 6) {

        n_transportistas_actual++;
        temp = (Transportista*)realloc(v_transportistas->transportistas, (n_transportistas_actual + 1) * sizeof(Transportista));
        if (temp == NULL) {
            perror("Error al reservar memoria durante la lectura");
            free(v_transportistas->transportistas);
            fclose(f);
            return;
        }
        v_transportistas->transportistas = temp;
    }

    // Actualizar la cantidad de transportistas después de la lectura completa
    v_transportistas->size = n_transportistas_actual;
    fclose(f);
}

void guardar_transportistas(VectorTransportistas* v_transportistas)
{
    FILE* f = fopen("../data/Transportistas.txt", "w");
    if (f == NULL) {
        return;
    }
    int i;
    for (i = 0; i < v_transportistas->size; i++) {
        fprintf(f, "%s-%s-%s-%s-%s-%s\n",
                v_transportistas->transportistas[i].id_transportista,
                v_transportistas->transportistas[i].nombre,
                v_transportistas->transportistas[i].email,
                v_transportistas->transportistas[i].contrasena,
                v_transportistas->transportistas[i].nombre_empresa,
                v_transportistas->transportistas[i].ciudad);
    }
    fclose(f);
    free(v_transportistas->transportistas);
    v_transportistas->size = 0;
}

Transportista* buscar_transportista_id(VectorTransportistas* v_transportistas, char* id_transportista)
{
    int i;
    for (i = 0; i < v_transportistas->size; i++) {
        if (strcmp(v_transportistas->transportistas[i].id_transportista, id_transportista) == 0) {
            return &v_transportistas->transportistas[i];
        }
    }
    return NULL;
}

Transportista* buscar_transportista_email(VectorTransportistas* v_transportistas, char* email)
{
    int i;
    for (i = 0; i < v_transportistas->size; i++) {
        if (strcmp(v_transportistas->transportistas[i].email, email) == 0) {
            return &v_transportistas->transportistas[i];
        }
    }
    return NULL;
}

void listar_transportista(Transportista* transportista)
{
    printf(
        "---------------------------\n"
        "Nombre:     %s\n"
        "Email:  %s\n"
        "Empresa:  %s\n"
        "Ciudad:  %s\n",
        transportista->nombre,
        transportista->email,
        transportista->nombre_empresa,
        transportista->ciudad);
}

Transportista* alta_transportista(VectorTransportistas* v_transportistas)
{
    Transportista* temp;
    temp = (Transportista*)realloc(v_transportistas->transportistas, (v_transportistas->size + 1) * sizeof(Transportista));
    if (temp == NULL) {
        perror("Error al reservar memoria para el nuevo transportista");
        return NULL;
    }
    v_transportistas->transportistas = temp;

    // El ID del transportista es asignado automáticamente.
    // Para ello, se obtendrá el ID del último transportista en el vector, se transformará a entero, se incrementará en 1 y se convertirá de nuevo a cadena.
    sprintf(v_transportistas->transportistas[v_transportistas->size].id_transportista, "%04d", atoi(v_transportistas->transportistas[v_transportistas->size - 1].id_transportista) + 1);
    printf("Introduce el nombre del transportista: ");
    scanf("%20s", v_transportistas->transportistas[v_transportistas->size].nombre);
    printf("Introduce el email del transportista: ");
    scanf("%30s", v_transportistas->transportistas[v_transportistas->size].email);
    printf("Introduce la contraseña del transportista: ");
    scanf("%15s", v_transportistas->transportistas[v_transportistas->size].contrasena);
    printf("Introduce el nombre de la empresa de transporte: ");
    scanf("%20s", v_transportistas->transportistas[v_transportistas->size].nombre_empresa);
    printf("Introduce la ciudad de operación: ");
    scanf("%20s", v_transportistas->transportistas[v_transportistas->size].ciudad);

    v_transportistas->size++;
    return &v_transportistas->transportistas[v_transportistas->size - 1];
}

void baja_transportista(VectorTransportistas* v_transportistas, char* id_transportista)
{
    int i;
    for (i = 0; i < v_transportistas->size; i++) {
        if (strcmp(v_transportistas->transportistas[i].id_transportista, id_transportista) == 0) {
            break;
        }
    }
    if (i == v_transportistas->size) {
        return;
    }
    for (; i < v_transportistas->size - 1; i++) {
        v_transportistas->transportistas[i] = v_transportistas->transportistas[i + 1];
    }
    v_transportistas->size--;
    Transportista* temp;
    temp = (Transportista*)realloc(v_transportistas->transportistas, v_transportistas->size * sizeof(Transportista));
    if (temp == NULL) {
        perror("Error al reservar memoria para el nuevo vector de transportistas");
        return;
    }
    v_transportistas->transportistas = temp;
}

Transportista* modificar_transportista(Transportista* transportista)
{
    unsigned opcion = 0;
    do{
        printf("1. Nombre: %s\n", transportista->nombre);
        printf("2. Email: %s\n", transportista->email);
        printf("3. Contraseña: %s\n", transportista->contrasena);
        printf("4. Nombre de la empresa: %s\n", transportista->nombre_empresa);
        printf("5. Ciudad: %s\n", transportista->ciudad);
        printf("6. Salir\n");
        leer_unsigned("Introduce el número de la opción que deseas modificar:", &opcion);

        switch (opcion) {
            case 1:
                leer_cadena("Introduce el nuevo nombre del transportista: ", transportista->nombre, 20);
                break;
            case 2:
                leer_cadena("Introduce el nuevo email del transportista: ", transportista->email, 30);
                break;
            case 3:
                leer_cadena("Introduce la nueva contraseña del transportista: ", transportista->contrasena, 15);
                break;
            case 4:
                leer_cadena("Introduce el nuevo nombre de la empresa de transporte: ", transportista->nombre_empresa, 20);
                break;
            case 5:
                leer_cadena("Introduce la nueva ciudad de operación: ", transportista->ciudad, 20);
                break;
            case 6:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no válida\n");
        }
    }while(opcion != 6);
    return transportista;
}

void listar_transportistas(VectorTransportistas* v_transportistas)
{
    int i;
    for (i = 0; i < v_transportistas->size; i++) {
        printf("========================================\n");
        printf("ID Transportista: %s\n", v_transportistas->transportistas[i].id_transportista);
        printf("Nombre: %s\n", v_transportistas->transportistas[i].nombre);
        printf("Email: %s\n", v_transportistas->transportistas[i].email);
        printf("Empresa: %s\n", v_transportistas->transportistas[i].nombre_empresa);
        printf("Ciudad: %s\n", v_transportistas->transportistas[i].ciudad);
    }
}

void listar_transportistas_ciudad(VectorTransportistas* v_transportistas, char* ciudad)
{
    unsigned encontradas = 0;
    int i;
    for (i = 0; i < v_transportistas->size; i++) {
        if (strcmp(v_transportistas->transportistas[i].ciudad, ciudad) == 0) {
            encontradas++;
            printf("========================================\n");
            printf("ID Transportista: %s\n", v_transportistas->transportistas[i].id_transportista);
            printf("Nombre: %s\n", v_transportistas->transportistas[i].nombre);
            printf("Email: %s\n", v_transportistas->transportistas[i].email);
            printf("Empresa: %s\n", v_transportistas->transportistas[i].nombre_empresa);
            printf("Ciudad: %s\n", v_transportistas->transportistas[i].ciudad);
        }
    }
    if (encontradas == 0) {
        printf("No se han encontrado transportistas en la ciudad %s\n", ciudad);
    }
}