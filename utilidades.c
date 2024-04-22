#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utilidades.h"

/* Especificación: void leer_cadena(char *, char *, int);
 * Precondición: texto será la frase que se imprimirá para solicitar el dato, cadena es la cadena dónde se escribirá
 *               el dato y largo es el tamaño de la variable cadena
 * Postcondición: si texto no es NULL, imprime por pantalla un mensaje que pedirá una cadena y se introducirá dentro de
 *                la variable cadena */
void leer_cadena(char *texto, char *cadena, int largo) {
    if (texto != NULL) {
        printf("%s", texto);
    }

    if (fgets(cadena, largo, stdin) != NULL) {
        size_t len = strlen(cadena);
        if (cadena[len - 1] == '\n') {
            cadena[len - 1] = '\0'; // Replace newline with null terminator
        } else {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF); // Clear the rest of the line
        }
    }
}

/* Especificación: void leer_caracter(char *, char *);
 * Precondición: texto será la frase que se imprimirá para solicitar el dato y caracter es la variable dónde se escribirá el dato
 * Postcondición: imprime por pantalla un mensaje que pedirá una cadena y se introducirá dentro de la variable caracter */
void leer_caracter(char *texto, char *caracter) {
    printf("%s", texto);
    while ((*caracter = getchar()) == '\n'); // Repeat until a non-newline character is read
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF); // Clear the rest of the line
}

/* Especificación: void leer_entero(char *, int *)
 * Precondición: num apunta a la variable de tipo entero a la que se le quiere asignar un valor,
 *               y texto será la frase que se imprimirá para solicitar ese valor
 * Postcondición: asigna un valor al puntero a entero num */
void leer_entero(char *texto, int *num) {
    printf("%s: ", texto);
    while (scanf("%d", num) != 1) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF); // Clear incorrect input
        printf("Entrada invalida. %s: ", texto);
    }
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF); // Clear the rest of the line
}

/* Especificación: void leer_real(char *, float *);
 * Precondición: num apunta a la variable de tipo float a la que se le quiere asignar un valor,
 *               y texto será la frase que se imprimirá para solicitar ese valor
 * Postcondición: asigna un valor al puntero a float num */
void leer_real(char *texto, float *num) {
    printf("%s: ", texto);
    while (scanf("%f", num) != 1) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF); // Clear incorrect input
        printf("Entrada invalida. %s: ", texto);
    }
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF); // Clear the rest of the line
}


/*
 * Especificación: void leer_unsigned(char *, unsigned int *);
 * Precondición: num apunta a la variable de tipo unsigned int a la que se le quiere asignar un valor,
 *              y texto será la frase que se imprimirá para solicitar ese valor
 * Postcondición: asigna un valor al puntero a unsigned unsigned num
 */
void leer_unsigned(char *texto, unsigned int *num) {
    printf("%s: ", texto);
    while (scanf("%u", num) != 1) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF); // Clear incorrect input
        printf("Entrada invalida. %s: ", texto);
    }
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF); // Clear the rest of the line
}
