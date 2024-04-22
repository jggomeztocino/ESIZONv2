#include "stdio.h"
#include <string.h>
#include <malloc.h>

#include "cliente.h"
#include "utilidades.h"

//Hacer los comentarios de las funciones como en categoria.h


void cargar_clientes(VectorClientes* v_clientes)
{
    FILE* f = fopen("../data/Clientes.txt", "r");
    if (f == NULL) {
        perror("\nError al abrir el archivo\n");
        return;
    }
    v_clientes->clientes = (Cliente*)malloc(sizeof(Cliente));
    v_clientes->size = 0;
    // 0000001-Juan Pérez-Plaza San Francisco 1 11100-San Fernando-Cádiz-juanperez@gmail.com-psw1234-1000
    // 0000002-Guillermo López-Calle Sacramento 2 11003-Cádiz-Cádiz-guillelopez@gmail.com/psw4321/500
    // Debe cargar todos los clientes del archivo

    while (fscanf(f, "%7[^-]-%20[^-]-%50[^-]-%20[^-]-%20[^-]-%30[^-]-%15[^-]-%f\n",
                  v_clientes->clientes[v_clientes->size].id_cliente,
                  v_clientes->clientes[v_clientes->size].nombre_cliente,
                  v_clientes->clientes[v_clientes->size].direccion_cliente,
                  v_clientes->clientes[v_clientes->size].poblacion,
                  v_clientes->clientes[v_clientes->size].provincia,
                  v_clientes->clientes[v_clientes->size].email,
                  v_clientes->clientes[v_clientes->size].contrasena,
                  &v_clientes->clientes[v_clientes->size].cartera) == 8) {
        v_clientes->size++;
        v_clientes->clientes = (Cliente*)realloc(v_clientes->clientes, (v_clientes->size + 1) * sizeof(Cliente));
        if(v_clientes->clientes == NULL) {
            free(v_clientes->clientes);
            perror("\nError al reservar memoria\n");
        }
    }
    fclose(f);
}

void guardar_clientes(VectorClientes* v_clientes)
{
    FILE* f = fopen("../data/Clientes.txt", "w");
    if (f == NULL) {
        return;
    }
    int i;
    for (i = 0; i < v_clientes->size; i++) {
        fprintf(f, "%s-%s-%s-%s-%s-%s-%s-%.2f\n",
                v_clientes->clientes[i].id_cliente,
                v_clientes->clientes[i].nombre_cliente,
                v_clientes->clientes[i].direccion_cliente,
                v_clientes->clientes[i].poblacion,
                v_clientes->clientes[i].provincia,
                v_clientes->clientes[i].email,
                v_clientes->clientes[i].contrasena,
                v_clientes->clientes[i].cartera);
    }
    fclose(f);
    free(v_clientes->clientes);
    v_clientes->size = 0;
}

void listar_cliente(Cliente* cliente)
{
    printf(
        "---------------------------\n"
        "Nombre:     %s\n"
        "Dirección:  %s\n"
        "Población:  %s\n"
        "Provincia:  %s\n"
        "Email:      %s\n"
        "Contraseña: %s\n"
        "Cartera:    %.2f €\n"
        "---------------------------\n",
        cliente->nombre_cliente, cliente->direccion_cliente, cliente->poblacion,
        cliente->provincia, cliente->email, cliente->contrasena, cliente->cartera);
}


void modificar_cliente(Cliente* cliente)
{
    unsigned seleccion;
    char nombre[21], direccion[51], poblacion[21], provincia[21], email[31], contrasena[16];
    float cartera;
    do {
        printf("¿Qué deseas modificar?\n"
               "---------------------------\n"
               "1. Nombre\n"
               "2. Dirección\n"
               "3. Población\n"
               "4. Provincia\n"
               "5. Email\n"
               "6. Contraseña\n"
               "7. Cartera\n"
               "8. Salir\n"
               "---------------------------\n");
        leer_unsigned("Introduce una opción [1-8]", &seleccion);

        if (seleccion < 1 || seleccion > 8) {
            puts("Introduzca una opción válida\n");
            continue; // Vuelve al inicio del bucle para solicitar una nueva opción
        }

        switch (seleccion) {
            case 1:
                leer_cadena("Introduzca su nuevo nombre\n", nombre, 21);
                strcpy(cliente->nombre_cliente, nombre);
                break;
            case 2:
                leer_cadena("Introduzca su nueva dirección\n", direccion, 51);
                strcpy(cliente->direccion_cliente, direccion);
                break;
            case 3:
                leer_cadena("Introduzca su nueva poblacion\n", poblacion, 21);
                strcpy(cliente->poblacion, poblacion);
                break;
            case 4:
                leer_cadena("Introduzca su nueva provincia\n", provincia, 21);
                strcpy(cliente->provincia, provincia);
                break;
            case 5:
                leer_cadena("Introduzca su nuevo email\n", email, 31);
                strcpy(cliente->email, email);
                break;
            case 6:
                leer_cadena("Introduzca su nueva contraseña\n", contrasena, 16);
                strcpy(cliente->contrasena, contrasena);
                break;
            case 7:
                leer_real("Introduzca su nueva cartera\n", &cartera);
                cliente->cartera = cartera;
                break;
            case 8:
                break;
            default:
                puts("Introduzca una opción válida\n");
                break;
        }
        if ( seleccion > 1 && seleccion < 8)
            listar_cliente(cliente); // muestra el perfil modificado
    } while (seleccion != 8);
}


