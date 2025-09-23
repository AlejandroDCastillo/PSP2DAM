#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void main() {
  pid_t pid, Hijo_pid,pid2,Hijo2_pid,pid3,Hijo3_pid;
  int suma;
  pid = fork();
  if (pid == -1 ) //Ha ocurrido un error 
  {
    printf("No se ha podido crear el proceso hijo...");
    exit(-1);       
  }
  if (pid == 0 )  //Nos encontramos en Proceso hijo 
  {        
    pid2 = fork();
    
    if (pid2 == 0){
    	
    	pid3 = fork();
    	
    	if (pid3 == 0)
    	{
		suma = getpid()+getppid();
		printf ("Soy el proceso P4, mi PID es:%d, mi PPID es: %d, la suma de los PIDs es: %d\n",getpid(),getppid(),suma);    	
    	}else
    	{
    		Hijo3_pid = wait(NULL);
    		suma = getpid()+getppid();
		printf ("Soy el proceso P3, mi PID es:%d, mi PPID es: %d, la suma de los PIDs es: %d\n",getpid(),getppid(),suma);    
    		
    	}
    }else
    {
    		Hijo2_pid = wait(NULL);
    		suma = getpid()+getppid();
		printf ("Soy el proceso P2, mi PID es:%d, mi PPID es: %d, la suma de los PIDs es: %d\n",getpid(),getppid(),suma);    
    }
    
   }else{
   	Hijo_pid = wait(NULL);
   	suma = getpid()+getppid();
		printf ("Soy el proceso P1, mi PID es:%d, mi PPID es: %d, la suma de los PIDs es: %d\n",getpid(),getppid(),suma);    
    }
   exit(0);
}


