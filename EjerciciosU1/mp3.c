#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void main() {
  pid_t pid, pid_hijo,pid2,pid_hijo2;
  
  

  pid = fork();
  if (pid == -1 ) //Ha ocurrido un error 
  {
    printf("ERROR !!! No se ha podido crear el proceso hijo...");
    exit(-1);       
  }
  if (pid == 0 )  //Nos encontramos en Proceso hijo 1 
  {        
    printf("Soy el proceso P2,me voy a dormir 10 segundos...\n");
    sleep(10);
    printf("Estoy despierto\n");	  

  }
  else    //Nos encontramos en Proceso padre 
  { 
  pid2=fork();
 	if(pid2 == 0) //Nos encontramos en el proceso hijo 2
 	{
 	  printf("Soy el proceso P3, mi PID es: %d ,el PID de mi padre es: %d \n",getpid(),getppid()); 
 	}
 	else //esta parte del codigo solo se ejecuta en el padre
 	{
 		pid_hijo=wait(NULL);
  		pid_hijo2=wait(NULL);//Las dos lineas hacen que el padre espere a que terminen sus procesos hijos
  		printf("Soy el proceso P1, mis hijos han terminado sus labores\n");
 	}	     
  }
   exit(0);
}
