#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <time.h>
#include <string.h>
void main(){
     time_t t;
     char fecha[]="Soy el Padre,Fecha: ";
     int fd[2];
         char mensaje[128];  // buffer para concatenar fecha y hora

     char buffer[sizeof(mensaje)];
     pid_t pid;
     time(&t);
     // Creamos el pipe
     pipe(fd); 
     
     //Se crea un proceso hijo
     pid = fork();

     if (pid==0)//Proceso hijo
     
     {
                close(fd[1]); // Cierra el descriptor de lectura
                printf("El hijo lee el PIPE \n");
                read(fd[0], buffer, sizeof(buffer));
                printf("Mensaje del Pipe: %s\n",buffer);                          
     }
     
     else//Proceso Padre
     
     {
                close(fd[0]); // Cierra el descriptor de lectura
                strcpy(mensaje, fecha);
                strcat( mensaje ,ctime(&t));
                printf("El padre escribe en el PIPE\n");
      	        write(fd[1], mensaje, strlen(mensaje)+1);                            
      	        wait(NULL);
     }
     
        
}
