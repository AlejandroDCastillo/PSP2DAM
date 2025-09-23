#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void main() {
  pid_t pid, Hijo_pid,pid2,Hijo2_pid,pidNieto,Nieto_pid;
  

  pid = fork();

  if (pid == -1 ) //Ha ocurrido un error 
  {
    printf("No se ha podido crear el proceso hijo...");
    exit(-1);       
  }
  if (pid == 0 )  //Nos encontramos en Proceso hijo 
  {        
    printf("Soy el proceso P2\n");
    if (getpid()%2==0)
   		{
   			printf("Mi PID es:%d, mi PPID es: %d\n",getpid(),getppid());
   		} else printf("Mi PID es:%d\n",getpid());
  }
  else    //Nos encontramos en Proceso padre 
  { 
   pid2 = fork();
   if (pid2 == 0)
   {
   	pidNieto = fork();
   	if (pidNieto == 0)//Ns encontramos en el proceso Nieto
   	{
   		printf("Soy el proceso P4\n");
   		if (getpid()%2==0)
   		{
   			printf("Mi PID es:%d, mi PPID es: %d\n",getpid(),getppid());
   		} else printf("Mi PID es:%d\n",getpid());
   	}else{
   		Nieto_pid=wait(NULL);
   		printf("Soy el proceso P3\n");
   		if (getpid()%2==0)
   		{
   			printf("Mi PID es:%d, mi PPID es: %d\n",getpid(),getppid());
   		} else printf("Mi PID es:%d\n",getpid());
   	}
     }else{
     	Hijo_pid = wait(NULL); //espera la finalización del proceso hijo
     	Hijo2_pid=wait(NULL); //espera la finalización del proceso hijo 2
     	printf ("Soy el proceso P1\n");
     	if (getpid()%2==0)
   		{
   			printf("Mi PID es:%d, mi PPID es: %d\n",getpid(),getppid());
   		} else printf("Mi PID es:%d\n",getpid());
     
   }
   }
   exit(0);
}


