#ifndef TRANSPORTISTA_H
#define TRANSPORTISTA_H
#include "pedido.h"


// Estructura que representa a un transportista
typedef struct {
    char id_transportista[5]; // 4 digitos
    char nombre[21]; // Nombre del transportista
    char email[31]; // Email del transportista
    char contrasena[16]; // Contraseña de acceso
    char nombre_empresa[21]; // Nombre de la empresa de transporte
    char ciudad[21]; // Ciudad de operación
} Transportista;

// Estructura para almacenar un vector de transportistas junto a su tamaño
typedef struct {
    Transportista* transportistas;
    unsigned size;
} VectorTransportistas;

void cargar_transportistas(VectorTransportistas* v_transportistas);

void guardar_transportistas(VectorTransportistas* v_transportistas);

Transportista* buscar_transportista_id(VectorTransportistas* v_transportistas, char* id_transportista);

Transportista* buscar_transportista_email(VectorTransportistas* v_transportistas, char* email);

void listar_transportista(Transportista* transportista);

Transportista* alta_transportista(VectorTransportistas* v_transportistas);

void baja_transportista(VectorTransportistas* v_transportistas, char* id_transportista);

Transportista* modificar_transportista(Transportista* transportista);

void listar_transportistas(VectorTransportistas* v_transportistas);

void listar_transportistas_ciudad(VectorTransportistas* v_transportistas, char* ciudad);

#endif // TRANSPORTISTA_H


