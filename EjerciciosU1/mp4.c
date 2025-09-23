/**
Programa Original

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void main()
{
 printf("CCC \n");
 if (fork()!=0)
 {
 printf("AAA \n");
 } else printf("BBB \n");
 exit(0);
}
**/


/**
Respuesta apartado A

	MP4				MP4_hijo	
  ----------------  ======>      --------------------
  PID=1000			   PID=1001
  Fork()=1001  		   PPID=1000			
  printf("CCC")  		   printf("BBB")
  printf("AAA")		   Fork()=0;
  
 **/
 
 
 /** 
 Respuesta apartado B
 
 1 opcion:	2 opcion:
 CCC  		CCC	
 AAA		BBB
 BBB		AAA
 **/
 
 //Respuesta apartado C
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
void main()
{
pid_t pid, pid_hijo;
 printf("CCC \n");
 pid =fork();
 if (pid == 0) //Nos encontramos en el proceso hijo
 {
 	printf("BBB \n");
 } else // Nos encontramos en el proceso padre
 {
 	pid_hijo =wait(NULL);
 	printf("AAA \n");
 }
 	exit(0);
}
