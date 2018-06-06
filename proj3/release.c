#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>

void main(int argc, char *argv[]){
	
	char *fname = "lock"; 	
	int fd, n_try, sleeptime, kValue, count = 0; 
	pid_t pid;
	
	n_try = argv[2];
	sleeptime = argv[3];
	pid = getpid();
	srand((unsigned)pid);
	
	while (unlink(fname) != 0)
	{
		if(++count < n_try)
		{
			sleep(rand()%sleeptime);
		}
                else 
                {
                	exit(-1);
		}
	}
	exit(0);
}
