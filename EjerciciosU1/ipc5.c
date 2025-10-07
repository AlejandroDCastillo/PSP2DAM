#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <time.h>
#include <string.h>
void main(){
     time_t t;
     char fecha[]="Soy el Padre,Fecha: ";
     int fd[2],fd2[2],dniInt=0;
     char mensaje[128],dni[8];  // buffer para concatenar fecha y hora

     char buffer[sizeof(dni)];
     pid_t pid;
     time(&t);
     // Creamos el pipe
     pipe(fd); 
     pipe(fd2); 
     
     //Se crea un proceso hijo
     pid = fork();

     if (pid==0)//Proceso hijo
     
     {
                close(fd[0]); // Cierra el descriptor de escritura
                printf("introduzca sus numeros del DNI:\n");
                scanf("%s",dni);
                write(fd[1], dni, strlen(dni)+1);
                close(fd2[1]);   
                read(fd2[0],buffer,sizeof(buffer));
                printf("Soy el proceso hijo, la letra es: %s",buffer);                         
                                     
     }
     
     else//Proceso Padre
     
     {
     		int i=0;
     		char letra[] = "TRWAGMYFPDXBNJZSQVHLCKE";
                close(fd[1]); // Cierra el descriptor de lectura
                close(fd2[0]); // Cierra el descriptor de escritura                
		 read(fd[0],buffer,sizeof(buffer));
                dniInt=atoi(buffer)%23;
                write(fd2[1], &letra[dniInt], 1);                            	
      	        wait(NULL);
     }
     
        
}
