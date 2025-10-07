#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
int main() {
    const char *fifo = "PIPE02";
    int numero;
    // Crear FIFO si no existe
    mkfifo(fifo, 0666);
    int factorial=1;
    int fd = open(fifo, O_RDONLY);
    if (fd == -1) {
        printf("lector: error al abrir FIFO");
        exit(EXIT_FAILURE);
    }

    // Leer el número enviado
    if (read(fd, &numero, sizeof(numero)) == -1) {
        printf("lector: error al leer");
        close(fd);
        exit(EXIT_FAILURE);
    }
	for (int i = 2; i <= numero; i++) {
        factorial *= i;
    }
	close(fd);
    // Abrir FIFO para escritura (bloquea hasta que el lector abra)
     fd = open(fifo, O_WRONLY);
    if (fd == -1) {
        printf("escritor: error al abrir FIFO");
        exit(EXIT_FAILURE);
    }

    // Escribir el número en la FIFO
    if (write(fd, &factorial, sizeof(factorial)) == -1) {
        printf("escritor: error al escribir");
    } else {
        printf(" Número %d enviado al lector.\n", numero);
    }

     close(fd);
    return 0;
}
