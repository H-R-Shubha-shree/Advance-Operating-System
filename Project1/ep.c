#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


extern float etime();

int main(int argc, char *argv[]) 
  {
	if (argc != 3)	
  {
	printf("Usage: ./ep -a size \n");
	exit(1);
	}
 
	float elapsed_time;
	int size=atoi(argv[2]);
	int unit=1024;
	char* buffer = (char*)calloc(size, unit);
	pid_t cpid;
	etime();

	if (strcmp(argv[1], "-b") == 0)
	{
		for (int i=0; i<size*unit; i+=4096)
		{ buffer[i] = 55; }
	}
 
 
   if (cpid=fork()==0) 
   {
   
   if (strcmp(argv[1], "-a") == 0)
	{
		for (int i=0; i<size*unit; i+=4096)
		{ buffer[i] = 55; }
	exit(0);
	
   }
 }
	else
	{
	waitpid(cpid, NULL, 0);
	elapsed_time = etime();
	printf("Elapsed time : %f \n", elapsed_time);
	}
}