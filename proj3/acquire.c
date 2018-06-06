#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>

void main(int argc, char *argv[]){
	
	char *fname = "lock"; 
	int fd, kValue; 
	pid_t pid;
	
	pid = getpid();
	kValue = atoi(argv[3]);

	while((fd = creat(fname, 0)) == -1 && errno == EACCES)
	{
		kill(pid,kValue); 
	}
	close (fd); 
	exit(0);
}
