#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

/**
 * Muestra la fecha y hora actual con formato, junto al PID del proceso.
 */
void mostrar_fecha_y_hora(const char *mensaje) {
    time_t t;
    struct tm *tm_info;

    time(&t);
    tm_info = localtime(&t);

    printf("%s %d: %02d/%02d/%04d %02d:%02d:%02d\n",
           mensaje,
           getpid(),
           tm_info->tm_mday,
           tm_info->tm_mon + 1,
           tm_info->tm_year + 1900,
           tm_info->tm_hour,
           tm_info->tm_min,
           tm_info->tm_sec);
}

/**
 * Manejador personalizado para la señal SIGINT (Ctrl+C).
 */
void fun_signal(int signum) {

      mostrar_fecha_y_hora("Fin del proceso");


    // Restaurar comportamiento por defecto para SIGINT
    signal(SIGINT, SIG_DFL);
}

int main() {
    // Registrar el manejador personalizado para SIGINT
    signal(SIGINT,fun_signal);

    mostrar_fecha_y_hora("Inicio del proceso");

    // Simular actividad del proceso (espera 30 segundos)
    sleep(30);


    return 0;
}
