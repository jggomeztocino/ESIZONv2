#ifndef TRANSPORTISTA_H
#define TRANSPORTISTA_H
#include "stdbool.h"
#include "pedido.h"
#include "string.h"
#include "fecha.h"
#include "utilidades.h"
// Estructura que representa a un transportista
typedef struct {
    int id_transportista; // 4 digitos
    char nombre[21]; // Nombre del transportista
    char email[31]; // Email del transportista
    char contrasena[16]; // Contraseña de acceso
    char nombre_empresa[21]; // Nombre de la empresa de transporte
    char ciudad[21]; // Ciudad de operación
} Transportista;
void mostrar_perfil_transportista(Transportista  v_transportistas);
void modificar_perfil_transportista(Transportista* v_transport, int pos_transportista);
int seleecion_transportista(Transportista* transportistas, int n_transportistas) ;

#endif // TRANSPORTISTA_H


