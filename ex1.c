#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void main() {
  pid_t pid,pid2,Hijo_pid,Hijo_pid2;
  int fd[2],fd2[2],fd3[2];
  char mensaje[128];
  char buffer[sizeof(mensaje)];
  int numeroCantidad=0;
  int cont;
  int numero2;
  int nomultiplo;
int suma;
  char numero2char[100];
  char *token;
  char delimitador[]=",";
  pipe(fd);
  pid = fork();
  if (pid == -1 ) //Ha ocurrido un error 
  {
    printf("No se ha podido crear el proceso hijo...");
    exit(-1);       
  }
  if (pid == 0 )  //Nos encontramos en P2
  { 
  
        /* Proceso P2 */
        printf("El proceso P2 lee el PIPE \n");//codigo para ver el flujo del programa
        close(fd[1]); // Cierra el descriptor de escritura
        read(fd[0], buffer, 1);
        numeroCantidad=atoi(buffer);
        printf("Mensaje del Pipe: %d\n",numeroCantidad);//codigo para ver el flujo del programa  
        for(int i=0;i<numeroCantidad;i++){
        printf("introduzca número:\n");
    	scanf("%d",&numero2);
    	    sprintf(numero2char, "%d",numero2);
    	          strcat(mensaje,numero2char);
                  strcat(mensaje,",");
        }
        printf("%s\n",mensaje);
        pipe(fd2);
  	pipe(fd3);       
    pid2=fork();
         

    if (pid2==0)
    {
        /* Proceso P3 */
        
                 close(fd2[1]); // Cierra el descriptor de escritura
		read(fd2[0],buffer,sizeof(buffer));  
		token = strtok(buffer, delimitador);
                 while (token != NULL)
               {                	  
        		  numero2=atoi(token);
        		  printf("%d\n",numero2);
        		  if(numero2%5==0){
        		  suma=suma+numero2;
        		  }else{
        		  nomultiplo++;
        		  }
        		  token = strtok(NULL, delimitador);   
   			 }
   			 printf("suma %d",suma);
    		close(fd3[0]); // Cierra el descriptor de lectura
    		    	    sprintf(numero2char, "%d",suma);
    		strcat(mensaje,numero2char);
    		sprintf(numero2char, "%d",nomultiplo);
    		strcat(mensaje,numero2char);
                write(fd3[1], mensaje, sizeof(mensaje));  
    }else{
    		close(fd2[0]); // Cierra el descriptor de lectura
                write(fd2[1], mensaje, sizeof(mensaje));
                 close(fd3[1]);//Cierra el descriptor de escritura
                read(fd3[0],buffer,sizeof(buffer)); 
                 token = strtok(buffer, delimitador);
                 while (token != NULL)
               {                	  
        		  numero2=atoi(token);
        		  printf("%d\n",numero2);
        		 if (cont>0){
        		  suma= atoi(token);
        		  }else
        		  {
        		  nomultiplo= atoi(token);
        		  }
        		  cont++; 
        		  token = strtok(NULL, delimitador);
           
   			 }
   			 printf("suma:%d\n nomultiplo:%d\n",suma,nomultiplo);
	
    }
    }
  else  
  { 
    /* Proceso P1 */
    printf("introduzca la cantidad de números a procesar:\n");
    scanf("%d",&numeroCantidad);
    sprintf(mensaje, "%d",numeroCantidad);
    close(fd[0]); // Cierra el descriptor de lectura
    write(fd[1], mensaje, sizeof(mensaje));
    wait(NULL);
   }

}

