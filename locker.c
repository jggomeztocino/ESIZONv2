#include "stdio.h"
#include <string.h>
#include <stdlib.h>

#include "locker.h"


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
        /*lockers->lockers = (Locker*)realloc(lockers->lockers, (lockers->size + 1) * sizeof(Locker));
        if(lockers->lockers == NULL) {
            free(lockers->lockers);
            perror("\nError al reservar memoria\n");
        }*/
        Locker* temp = (Locker*)realloc(lockers->lockers, (lockers->size + 1) * sizeof(Locker));
        if (temp == NULL) {
            perror("\nError al reservar memoria\n");
            free(lockers->lockers);
            fclose(f);
            return;
        }
        lockers->lockers = temp;
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


void cargar_compartimentos(VectorCompartimentos* v_compartimentos) {
    // Abrir archivo de compartimentos para lectura
    FILE* f = fopen("../data/compartimentos.txt", "r");
    if (f == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    // Inicializar la memoria para almacenar los compartimentos
    v_compartimentos->compartimentos = (CompartimentoLocker*)malloc(sizeof(CompartimentoLocker));
    if (v_compartimentos->compartimentos == NULL) {
        perror("Error al reservar memoria inicial");
        fclose(f);
        return;
    }
    v_compartimentos->size = 0;

    CompartimentoLocker* temp;
    unsigned n_compartimentos_actual = 0;

    // Leer los datos de los compartimentos del archivo
    while (fscanf(f, "%10[^-]-%u-%u-%u-%u-%u-%u-%u-%u-%u\n",
                  v_compartimentos->compartimentos[n_compartimentos_actual].id_locker,
                  &v_compartimentos->compartimentos[n_compartimentos_actual].n_compartimento,
                  &v_compartimentos->compartimentos[n_compartimentos_actual].cod_locker,
                  &v_compartimentos->compartimentos[n_compartimentos_actual].estado,
                  &v_compartimentos->compartimentos[n_compartimentos_actual].fecha_ocupacion.dia,
                  &v_compartimentos->compartimentos[n_compartimentos_actual].fecha_ocupacion.mes,
                  &v_compartimentos->compartimentos[n_compartimentos_actual].fecha_ocupacion.anio,
                  &v_compartimentos->compartimentos[n_compartimentos_actual].fecha_caducidad.dia,
                  &v_compartimentos->compartimentos[n_compartimentos_actual].fecha_caducidad.mes,
                  &v_compartimentos->compartimentos[n_compartimentos_actual].fecha_caducidad.anio) == 10) {

        n_compartimentos_actual++;
        temp = (CompartimentoLocker*)realloc(v_compartimentos->compartimentos, (n_compartimentos_actual + 1) * sizeof(CompartimentoLocker));
        if (temp == NULL) {
            perror("Error al reservar memoria durante la lectura");
            free(v_compartimentos->compartimentos);
            fclose(f);
            return;
        }
        v_compartimentos->compartimentos = temp;
    }

    // Actualizar la cantidad de compartimentos después de la lectura completa
    v_compartimentos->size = n_compartimentos_actual;
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
        fprintf(f, "%s-%u-%u-%u-%u-%u-%u-%u-%u-%u\n",
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




void listar_compartimento(CompartimentoLocker* v_compartimento)
{
    printf("ID: %s\n", v_compartimento->id_locker);
    printf("Número de compartimento: %u\n", v_compartimento->n_compartimento);
    printf("Código del locker: %u\n", v_compartimento->cod_locker);
    printf("Estado: %s\n", v_compartimento->estado == 0 ? "vacío" : "ocupado");
    printf("Fecha de ocupación: %u/%u/%u\n", v_compartimento->fecha_ocupacion.dia, v_compartimento->fecha_ocupacion.mes, v_compartimento->fecha_ocupacion.anio);
    printf("Fecha de caducidad: %u/%u/%u\n", v_compartimento->fecha_caducidad.dia, v_compartimento->fecha_caducidad.mes, v_compartimento->fecha_caducidad.anio);
}

void listar_todo_lockers(VectorLockers* v_lockers)
{
    int i;
    for (i = 0; i < v_lockers->size; i++) {
        listar_locker(&v_lockers->lockers[i]);
    }
}


CompartimentoLocker* buscar_compartimento(VectorCompartimentos* v_compartimentos, char* id_locker, unsigned num_compartimento)
{
    int i;
    for (i = 0; i < v_compartimentos->size; i++) {
        if (strcmp(v_compartimentos->compartimentos[i].id_locker, id_locker) == 0 && v_compartimentos->compartimentos[i].n_compartimento == num_compartimento) {
            return &v_compartimentos->compartimentos[i];
        }
    }
    return NULL;
}

CompartimentoLocker* buscar_primer_compartimento_libre(VectorCompartimentos* v_compartimentos, char* id_locker)
{
    int i;
    for (i = 0; i < v_compartimentos->size; i++) {
        if (strcmp(v_compartimentos->compartimentos[i].id_locker, id_locker) == 0 && v_compartimentos->compartimentos[i].estado == 0) {
            return &v_compartimentos->compartimentos[i];
        }
    }
    return NULL;
}






