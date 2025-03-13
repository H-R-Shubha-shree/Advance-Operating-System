#include <sys/time.h>
#include <stdlib.h>

struct timeval start;

float etime()
{
struct timeval end;
float Seconds, Useconds, elapsed_time;
gettimeofday(&end, NULL);
Seconds = (end.tv_sec - start.tv_sec);
Useconds = (end.tv_usec - start.tv_usec);
elapsed_time = (Seconds + Useconds) / 1000000.0;
start=end;
return elapsed_time;
}