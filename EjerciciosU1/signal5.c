#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

const char *fifo = "PIPE1";
int fd_lectura; // descriptor global para los hijos

// ---------- MANEJADORES DE SEÑAL ----------
void manejador_p2(int sig) {
    int num;
    read(fd_lectura, &num, sizeof(int));
    printf("Número par %d recibido por el proceso P2 con pid %d\n", num, getpid());
    fflush(stdout);
}

void manejador_p3(int sig) {
    int num;
    read(fd_lectura, &num, sizeof(int));
    printf("Número impar %d recibido por el proceso P3 con pid %d\n", num, getpid());
    fflush(stdout);
}

// ---------- PROGRAMA PRINCIPAL ----------
int main() {
    pid_t pid_p2, pid_p3;
    int num;

    // Crear FIFO si no existe
    mkfifo(fifo, 0666);

    // Crear primer hijo (P2)
    pid_p2 = fork();

    // ======= PROCESO P2 =======
    if (pid_p2 == 0) {
        signal(SIGUSR1, manejador_p2);
        fd_lectura = open(fifo, O_RDONLY); // abre una vez
        if (fd_lectura == -1) {
            perror("P2: error al abrir FIFO");
            exit(EXIT_FAILURE);
        }
        while (1) pause();
        exit(0);
    }

    // ======= PROCESO PADRE =======
    else if (pid_p2 > 0) {
        // Crear segundo hijo (P3)
        pid_p3 = fork();

        // ======= PROCESO P3 =======
        if (pid_p3 == 0) {
            signal(SIGUSR2, manejador_p3);
            fd_lectura = open(fifo, O_RDONLY); // abre una vez
            if (fd_lectura == -1) {
                perror("P3: error al abrir FIFO");
                exit(EXIT_FAILURE);
            }
            while (1) pause();
            exit(0);
        }

        // ======= PROCESO PADRE (P1) =======
        else if (pid_p3 > 0) {
            int fd_escritura = open(fifo, O_WRONLY);
            if (fd_escritura == -1) {
                perror("P1: error al abrir FIFO para escribir");
                exit(EXIT_FAILURE);
            }

            printf("Introduce número: ");
            while (scanf("%d", &num) == 1) {
                if (num == 0) {
                    printf("Mandando señal de terminación al proceso hijo P2 con pid %d\n", pid_p2);
                    kill(pid_p2, SIGTERM);

                    printf("Mandando señal de terminación al proceso hijo P3 con pid %d\n", pid_p3);
                    kill(pid_p3, SIGTERM);
                    break;
                }

                if (write(fd_escritura, &num, sizeof(num)) == -1) {
                    perror("Error al escribir en FIFO");
                } else {
                    printf("Número %d enviado al FIFO\n", num);
                }

                if (num % 2 == 0) {
                    printf("Enviando señal a P2\n");
                    kill(pid_p2, SIGUSR1);
                } else {
                    printf("Enviando señal a P3\n");
                    kill(pid_p3, SIGUSR2);
                }

                printf("Introduce número: ");
                fflush(stdout);
            }

            close(fd_escritura);
            unlink(fifo);
            printf("Fin proceso padre con pid %d\n", getpid());
        }

        // Error al crear P3
        else {
            perror("Error al crear proceso P3");
            exit(EXIT_FAILURE);
        }
    }

    // Error al crear P2
    else {
        perror("Error al crear proceso P2");
        exit(EXIT_FAILURE);
    }

    return 0;
}

