#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
int main() {
    const char *fifo = "FIFO1";
    const char *fifo2 = "FIFO2";
    srand(time(NULL));  // Inicializa la semilla con la hora actual
    
    int randomNum = rand() % 11;  // Número entre 0 y 10
    
    int numero;
    // Crear FIFO si no existe
    mkfifo(fifo, 0666);
    
    
    // Abrir FIFO para escritura (bloquea hasta que el lector abra)
    int fd = open(fifo, O_WRONLY);
    if (fd == -1) {
        printf("escritor: error al abrir FIFO");
        exit(EXIT_FAILURE);
    }

    // Escribir el número en la FIFO
    if (write(fd, &randomNum, sizeof(randomNum)) == -1) {
        printf("escritor: error al escribir");
    } else {
        printf(" Número %d enviado al lector.\n", randomNum);
    }

     close(fd);
     fd = open(fifo2, O_RDONLY);
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
	printf("el numero factorial de %d, es: %d\n",randomNum,numero),
	close(fd);
    
    return 0;
}
