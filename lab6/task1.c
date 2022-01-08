#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>

void printTime()
{
	time_t t = time(NULL);
	struct timeb tmb;
	ftime(&tmb);
	struct tm *current_time = localtime(&t);
	printf("%02d:%02d:%02d:%02d\n",
		current_time->tm_hour,
		current_time->tm_min,
		current_time->tm_sec,
		tmb.millitm);
	printf("\n");
}

int main()
{
	pid_t parent = getpid();

	if (fork() == 0)
	{
		printf("Child thread 1:\n");
		printf("Proccess pid = %d\n", getpid());
		printf("Parent pid = %d\n", getppid());
		printTime();
	}
	if (fork() == 0 && getppid() == parent)
	{
		printf("Child thread 2:\n");
		printf("Proccess pid = %d\n", getpid());
		printf("Parent pid = %d\n", getppid());
		printTime();
	}

	if (parent == getpid())
	{
		printf("Parent thread:\n");
		printf("Proccess pid = %d\n", getpid());
		printTime();
		system("ps -x | grep task1 -m 3");
	}
}
