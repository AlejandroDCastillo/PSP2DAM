#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void main() {
  pid_t pid, pid_hijo, pid_nieto, pid2;
  

  pid = fork();

  if (pid == -1 ) //Ha ocurrido un error 
  {
    printf("ERROR !!! No se ha podido crear el proceso hijo...");
    exit(-1);       
  }
  if (pid == 0 )  //Nos encontramos en Proceso hijo 
  {          
    pid2=fork();
    if (pid2 ==0)//nos encontramos en el Proceso "Nieto"
    {
    printf("Soy el proceso P3, mi PID es %d, el PID de mi padre es: %d\n",getpid(),getppid());
    }else//Nos encontramos en la parte del codigo que solo ejecuta el proceso hijo
    {
     pid_nieto=wait(NULL);//esperamos que finalice el proceso "nieto"
     printf("Soy el proceso P2, mi PID es %d, el PID de mi padre es: %d\n",getpid(),getppid());
    }
  }
  else    //Nos encontramos en Proceso padre 
  { 
   pid_hijo = wait(NULL); //espera la finalización del proceso hijo
     printf("Soy el proceso P1, mi PID es %d, el PID de mi hijo es: %d\n",getpid(),pid);
  }
   exit(0);
}
