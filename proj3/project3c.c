#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>

int main (int argc, char*argv[])
{
	char *fileName;
	int kValue, sleepTime, numTries, i, status;
	pid_t pid, w;
	
	fileName = argv[1]; //text.dat
	numTries = atoi(argv[2]);
	sleepTime = atoi(argv[3]);
	kValue = atoi(argv[4]); //child number
	
	pid = getpid();
	srand((unsigned)pid);	

	for(i = 0; i < numTries; ++i)
	{
		if(fork() == 0)
		{
			execl("acquire","acquire",argv[2],argv[3],argv[4],(char*)0);
		}
		//wait for child processes to stop
		while ((w = wait(&status)) && w != -1){}
		//breaks out of for loop if the process created by the child successfully acquire the lock
		if (status == 0)
		{
			break;
		}
		//child process goes to sleep if it fails to acquire the lock
        else
		{
			sleep(rand()%sleepTime);
		}
	}

	//child process fails to acquire/create lock file after num tries and kills itself
	if(i == numTries)
	{
		printf("Unable to obtain lock file.\n");
		kill(pid,kValue);
	}
	//child process prints out the content of the text.dat file
	if(fork() == 0)
	{
		execl("/bin/cat", "/bin/cat", fileName, (char*)0);
	}
	//wait for child process to stop
	while ((w = wait(&status)) && w != -1){}
	//child process execute the release.c program
	if(fork() == 0)
	{
		execl("release","release",argv[2],argv[3],argv[4],(char*)0);
	}
	//wait for child process to stop
	while ((w = wait(&status)) && w != -1){}
	exit(pid%255);
	
}
