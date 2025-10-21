#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

int contador = 0;        // Número de veces que ha sonado la alarma
int total_alarmas = 0;   // Número total de veces que debe sonar
int intervalo = 0;
void manejador_alarma(int signum) {
     time_t ahora;
    struct tm *info_tiempo;
    char hora[9];

    // Obtener hora actual
    time(&ahora);
    info_tiempo = localtime(&ahora);
    strftime(hora, sizeof(hora), "%H:%M:%S", info_tiempo);

    contador++;
    printf("Señal de alarma recibida a las %s\n", hora);
    fflush(stdout);

    if (contador < total_alarmas) {
        alarm(intervalo); // Programar siguiente alarma
    } else {
        printf("Alarma desactivada\n");
    }
}



int main() {
 printf("¿Cuántas veces sonará la alarma?:\n");
    scanf("%d", &total_alarmas);
    printf("¿Cada cuántos segundos se repetirá la alarma?:\n");
    scanf("%d", &intervalo);

    signal(SIGALRM, manejador_alarma); // Asignar manejador de señal

    printf("Alarma activada\n");
    alarm(intervalo); // Activar primera alarma

    // Esperar hasta que se completen todas las alarmas
    while (contador < total_alarmas) {
        pause(); // Espera a que llegue una señal
    }

    return 0;
}

  

