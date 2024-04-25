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

/**
    * @brief Carga los administradores-proveedores desde el archivo AdminProvs.txt
    * @param v_adminprov Vector de administradores-proveedores
    
*/
void cargar_adminprov(VectorAdminProv *v_adminprov);

/**

    * @brief Guarda los administradores-proveedores en el archivo AdminProvs.txt
    * @param v_adminprov Vector de administradores-proveedores
    
*/
void guardar_adminprov(VectorAdminProv *v_adminprov);

/**

    * @brief Modifica el id de la empresa de un administrador-proveedor
    * @param admin Puntero al administrador-proveedor


*/
void modificarIdEmpresa(AdminProv *admin);

/**

    * @brief Modifica el nombre de un administrador-proveedor
    * @param admin Puntero al administrador-proveedor
*/
void modificarNombre(AdminProv *admin);


/**

    * @brief Modifica el email de un administrador-proveedor
    * @param admin Puntero al administrador-proveedor
*/
void modificarEmail(AdminProv *admin);


/**

    * @brief Modifica la contraseña de un administrador-proveedor
    * @param admin Puntero al administrador-proveedor
*/
void modificarContrasena(AdminProv *admin);


/**

    * @brief busca un administrador por su id de empresa
    * @param v_adminprov Vector de administradores-proveedores
    * @param id_empresa Id de la empresa a buscar
    * @return Puntero al administrador encontrado o NULL si no se encuentra
*/
AdminProv *buscar_adminprov_id(VectorAdminProv *v_adminprov, char *id_empresa);


/**

    * @brief busca un administrador por su email
    * @param v_adminprov Vector de administradores-proveedores
    * @param email Email a buscar
    * @return Puntero al administradorencontrado o NULL si no se encuentra
*/
AdminProv *buscar_adminprov_email(VectorAdminProv *v_adminprov, char *email);


/**

    * @brief Lista un administrador-proveedor
    * @param adminprov Puntero al administrador-proveedor
*/
void listar_adminprov(AdminProv *adminprov);


/**

    * @brief Lista todos los administradores-proveedores
    * @param v_adminprov Vector de administradores-proveedores
*/
void listar_provs(VectorAdminProv *v_adminprov);


/**

    * @brief Da de alta un proveedor
    * @param v_adminprov Vector de administradores-proveedores
    * @return Puntero al proveedor dado de alta
*/
AdminProv* alta_proveedor(VectorAdminProv *v_adminprov);


/**

    * @brief Elimina un proveedor
    * @param v_adminprov Vector de administradores-proveedores
    * @param proveedor Puntero al proveedor a eliminar
*/
void eliminar_proveedor(VectorAdminProv *v_adminprov, AdminProv *proveedor);


/**

    * @brief Da de baja un proveedor
    * @param v_adminprov Vector de administradores-proveedores
*/
void baja_proveedor(VectorAdminProv *v_adminprov);


/**

    * @brief Modifica un proveedor
    * @param v_adminprov Vector de administradores-proveedores
    * @return Puntero al proveedor modificado
*/
AdminProv *modificar_proveedor(VectorAdminProv *v_adminprov);


/**

    * @brief Busca un proveedor por su id
    * @param v_adminprov Vector de administradores-proveedores
    * @param id_proveedor Id del proveedor a buscar
    * @return Puntero al proveedor encontrado o NULL si no se encuentra
*/
AdminProv* buscar_proveedor_id(VectorAdminProv* v_adminprov, char* id_proveedor);


/**

    * @brief Busca un proveedor por su email
    * @param v_adminprov Vector de administradores-proveedores
    * @param email Email del proveedor a buscar
    * @return Puntero al proveedor encontrado o NULL si no se encuentra
*/
AdminProv* buscar_proveedor_email(VectorAdminProv* v_adminprov, char* email);



#endif//ADMINPROV_H
