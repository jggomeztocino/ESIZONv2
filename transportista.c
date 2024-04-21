#include "stdio.h"
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#include "transportista.h"
//Ejemplo:
//0001-Rafael Guitierrez- rafael@gutitrans.com-rf001-GutiTrans-Cádiz
//0002-Pepe Tinoco-pepe@itranspo.com-pp001-TransPo-Cádiz
void cargar_transportistas(VectorTransportistas* transportistas)
{
    FILE* f = fopen("../data/Transportistas.txt", "r");
    if (f == NULL) {
        perror("\nError al abrir el archivo\n");
        return;
    }
    transportistas->transportistas = (Transportista*)malloc(sizeof(Transportista));
    transportistas->size = 0;
    while (fscanf(f, "%4[^-]-%20[^-]-%30[^-]-%15[^-]-%20[^-]-%20[^-]\n",
                  transportistas->transportistas[transportistas->size].id_transportista,
                  transportistas->transportistas[transportistas->size].nombre,
                  transportistas->transportistas[transportistas->size].email,
                  transportistas->transportistas[transportistas->size].contrasena,
                  transportistas->transportistas[transportistas->size].nombre_empresa,
                  transportistas->transportistas[transportistas->size].ciudad) == 6) {
        transportistas->size++;
        transportistas->transportistas = (Transportista*)realloc(transportistas->transportistas, (transportistas->size + 1) * sizeof(Transportista));
        if(transportistas->transportistas == NULL) {
            free(transportistas->transportistas);
            perror("\nError al reservar memoria\n");
        }
    }
    fclose(f);
}

void guardar_transportistas(VectorTransportistas* transportistas)
{
    FILE* f = fopen("../data/Transportistas.txt", "w");
    if (f == NULL) {
        return;
    }
    int i;
    for (i = 0; i < transportistas->size; i++) {
        fprintf(f, "%s-%s-%s-%s-%s-%s\n",
                transportistas->transportistas[i].id_transportista,
                transportistas->transportistas[i].nombre,
                transportistas->transportistas[i].email,
                transportistas->transportistas[i].contrasena,
                transportistas->transportistas[i].nombre_empresa,
                transportistas->transportistas[i].ciudad);
    }
    fclose(f);
    free(transportistas->transportistas);
    transportistas->size = 0;
}

Transportista* buscar_transportista_id(VectorTransportistas* transportistas, char* id_transportista)
{
    int i;
    for (i = 0; i < transportistas->size; i++) {
        if (strcmp(transportistas->transportistas[i].id_transportista, id_transportista) == 0) {
            return &transportistas->transportistas[i];
        }
    }
    return NULL;
}

Transportista* buscar_transportista_email(VectorTransportistas* transportistas, char* email)
{
    int i;
    for (i = 0; i < transportistas->size; i++) {
        if (strcmp(transportistas->transportistas[i].email, email) == 0) {
            return &transportistas->transportistas[i];
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