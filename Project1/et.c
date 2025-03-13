#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

extern float etime();
int size;
char* buffer;
char* before_or_after_fork;

void *thread_function (void *arg)
{
	if (strcmp(before_or_after_fork, "-a") == 0)
	{
		for (int i=0; i<size*1024; i+=4096)
		{ buffer[i] = 55; }
	}
}

int main (int argc, char *argv[])
{
	if (argc!=3)
	{
		printf("Usage: ./ep -a size \n");
		exit(1);
	}
	
	float elapsed_time;
	int size=atoi(argv[2]);
	int unit=1024;
	operand=argv[1];
	char* buffer = (char*)calloc(size,unit);
	pthread_t thread;

	etime();

	if (strcmp(before_or_after_fork, "-b") ==0)
	{
		for(int i=0; i<size*unit; i+=4096)
		{ buffer[i] = 55; }
	}

	pthread_create(&thread, NULL, thread_function, NULL);
	pthread_join(thread, NULL);
	elapsed_time = etime();
	printf("Total elapsed time : %f seconds \n", elapsed_time);
	}