/**************************************************************************/
/* PROGRAM: proj1.c */
/* DESCRIPTION: This program generates a binary tree */
/* using fork(). The number of levels n is a command line argument. */
/* Each process sleeps for 1 seconds then prints out */
/* Level number, process ID, parent ID, child1 ID, and child2 ID */
/**************************************************************************/
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>

int main(int argc, char *argv[])
{
    int i, n;
    pid_t child1pid, child2pid;
    //if argument entered is not 2, prompt error and exit
    if (argc !=2) {
        printf("\n Usage: %s (number of levels)\n", argv[0]);
        exit(1);
    }
    n = atoi(argv[1]); //n takes in the second argument
    //value of n must be between 1-5, or else exit
    if (n >= 6 || n < 0) {
        printf("number of levels must be 1-5\n");
        exit(1);
    }
    printf("\nlevel number:\tprocess ID:\tparent ID:\tchild1 ID:\tchild2 ID:\n");
    for (i=0; i <= n; i++) {
        child1pid = 0;
        child2pid = 0;
        //if level reaches max level, print the leaves
        if (i == n) {
            printf("%d\t\t%ld\t\t%ld\t\t%ld\t\t%ld\n", i, (long)getpid(), (long)getppid(), (long)child1pid, (long)child2pid);
            break;
        }
        //if child pid is -1, fork failed and exit
        if (child1pid == -1 || child2pid == -1) {
            perror ("\n The fork failed\n");
            exit(1);
        }
        //if either child pid is 0, continue the loop
        if ((child1pid = fork()) == 0 || (child2pid = fork()) == 0) {
            sleep(1);
            continue;
        }
        printf("%d\t\t%ld\t\t%ld\t\t%ld\t\t%ld\n", i, (long)getpid(), (long)getppid(), (long)child1pid, (long)child2pid);
        sleep(n+1); //parent process sleeps for 1 seconds
        exit(0);
    }
    return 0;
}
