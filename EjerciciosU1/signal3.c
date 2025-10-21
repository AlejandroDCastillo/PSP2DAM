/* El programa muestra cómo capturar una señal del sistema (en este caso SIGINT) 
   y cómo asignarle un manejador personalizado -> función que se ejecuta cuando llega la señal*/

#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<time.h>
#include<stdlib.h>
FILE *archivo;
int contador=0;



/*
  fun_signal es la función manejadora (handler) de la señal.
   - El parámetro signum recibe el número de la señal (en este caso, SIGINT = 2).
   - Cuando el usuario pulsa Ctrl+C, en lugar de que el programa termine inmediatamente (comportamiento por defecto), se ejecuta esta función
  */

 char* mostrar_fecha_y_hora(const char *mensaje) {
    
    time_t t;
    struct tm *tm_info;
    char *resultado = malloc(100);

    time(&t);
    tm_info = localtime(&t);
     snprintf(resultado, 100, "%s: %02d:%02d:%02d\n",
             mensaje,
             tm_info->tm_hour,
             tm_info->tm_min,
             tm_info->tm_sec);

    return resultado;
}


void fun_signal(int signum){
contador++;
    char *mensaje = mostrar_fecha_y_hora("Señal SIGINT recibida a las");

if (mensaje != NULL && archivo != NULL) {
        fprintf(archivo, "%s ", mensaje); // Escribe en archivo
        fflush(archivo);                 // Asegura que se escriba en disco
        free(mensaje);                   // Libera memoria
    }
   if(contador>=4){
   	printf("\nsalimos del programa\n");
	exit(0);
   }

}


int main(){
archivo = fopen("salida.txt", "w");
  signal(SIGINT,fun_signal); // Esta línea registra la función manejadora para la señal SIGINT. A partir de aquí, si se pulsa Ctrl+C, se ejecutará fun_signal()
  while(1){
  pause();
  }
  return 0;
}