Cliente* buscar_cliente_por_id(VectorClientes* v_clientes, char* id_cliente) {
    int i;
    for (i = 0; i < v_clientes->size; i++) {
        if (strcmp(v_clientes->clientes[i].id_cliente, id_cliente) == 0) {
            return &v_clientes->clientes[i];
        }
    }
    return NULL;
}

Cliente* buscar_cliente_por_email(VectorClientes* v_clientes, char* email) {
    int i;
    for (i = 0; i < v_clientes->size; i++) {
        if (strcmp(v_clientes->clientes[i].email, email) == 0) {
            return &v_clientes->clientes[i];
        }
    }
    return NULL;
}

void listar_clientes(VectorClientes* v_clientes) {
    printf("Tamaño del vector: %d\n", v_clientes->size);
    int i;
    printf("---------------------------\n");
    for (i = 0; i < v_clientes->size; i++) {
        printf("Cliente %d\n", i + 1);
        listar_cliente(&v_clientes->clientes[i]);
    }
}

void eliminar_cliente(VectorClientes* v_clientes, char* id_cliente) {
    int i;
    for (i = 0; i < v_clientes->size; i++) {
        if (strcmp(v_clientes->clientes[i].id_cliente, id_cliente) == 0){
            // Desplazar los elementos a la izquierda
            int j;
            for (j = i; j < v_clientes->size - 1; j++) {
                v_clientes->clientes[j] = v_clientes->clientes[j + 1];
            }
            v_clientes->size--;
            break;
        }
    }
    v_clientes->clientes = (Cliente*)realloc(v_clientes->clientes, v_clientes->size * sizeof(Cliente));
    if(v_clientes->clientes == NULL) {
        free(v_clientes->clientes);
        perror("\nError al reservar memoria\n");
    }
}


void alta_cliente(VectorClientes* v_clientes) {
    char nombre[21], direccion[51], poblacion[21], provincia[21], email[31], contrasena[16];
    float cartera;
    leer_cadena("Introduzca su nombre\n", nombre, 21);
    leer_cadena("Introduzca su direccion\n", direccion, 51);
    leer_cadena("Introduzca su poblacion\n", poblacion, 21);
    leer_cadena("Introduzca su provincia\n", provincia, 21);
    leer_cadena("Introduzca su email\n", email, 31);
    leer_cadena("Introduzca su contraseña\n", contrasena, 16);
    leer_real("Introduzca su cartera\n", &cartera);
    sprintf(v_clientes->clientes[v_clientes->size].id_cliente, "%07d", v_clientes->size + 1);
    strcpy(v_clientes->clientes[v_clientes->size].nombre_cliente, nombre);
    strcpy(v_clientes->clientes[v_clientes->size].direccion_cliente, direccion);
    strcpy(v_clientes->clientes[v_clientes->size].poblacion, poblacion);
    strcpy(v_clientes->clientes[v_clientes->size].provincia, provincia);
    strcpy(v_clientes->clientes[v_clientes->size].email, email);
    strcpy(v_clientes->clientes[v_clientes->size].contrasena, contrasena);
    v_clientes->clientes[v_clientes->size].cartera = cartera;
    v_clientes->size++;
    v_clientes->clientes = (Cliente*)realloc(v_clientes->clientes, (v_clientes->size + 1) * sizeof(Cliente));
    if(v_clientes->clientes == NULL) {
        free(v_clientes->clientes);
        perror("\nError al reservar memoria\n");
    }
}