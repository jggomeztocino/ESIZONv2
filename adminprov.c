#include "stdio.h"
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#include "adminprov.h"

void cargar_adminprov(VectorAdminProv *v_adminprov)
{
    FILE *f = fopen("../data/AdminProv.txt", "r");
    if (f == NULL)
    {
        perror("Error al abrir el archivo");
        return;
    }

    v_adminprov->admin_provs = NULL;
    v_adminprov->size = 0;
    AdminProv *temp;

    AdminProv ap;

    while (fscanf(f, "%4[^-]-%20[^-]-%30[^-]-%15[^-]-%13[^\n]\n",
                  ap.id_empresa,
                  ap.nombre,
                  ap.email,
                  ap.contrasena,
                  ap.perfil_usuario) == 5)
    {

        temp = (AdminProv *)realloc(v_adminprov->admin_provs, (v_adminprov->size + 1) * sizeof(AdminProv));
        if (temp == NULL)
        {
            perror("Error al reservar memoria");
            free(v_adminprov->admin_provs);
            fclose(f);
            return;
        }
        v_adminprov->admin_provs = temp;
        v_adminprov->admin_provs[v_adminprov->size] = ap;
        v_adminprov->size++;
    }

    fclose(f);
}

void guardar_adminprov(VectorAdminProv *v_adminprov)
{
    FILE *f = fopen("../data/Adminprov.txt", "w");
    if (f == NULL)
    {
        return;
    }
    int i;
    for (i = 0; i < v_adminprov->size; i++)
    {
        fprintf(f, "%s-%s-%s-%s-%s\n",
                v_adminprov->admin_provs[i].id_empresa,
                v_adminprov->admin_provs[i].nombre,
                v_adminprov->admin_provs[i].email,
                v_adminprov->admin_provs[i].contrasena,
                v_adminprov->admin_provs[i].perfil_usuario);
    }
    fclose(f);
    free(v_adminprov->admin_provs);
    v_adminprov->size = 0;
}

AdminProv *buscar_adminprov_id(VectorAdminProv *v_adminprov, char *id_empresa)
{
    int i;
    for (i = 0; i < v_adminprov->size; i++)
    {
        if (strcmp(v_adminprov->admin_provs[i].id_empresa, id_empresa) == 0)
        {
            return &v_adminprov->admin_provs[i];
        }
    }
    return NULL;
}

AdminProv *buscar_adminprov_email(VectorAdminProv *v_adminprov, char *email)
{
    int i;
    for (i = 0; i < v_adminprov->size; i++)
    {
        if (strcmp(v_adminprov->admin_provs[i].email, email) == 0)
        {
            return &v_adminprov->admin_provs[i];
        }
    }
    return NULL;
}

void listar_adminprov(AdminProv *adminprov)
{
    printf("\n==============================\n");
    printf("ID: %s\n", adminprov->id_empresa);
    printf("Nombre: %s\n", adminprov->nombre);
    printf("Email: %s\n", adminprov->email);
    printf("Contraseña: %s\n", adminprov->contrasena);
    printf("Perfil de usuario: %s\n", adminprov->perfil_usuario);
    printf("==============================");
}

void listar_provs(VectorAdminProv *v_adminprov)
{
    int i;
    for (i = 0; i < v_adminprov->size; i++)
    {
        if (strcmp(v_adminprov->admin_provs[i].perfil_usuario, "proveedor") == 0)
        {
            listar_adminprov(&v_adminprov->admin_provs[i]);
        }
    }
    printf("\n");
}

AdminProv *alta_proveedor(VectorAdminProv *v_adminprov)
{
    if (v_adminprov->size == 0)
    {
        v_adminprov->admin_provs = (AdminProv *)malloc(sizeof(AdminProv));
        if (v_adminprov->admin_provs == NULL)
        {
            free(v_adminprov->admin_provs);
            perror("\nError al reservar memoria\n");
        }
    }
    else
    {
        AdminProv *temp = (AdminProv *)realloc(v_adminprov->admin_provs, (v_adminprov->size + 1) * sizeof(AdminProv));
        if (temp == NULL)
        {
            free(v_adminprov->admin_provs);
            perror("\nError al reservar memoria\n");
        }
        v_adminprov->admin_provs = temp;
    }
    // Los IDs son consecutivos a la hora de dar de alta
    sprintf(v_adminprov->admin_provs[v_adminprov->size].id_empresa, "%04d", v_adminprov->size + 1);
    leer_cadena("\nIntroduce el nombre de la empresa: ", v_adminprov->admin_provs[v_adminprov->size].nombre, 20);
    leer_cadena("\nIntroduce el email de la empresa: ", v_adminprov->admin_provs[v_adminprov->size].email, 30);
    leer_cadena("\nIntroduce la contraseña de la empresa: ", v_adminprov->admin_provs[v_adminprov->size].contrasena, 15);
    strcpy(v_adminprov->admin_provs[v_adminprov->size].perfil_usuario, "proveedor"); // Perfil de usuario por defecto: proveedor
    v_adminprov->size++;
    return &v_adminprov->admin_provs[v_adminprov->size - 1];
}

void eliminar_proveedor(VectorAdminProv *v_adminprov, AdminProv *proveedor)
{
    int i;
    for (i = 0; i < v_adminprov->size; i++)
    {
        if (proveedor == &v_adminprov->admin_provs[i])
            break;
    }
    if (i == v_adminprov->size)
    {
        printf("No se ha encontrado el proveedor\n");
        return;
    }
    for (; i < v_adminprov->size - 1; i++)
        v_adminprov->admin_provs[i] = v_adminprov->admin_provs[i + 1];
    v_adminprov->size--;
    AdminProv *temp = (AdminProv *)realloc(v_adminprov->admin_provs, v_adminprov->size * sizeof(AdminProv));
    if (temp == NULL)
    {
        perror("\nError al reservar memoria\n");
    }
    v_adminprov->admin_provs = temp;
}

