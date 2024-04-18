#include "stdio.h"
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#include "adminprov.h"

/*
// Estructura para administradores-proveedores
typedef struct {
    char id_empresa[5]; // 4 dígitos + '\0'
    char nombre[21];
    char email[31];
    char contrasena[16];
    char perfil_usuario[12]; // "administrador" o "proveedor"
} AdminProv;

// Vector de administradores proveedores
typedef struct {
    AdminProv *admin_provs;
    unsigned size;
} VectorAdminProv;
 */

void cargar_adminprov(VectorAdminProv *v_adminprov)
{
    FILE* f = fopen("../data/adminprov.txt", "r");
    if (f == NULL) {
        perror("\nError al abrir el archivo\n");
        return;
    }
    v_adminprov->admin_provs = (AdminProv*)malloc(sizeof(AdminProv));
    v_adminprov->size = 0;
    while (fscanf(f, "%s-%20[^\n]-%30[^\n]-%15[^\n]-%11[^\n]\n",
                  v_adminprov->admin_provs[v_adminprov->size].id_empresa,
                  v_adminprov->admin_provs[v_adminprov->size].nombre,
                  v_adminprov->admin_provs[v_adminprov->size].email,
                  v_adminprov->admin_provs[v_adminprov->size].contrasena,
                  v_adminprov->admin_provs[v_adminprov->size].perfil_usuario) == 5) {
        v_adminprov->size++;
        v_adminprov->admin_provs = (AdminProv*)realloc(v_adminprov->admin_provs, (v_adminprov->size + 1) * sizeof(AdminProv));
        if(v_adminprov->admin_provs == NULL) {
            free(v_adminprov->admin_provs);
            perror("\nError al reservar memoria\n");
        }
    }
    fclose(f);
}

void guardar_adminprov(VectorAdminProv *v_adminprov)
{
    FILE* f = fopen("../data/adminprov.txt", "w");
    if (f == NULL) {
        return;
    }
    int i;
    for (i = 0; i < v_adminprov->size; i++) {
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

AdminProv* buscar_adminprov_id(VectorAdminProv* v_adminprov, char* id_empresa)
{
    int i;
    for (i = 0; i < v_adminprov->size; i++) {
        if (strcmp(v_adminprov->admin_provs[i].id_empresa, id_empresa) == 0) {
            return &v_adminprov->admin_provs[i];
        }
    }
    return NULL;
}

void listar_adminprov(AdminProv* adminprov)
{
    printf("ID: %s\n", adminprov->id_empresa);
    printf("Nombre: %s\n", adminprov->nombre);
    printf("Email: %s\n", adminprov->email);
    printf("Contraseña: %s\n", adminprov->contrasena);
    printf("Perfil de usuario: %s\n", adminprov->perfil_usuario);
}
