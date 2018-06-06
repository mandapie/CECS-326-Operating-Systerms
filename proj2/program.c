# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h> 
# include <unistd.h>

int main (int argc, char*argv[])
{
	
	int a, b, s, sleepTime, seed;
	pid_t pid;

	if(argc != 4){
		printf("Need the program name and 3 arguments.\n");
		exit(1);
	}

	sleepTime = atoi(argv[1]);
	a = atoi(argv[2]);
	b = atoi(argv[3]);

	if(sleepTime <= 0 || sleepTime > 50){
		printf("Enter a sleep time that is greater than 0 or 50 and less.\n");
		exit(1);
	}
	printf("I am parent process, the maximum sleep time is %d and the two numbers are %d and %d.\n",sleepTime,a,b);
	for (int i=0;i<4;i++)
    {
		pid = fork();
        if(pid == 0)
        {
			execlp("./child","child",argv[2],argv[3],i,sleepTime,(char *)NULL);
			perror("Exec failure!\n");
		}
        else
		{
			printf("Forked child %d.\n",(int)pid);
			seed = (int)(getpid() + pid);
		    srand(seed);
		    s = rand() % sleepTime;
	    	sleep(s);
        }
    }
	return(0);
}	
