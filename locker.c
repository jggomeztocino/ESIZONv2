#include "stdio.h"
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#include "locker.h"
//Ejemplo:
//Lock001-Puerto Real-Cádiz-local 12-15-0
void cargar_lockers(VectorLockers* lockers)
{
    FILE* f = fopen("../data/Lockers.txt", "r");
    if (f == NULL) {
        perror("\nError al abrir el archivo\n");
        return;
    }
    lockers->lockers = (Locker*)malloc(sizeof(Locker));
    lockers->size = 0;
    while (fscanf(f, "%10[^-]-%20[^-]-%20[^-]-%20[^-]-%u-%u\n",
                  lockers->lockers[lockers->size].id_locker,
                  lockers->lockers[lockers->size].localidad,
                  lockers->lockers[lockers->size].provincia,
                  lockers->lockers[lockers->size].ubicacion,
                  &lockers->lockers[lockers->size].num_compartimentos_total,
                  &lockers->lockers[lockers->size].num_compartimentos_ocupados) == 6) {
        lockers->size++;
        lockers->lockers = (Locker*)realloc(lockers->lockers, (lockers->size + 1) * sizeof(Locker));
        if(lockers->lockers == NULL) {
            free(lockers->lockers);
            perror("\nError al reservar memoria\n");
        }
    }
    fclose(f);
}

void guardar_lockers(VectorLockers* lockers)
{
    FILE* f = fopen("../data/Lockers.txt", "w");
    if (f == NULL) {
        return;
    }
    int i;
    for (i = 0; i < lockers->size; i++) {
        fprintf(f, "%s-%s-%s-%s-%u-%u\n",
                lockers->lockers[i].id_locker,
                lockers->lockers[i].localidad,
                lockers->lockers[i].provincia,
                lockers->lockers[i].ubicacion,
                lockers->lockers[i].num_compartimentos_total,
                lockers->lockers[i].num_compartimentos_ocupados);
    }
    fclose(f);
    free(lockers->lockers);
    lockers->size = 0;
}

Locker* buscar_locker_id(VectorLockers* lockers, char* id_locker)
{
    int i;
    for (i = 0; i < lockers->size; i++) {
        if (strcmp(lockers->lockers[i].id_locker, id_locker) == 0) {
            return &lockers->lockers[i];
        }
    }
    return NULL;
}

void listar_locker(Locker* locker)
{
    printf("ID: %s\n", locker->id_locker);
    printf("Localidad: %s\n", locker->localidad);
    printf("Provincia: %s\n", locker->provincia);
    printf("Ubicación: %s\n", locker->ubicacion);
    printf("Número total de compartimentos: %u\n", locker->num_compartimentos_total);
    printf("Número de compartimentos ocupados: %u\n", locker->num_compartimentos_ocupados);
}

void listar_lockers_localidad(VectorLockers* lockers, char* localidad)
{
    int i;
    for (i = 0; i < lockers->size; i++) {
        if (strcmp(lockers->lockers[i].localidad, localidad) == 0) {
            listar_locker(&lockers->lockers[i]);
        }
    }
}
//Ejemplo:
//Lock001-01-134697-ocupado-08/01/2024-13/03/2024
void cargar_compartimentos(VectorCompartimentos* v_compartimentos)
{
    FILE* f = fopen("../data/compartimentos.txt", "r");
    if (f == NULL) {
        perror("\nError al abrir el archivo\n");
        return;
    }
    v_compartimentos->compartimentos = (CompartimentoLocker*)malloc(sizeof(CompartimentoLocker));
    v_compartimentos->size = 0;
    while (fscanf(f, "%10[^-]-%u-%10[^-]-%u-%u-%u-%u-%u-%u-%u\n",
                  v_compartimentos->compartimentos[v_compartimentos->size].id_locker,
                  &v_compartimentos->compartimentos[v_compartimentos->size].n_compartimento,
                  v_compartimentos->compartimentos[v_compartimentos->size].cod_locker,
                  &v_compartimentos->compartimentos[v_compartimentos->size].estado,
                  &v_compartimentos->compartimentos[v_compartimentos->size].fecha_ocupacion.dia,
                  &v_compartimentos->compartimentos[v_compartimentos->size].fecha_ocupacion.mes,
                  &v_compartimentos->compartimentos[v_compartimentos->size].fecha_ocupacion.anio,
                  &v_compartimentos->compartimentos[v_compartimentos->size].fecha_caducidad.dia,
                  &v_compartimentos->compartimentos[v_compartimentos->size].fecha_caducidad.mes,
                  &v_compartimentos->compartimentos[v_compartimentos->size].fecha_caducidad.anio) == 10) {
        v_compartimentos->size++;
        v_compartimentos->compartimentos = (CompartimentoLocker*)realloc(v_compartimentos->compartimentos, (v_compartimentos->size + 1) * sizeof(CompartimentoLocker));
        if(v_compartimentos->compartimentos == NULL) {
            free(v_compartimentos->compartimentos);
            perror("\nError al reservar memoria\n");
        }
    }
    fclose(f);
}

