#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void main() {
  pid_t pid, pid_hijo;
  
  


  pid = fork();

  if (pid == -1 ) //Ha ocurrido un error 
  {
    printf("ERROR !!! No se ha podido crear el proceso hijo...");
    exit(-1);       
  }
  if (pid == 0 )  //Nos encontramos en Proceso hijo 
  {        
    printf("Soy el proceso hijo, el nombre de mi creador es Alejandro Del Castillo \n");	  

  }
  else    //Nos encontramos en Proceso padre 
  { 
   pid_hijo = wait(NULL); //espera la finalización del proceso hijo
   printf("Soy el proceso padre, el PID de mi hijo es: %d y mi PID es: %d\n",pid,getpid());          
  }
   exit(0);
}
