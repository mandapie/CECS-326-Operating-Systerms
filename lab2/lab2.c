/**************************************************************************/
/* PROGRAM: lab2.c */
/* DESCRIPTION: This program generates a chain of processes */
/* using fork(). The number of processes n is a command line argument. */
/* Each process sleeps for a random time less than 10 seconds then prints out */
/* process ID, parent ID, and child ID */
/**************************************************************************/
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
int main(int argc, char *argv[])
{
    int i, m, n, sleeptime, seed;
    pid_t childpid;
    if (argc !=3) {
        printf("\n Usage: %s (number of processes) (sleeptime)\n", argv[0]);
        exit(1);
    }
    n = atoi(argv[1]); m = atoi(argv[2]);
	if (n > 10 || m > 20)
	{
		printf("first input must be less than 10 and second input must be less than 20");
		exit(1);
	}
    childpid = 0;
    for (i=0; i<n;i++)
    {
        // same with: if (childpid = fork()) break;
        childpid = fork();
        if (childpid != 0)
        {
            break; // 1-ary tree
        }
    }
    if (childpid == -1) {
        perror ("\n The fork failed\n");
        exit(1);
    }
    printf("\n %d: process ID:%6ld parent ID:%6ld child ID:%6ld",i, (long)getpid(), (long)getppid(), (long)childpid);
    seed = (int)(getpid() + childpid);
    srand(seed);
    /* since each process has a different childpid, using the childpid
    as the seed number will restart the random function.
    Therefore, each process will have a different sleeptime
    */
    sleeptime = rand()%m;
    printf (" sleep = %d\n", sleeptime);
    sleep(sleeptime);
    exit(0);
}