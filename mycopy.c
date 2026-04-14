/*
 * Copia un archivo en otro.
 */
#include <stdio.h>
#include <stdlib.h>     // exit()

int main(int argc, char *argv[]) {

    if (argc != 3) {
        perror("Cantidad incorrecta de argumentos.");
        exit(EXIT_FAILURE);
    }

    FILE *origen = fopen(argv[1], "r");
    if (origen == NULL) {
        perror("Error al abrir el archivo de origen");
        fclose(origen);
        exit(EXIT_FAILURE);
    }

    FILE *destino = fopen(argv[2], "r");
    if (destino != NULL) {
        perror("El archivo destino ya existe");
        fclose(origen);
        fclose(destino);
        exit(EXIT_FAILURE);
    }

    destino = fopen(argv[2], "w");
    if (destino == NULL) {
        perror("Error al crear el archivo de destino");
        fclose(origen);
        fclose(destino);
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    size_t bytesLeidos;
    while ((bytesLeidos = fread(buffer, 1, sizeof(buffer), origen)) > 0) {
        fwrite(buffer, 1, bytesLeidos, destino);
    }

    fclose(origen);
    fclose(destino);

    // Termina la ejecución del proceso.
    exit(EXIT_SUCCESS);
}
