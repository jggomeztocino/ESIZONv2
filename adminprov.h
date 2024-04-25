#ifndef ADMINPROV_H
#define ADMINPROV_H


#include "utilidades.h"

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

void cargar_adminprov(VectorAdminProv *v_adminprov);

void guardar_adminprov(VectorAdminProv *v_adminprov);

void modificarIdEmpresa(AdminProv *admin);

void modificarNombre(AdminProv *admin);

void modificarEmail(AdminProv *admin);

void modificarContrasena(AdminProv *admin);

AdminProv *buscar_adminprov_id(VectorAdminProv *v_adminprov, char *id_empresa);

AdminProv *buscar_adminprov_email(VectorAdminProv *v_adminprov, char *email);

void listar_adminprov(AdminProv *adminprov);

void listar_provs(VectorAdminProv *v_adminprov);

AdminProv* alta_proveedor(VectorAdminProv *v_adminprov);

void eliminar_proveedor(VectorAdminProv *v_adminprov, AdminProv *proveedor);

void baja_proveedor(VectorAdminProv *v_adminprov);

AdminProv *modificar_proveedor(VectorAdminProv *v_adminprov);

AdminProv* buscar_proveedor_id(VectorAdminProv* v_adminprov, char* id_proveedor);

AdminProv* buscar_proveedor_email(VectorAdminProv* v_adminprov, char* email);



#endif//ADMINPROV_H