void guardar_compartimentos(VectorCompartimentos* v_compartimentos)
{
    FILE* f = fopen("../data/compartimentos.txt", "w");
    if (f == NULL) {
        return;
    }
    int i;
    for (i = 0; i < v_compartimentos->size; i++) {
        fprintf(f, "%s-%u-%s-%u-%u-%u-%u-%u-%u\n",
                v_compartimentos->compartimentos[i].id_locker,
                v_compartimentos->compartimentos[i].n_compartimento,
                v_compartimentos->compartimentos[i].cod_locker,
                v_compartimentos->compartimentos[i].estado,
                v_compartimentos->compartimentos[i].fecha_ocupacion.dia,
                v_compartimentos->compartimentos[i].fecha_ocupacion.mes,
                v_compartimentos->compartimentos[i].fecha_ocupacion.anio,
                v_compartimentos->compartimentos[i].fecha_caducidad.dia,
                v_compartimentos->compartimentos[i].fecha_caducidad.mes,
                v_compartimentos->compartimentos[i].fecha_caducidad.anio);
    }
    fclose(f);
    free(v_compartimentos->compartimentos);
    v_compartimentos->size = 0;
}

CompartimentoLocker* buscar_compartimento_id(VectorCompartimentos* v_compartimentos, char* id_locker, unsigned n_compartimento)
{
    int i;
    for (i = 0; i < v_compartimentos->size; i++) {
        if (strcmp(v_compartimentos->compartimentos[i].id_locker, id_locker) == 0 && v_compartimentos->compartimentos[i].n_compartimento == n_compartimento) {
            return &v_compartimentos->compartimentos[i];
        }
    }
    return NULL;
}

void listar_compartimento(CompartimentoLocker* v_compartimento)
{
    printf("ID: %s\n", v_compartimento->id_locker);
    printf("Número de compartimento: %u\n", v_compartimento->n_compartimento);
    printf("Código del locker: %s\n", v_compartimento->cod_locker);
    printf("Estado: %s\n", v_compartimento->estado == 0 ? "vacío" : "ocupado");
    printf("Fecha de ocupación: %u/%u/%u\n", v_compartimento->fecha_ocupacion.dia, v_compartimento->fecha_ocupacion.mes, v_compartimento->fecha_ocupacion.anio);
    printf("Fecha de caducidad: %u/%u/%u\n", v_compartimento->fecha_caducidad.dia, v_compartimento->fecha_caducidad.mes, v_compartimento->fecha_caducidad.anio);
}

void listar_compartimentos_locker(VectorCompartimentos* v_compartimentos, char* id_locker)
{
    int i;
    for (i = 0; i < v_compartimentos->size; i++) {
        if (strcmp(v_compartimentos->compartimentos[i].id_locker, id_locker) == 0) {
            listar_compartimento(&v_compartimentos->compartimentos[i]);
        }
    }
}