#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
/* Parent Program */
int main (int argc, char*argv[])
{
	char *fileName;
	char *lockFileName = "lock";
	char kValue[1];
	int sleepTime, numTries, status;
	pid_t pid, w;

	if(argc != 4){
		printf("Need the program name, file name, number of tries, and sleep time.\n");
		exit(1);
	}

	fileName = argv[1];
	numTries = atoi(argv[2]);
	sleepTime = atoi(argv[3]);

	if(strcmp("text.dat",fileName) != 0)
	{
		printf("File name must be text.dat\n");
		exit(1);
	}

	if(sleepTime <= 0)
	{
		printf("The sleep time number must be greater than zero.\n");
		exit(1);
	}

	if(numTries <= 0)
	{
		printf("The number of tries must be greater than zero.\n");
		exit(1);
	}
	
	//remove lock file before forking child processes
	unlink(lockFileName);
	
	//for loop to create 3 child processes
	for (int k = 0; k < 3; k++)
	{
		pid = fork();
		if(pid < 0)
		{
			perror("Fork failed\n");
			exit(1);
		}
		else if(pid == 0)
		{
			sprintf(kValue,"%d",k);
			execl("project3c","project3c",argv[1],argv[2],argv[3],kValue,(char *)0);
		}
		else{
			printf("Forked child: %d\n",pid);
		}
	}
	//wait for child processes to finish execution
	while ((w = wait(&status)) && w != - 1)
	{
		if (w != - 1){
			printf ("Wait on PID: %d returns status of: %04X\n", w, status);
		}
	}
	exit(0);
}
