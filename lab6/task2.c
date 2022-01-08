#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/timeb.h>

void printData(int number)
{
	struct timeb tmb;
	for (int i = 0; i < 10; i++) {
		ftime(&tmb);
		printf("thread number = %02d, pid = %02d, ppid = %02d, current time (ms) = %02d\n",
			number,
			getpid(),
			getppid(),
			tmb.millitm);
		usleep(number*1000*200);
	}
}

int main(int argc[], char* argv[])
{
	int parents = atoi(argv[2]);
	int childs = atoi(argv[1]);
	int number = 0;
	for (int i = 1; i <= parents; i++) {
		if (fork() == 0) {
			number = i;
			for (int j = 1; j <= childs; j++) {
				if (number == i && fork() == 0) {
					number = parents + j + (childs*(i-1));
				}
			}
		}
	}
	printData(number);
	for (int i = 0; i < parents; i++) {
		wait(0);
	}
}
