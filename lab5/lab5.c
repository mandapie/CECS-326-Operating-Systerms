#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char*argv[])
{
    pid_t pid, w;
    int k, status, n;
    char value[3];
    
    if(argc != 3)
    {
		printf("Need the program name, number of child, sleeptime.\n");
		exit(1);
	}
    
    n = atoi(argv[1]);

    for (k=0;k < n; ++k)
    {
        if ((pid = fork()) == 0)
        {
            sprintf(value, "%d",k);
            execl("child", "child", value, argv[2], (char *) 0);
        }
        else
            printf ("Forked child %d\n", pid);
    }
    /* Wait for children */
    while ((w = wait(&status)) && w != - 1)
    {
    if (w != - 1)
        printf ("Wait on PID: %d returns status of: %04X\n", w, status);
    }
    exit(0);
}