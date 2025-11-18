#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int num1 = 0, n, fp, fifo;
char buffer[32];
pid_t p2, p3;

void par(int num){
    printf("Número par %d recibido por el proceso P2 con pid %d\n", num, getpid());
}

void impar(int num){
    printf("Número impar %d recibido por el proceso P3 con pid %d\n", num, getpid());
}

void finProcesos(int sigNum){
    if (getpid() == p2 || getpid() == p3) {
        // HIJO
        close(fp);
        exit(0);
    } 
    else {
        // PADRE
        printf("Mandando señal de terminación al proceso hijo P2 con pid %d\n", p2);
        kill(p2, SIGTERM);
    
        printf("Mandando señal de terminación al proceso hijo P3 con pid %d\n", p3);
        kill(p3, SIGTERM);
        
        close(fp);
        unlink("PIPE1");
        printf("Fin proceso padre con pid %d\n", getppid());
        exit(0);
    }
}

int main(){
    fifo = mkfifo("PIPE1", 0666); // crea el fifo

    // Hijo P2
    p2 = fork();
    if (p2 == 0) {
        fp = open("PIPE1", O_RDONLY); // lectura
        while (1) {
            n = read(fp, buffer, sizeof(buffer)-1);
            if (n > 0) {
                int num = atoi(buffer);
                if (num % 2 == 0) {
                    par(num);
                }
            }
        }
    }

    // Hijo P3
    p3 = fork();
    if (p3 == 0) {
        fp = open("PIPE1", O_RDONLY); // lectura
        while (1) {
            n = read(fp, buffer, sizeof(buffer)-1);
            if (n > 0) {
                int num = atoi(buffer);
                if (num % 2 != 0) {
                    impar(num);
                }
            }
        }
    }

    // PADRE
    fp = open("PIPE1", O_WRONLY); // escritura

    do {
        printf("Introduce número:");
        scanf("%d", &num1);
        sprintf(buffer, "%d", num1);
        if (num1 != 0)
        {
            write(fp, buffer, strlen(buffer)+1);
            usleep(10000);
        }
    } while (num1 != 0);

    finProcesos(0);
    
    return 0;
}