void baja_proveedor(VectorAdminProv *v_adminprov)
{
    unsigned opcion;
    AdminProv *proveedor = NULL;

    leer_unsigned("¿Cómo desea buscar al proveedor a dar de baja?\n1. Por ID\n2. Por email\n", &opcion);
    if (opcion == 1)
    {
        char id_empresa[5];
        leer_cadena("\nIntroduce el ID de la empresa: ", id_empresa, 4);
        proveedor = buscar_adminprov_id(v_adminprov, id_empresa);
        if (proveedor == NULL)
        {
            printf("\nNo se ha encontrado el proveedor con ID %s\n", id_empresa);
            return;
        }
    }
    else if (opcion == 2)
    {
        char email[31];
        leer_cadena("\nIntroduce el email de la empresa: ", email, 30);
        proveedor = buscar_adminprov_email(v_adminprov, email);
        if (proveedor == NULL)
        {
            printf("\nNo se ha encontrado el proveedor con email %s\n", email);
            return;
        }
    }
    else
    {
        printf("\nOpción no válida. Por favor, elige 1 o 2.\n");
        return;
    }

    eliminar_proveedor(v_adminprov, proveedor);
}

AdminProv *modificar_proveedor(VectorAdminProv *v_adminprov)
{
    // Pregunta si desea buscar por ID o por email y llama a la función correspondiente
    unsigned opcion;
    AdminProv *proveedor;

    leer_unsigned("\n¿Cómo desea buscar al proveedor a modificar?\n1. Por ID\n2. Por email\n", &opcion);

    if (opcion == 1)
    {
        char id_empresa[5];
        leer_cadena("\nIntroduce el ID de la empresa: ", id_empresa, 4);
        proveedor = buscar_adminprov_id(v_adminprov, id_empresa);
        if (proveedor == NULL)
        {
            printf("\nNo se ha encontrado el proveedor con ID %s\n", id_empresa);
            return NULL;
        }
    }
    if (opcion == 2)
    {
        char email[31];
        leer_cadena("\nIntroduce el email de la empresa: ", email, 30);
        proveedor = buscar_adminprov_email(v_adminprov, email);
        if (proveedor == NULL)
        {
            printf("\nNo se ha encontrado el proveedor con email %s\n", email);
            return NULL;
        }
    }

    unsigned opcion_modificar;
    while (1)
    {
        listar_adminprov(proveedor);

        leer_unsigned("\n¿Qué campo desea modificar?\n1. Nombre\n2. Email\n3. Contraseña\n4. Volver\n", &opcion_modificar);
        if (opcion_modificar == 1)
        {
            leer_cadena("Introduce el nuevo nombre de la empresa: ", proveedor->nombre, 20);
        }
        if (opcion_modificar == 2)
        {
            leer_cadena("Introduce el nuevo email de la empresa: ", proveedor->email, 30);
        }
        if (opcion_modificar == 3)
        {
            leer_cadena("Introduce la nueva contraseña de la empresa: ", proveedor->contrasena, 15);
        }
        if (opcion_modificar == 4)
        {
            return proveedor;
        }
    }
}

AdminProv *buscar_proveedor_id(VectorAdminProv *v_adminprov, char *id_proveedor)
{
    AdminProv *proveedor = buscar_adminprov_id(v_adminprov, id_proveedor);
    if (proveedor == NULL || strcmp(proveedor->perfil_usuario, "proveedor") != 0)
    {
        return NULL;
    }
    return proveedor;
}

AdminProv *buscar_proveedor_email(VectorAdminProv *v_adminprov, char *email)
{
    AdminProv *proveedor = buscar_adminprov_email(v_adminprov, email);
    if (proveedor == NULL || strcmp(proveedor->perfil_usuario, "proveedor") != 0)
    {
        return NULL;
    }
    return proveedor;
}

// Funcion para modificar el ID de la empresa del administrador
void modificarIdEmpresa(AdminProv *admin)
{
    char nuevoId[5];
    leer_cadena("Ingrese el nuevo ID de Empresa: ", nuevoId, sizeof(nuevoId));
    strcpy(admin->id_empresa, nuevoId);
    printf("\nID de Empresa actualizado con exito.\n");
}

// Funcion para modificar el nombre del administrador
void modificarNombre(AdminProv *admin)
{
    char nuevoNombre[21];
    leer_cadena("Ingrese el nuevo nombre: ", nuevoNombre, sizeof(nuevoNombre));
    strcpy(admin->nombre, nuevoNombre);
    printf("\nNombre actualizado con exito.\n");
}

// Funcion para modificar el email del administrador
void modificarEmail(AdminProv *admin)
{
    char nuevoEmail[31];
    leer_cadena("Ingrese el nuevo email: ", nuevoEmail, sizeof(nuevoEmail));
    strcpy(admin->email, nuevoEmail);
    printf("\nEmail actualizado con exito.\n");
}

// Funcion para modificar la contrasena del administrador
void modificarContrasena(AdminProv *admin)
{
    char nuevaContrasena[16];
    leer_cadena("Ingrese la nueva contrasena: ", nuevaContrasena, sizeof(nuevaContrasena));
    strcpy(admin->contrasena, nuevaContrasena);
    printf("\nContrasena actualizada con exito.\n");
}