#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define BUFFER_SIZE 4096

void copy_system_calls(const char *src, const char *dst) {
    int fd_src = open(src, O_RDONLY);
    if (fd_src < 0) {
        perror("Error al abrir origen (syscall)");
        exit(EXIT_FAILURE);
    }

    // O_EXCL junto con O_CREAT hace que falle si el archivo ya existe
    int fd_dst = open(dst, O_WRONLY | O_CREAT | O_EXCL, 0644);
    if (fd_dst < 0) {
        perror("Error al crear destino (syscall)");
        close(fd_src);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes;
    while ((bytes = read(fd_src, buffer, BUFFER_SIZE)) > 0) {
        if (write(fd_dst, buffer, bytes) != bytes) {
            perror("Error escribiendo");
            break;
        }
    }

    close(fd_src);
    close(fd_dst);
}

void copy_library_functions(const char *src, const char *dst) {
    FILE *f_src = fopen(src, "rb");
    if (!f_src) {
        perror("Error al abrir origen (lib)");
        exit(EXIT_FAILURE);
    }

    // Verificamos si existe manualmente para cumplir la consigna antes de fopen "wb"
    if (access(dst, F_OK) == 0) {
        errno = EEXIST;
        perror("Error al crear destino (lib)");
        fclose(f_src);
        exit(EXIT_FAILURE);
    }

    FILE *f_dst = fopen(dst, "wb");
    if (!f_dst) {
        perror("Error al abrir destino (lib)");
        fclose(f_src);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    size_t bytes;
    while ((bytes = fread(buffer, 1, BUFFER_SIZE, f_src)) > 0) {
        if (fwrite(buffer, 1, bytes, f_dst) != bytes) {
            perror("Error escribiendo");
            break;
        }
    }

    fclose(f_src);
    fclose(f_dst);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s [s|f] origen destino\n", argv[0]);
        return EXIT_FAILURE;
    }

    char mode = argv[1][0];
    if (mode == 's') {
        copy_system_calls(argv[2], argv[3]);
    } else if (mode == 'f') {
        copy_library_functions(argv[2], argv[3]);
    } else {
        fprintf(stderr, "Modo inválido. Use 's' o 'f'.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
