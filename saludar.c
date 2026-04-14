/*
 * Imprime un saludo por la salida estándar.
 */
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("No se proporcionó un nombre.\n");
        exit(EXIT_FAILURE);
    } else if (argc > 2) {
        printf("Mucho argumento!\n");
        exit(EXIT_FAILURE);
    }
    
    char *nombre = argv[1];
    printf("Hola %s\n", nombre);
    exit(EXIT_SUCCESS);
}
