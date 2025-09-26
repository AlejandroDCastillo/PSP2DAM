#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void main() {
  pid_t pid,pid2,pid3,pid4,pid5,Hijo6_pid,Hijo2_pid,Hijo3_pid,Hijo4_pid,Hijo5_pid;
  int suma;
  pid = fork();
  if (pid == -1 ) //Ha ocurrido un error 
  {
    printf("No se ha podido crear el proceso hijo...");
    exit(-1);       
  }
  if (pid == 0 )  //P2
  {        
    pid2 =fork();
    		if(pid2==0)//P3
    		{
    		pid3=fork();
    			if(pid3==0)//P5
    			{
    				printf ("Soy el proceso P5, mi PID es:%d, mi PPID es: %d\n",getpid(),getppid());    
    			}else//P3 (de nuevo)
    			{
    				Hijo5_pid=wait(NULL);
    				printf ("Soy el proceso P3, mi PID es:%d, mi PPID es: %d\n",getpid(),getppid());    
    			}
    			
    		}else//P2 (De nuevo)
    		{
    		pid4=fork();
    			if(pid4==0)//P4
    			{
    				pid5=fork();
    				if (pid5==0)//P6
    				{
    				    	printf ("Soy el proceso P6, mi PID es:%d, mi PPID es: %d\n",getpid(),getppid());    
    				}else//P4 (de nuevo)
    				{
    	    				Hijo6_pid=wait(NULL);
    	    				printf ("Soy el proceso P4, mi PID es:%d, mi PPID es: %d\n",getpid(),getppid());    			
    				}
    			}else//P2 (por ultima vez)
    			{
    			Hijo3_pid=wait(NULL);
    			Hijo4_pid=wait(NULL);
    			printf ("Soy el proceso P2, mi PID es:%d, mi PPID es: %d\n",getpid(),getppid());    
    			
    			}
    		}
   }else//P1
   {
   		Hijo2_pid = wait(NULL);
		printf ("Soy el proceso P1, mi PID es:%d, mi PPID es: %d\n",getpid(),getppid());    
    }
   exit(0);
   }



