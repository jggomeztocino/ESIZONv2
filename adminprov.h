#ifndef ADMINPROV_H
#define ADMINPROV_H

/* Estructura para administradores-proveedores */
typedef struct {
    char id_empresa[5]; // 4 dígitos + '\0'
    char nombre[21];
    char email[31];
    char contrasena[16];
    char perfil_usuario[12]; // "administrador" o "proveedor"
} AdminProv;

/* Vector de administradores proveedores */
typedef struct {
    AdminProv *admin_provs;
    unsigned size;
} VectorAdminProv;

#endif
