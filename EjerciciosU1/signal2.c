#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int segundos_transcurridos = 0;

void manejador_alarma(int signum) {
    segundos_transcurridos += 5;
    printf("Han transcurrido %d segundos\n", segundos_transcurridos);

    // Reprogramar la alarma
    alarm(5);
}

void manejador_sigint(int signum) {
    printf("\nEl proceso ha terminado. Total de segundos: %d\n", segundos_transcurridos);
    exit(0); // Terminar el programa correctamente
}

int main() {
    // Configurar manejadores de señal
    signal(SIGALRM, manejador_alarma);
    signal(SIGINT, manejador_sigint);

    // Iniciar la primera alarma
    alarm(5);

    // Bucle principal que espera señales
    while (1) {
        pause();  // Esperar hasta que llegue una señal
    }

    return 0;
}

