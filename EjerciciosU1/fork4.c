#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void main() {
  pid_t pid,pid2,pid3,pid4,pid5,Hijo6_pid,Hijo2_pid,Hijo3_pid,Hijo4_pid,Hijo5_pid;
  int suma;
    int acumulado=getpid();
  pid = fork();
  if (pid == -1 ) //Ha ocurrido un error 
  {
    printf("No se ha podido crear el proceso hijo...");
    exit(-1);       
  }
  if (pid == 0 )  //P2
  {        
    pid2 =fork();
    if(pid2==0)//P5
   	{
   		if(getpid()%2==0)
   		{
   			acumulado=acumulado+10;
   		}else
   		{
   			acumulado=acumulado-100;
   		}
  		printf ("Soy el proceso P5, mi PID es:%d, mi PPID es: %d, el valor de acumulado es:%d\n",getpid(),getppid(),acumulado);    
   	}else//P2(de nuevo)
   	{	
   		if(getpid()%2==0)
   		{
   			acumulado=acumulado+10;
   		}else
   		{
   			acumulado=acumulado-100;
   		}
   		Hijo5_pid=wait(NULL);
   		printf ("Soy el proceso P2, mi PID es:%d, mi PPID es: %d, el valor de acumulado es:%d\n",getpid(),getppid(),acumulado);    
   	}
   }else//P1 (De nuevo)
    		{
    		pid3=fork();
			if (pid3==0)//P4
    			{
    				if(getpid()%2==0)
   		{
   			acumulado=acumulado+10;
   		}else
   		{
   			acumulado=acumulado-100;
   		}
    				printf ("Soy el proceso P4, mi PID es:%d, mi PPID es: %d, el valor de acuulado es:%d\n",getpid(),getppid(),acumulado);    
    			}else//P3
    				{
    					if(getpid()%2==0)
   		{
   			acumulado=acumulado+10;
   		}else
   		{
   			acumulado=acumulado-100;
   		}
    	    				Hijo4_pid=wait(NULL);
    	    				printf ("Soy el proceso P3, mi PID es:%d, mi PPID es: %d, el valor de acumulado es: %d\n",getpid(),getppid(),acumulado);    		    				    			 
    			}    
    		Hijo3_pid=wait(NULL);
    		Hijo2_pid=wait(NULL);
    		printf ("Soy el proceso P1, mi PID es:%d, mi PPID es: %d, el valor de acumulado es:%d\n",getpid(),getppid(),acumulado);  			
    		}
   
   exit(0);
   }



