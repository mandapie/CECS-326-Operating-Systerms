/***********************************************************************************/
/* */
/* PROGRAM : child */
/* CLASS: CECS-326 */
/* Professors: Dr. Thinh Nguyen */
/* Student: Amanda Pan */
/* DESCRIPTION: This program demonstrates communication between a parent */
/* process and a child process. This child process is */
/* invoked by an exec function from parent process. The */
/* parent process passes the child number and a sleep time */
/* in the command line arguments by the exec call. The */
/* child process sleeps for a random time up to sleeptime */
/* and then randomly kills itself. The child process also */
/* displays a message to indicate how it is terminated. */
/* INVOCATION: child n sleeptime */
/* n = child number */
/* sleeptime = maximum sleep time in seconds for */
/* each child process */
/* */
/***********************************************************************************/
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
int main(int argc, char *argv[])
{
pid_t pid, w; /* w = return value for wait() */
int ret_value, n, nsleep; /* ret_value = return value to parent */
/* n = child number */
/* nsleep = sleep time */
pid = getpid(); /* obtain child PID to display message */
ret_value = (int) (pid%256); /* As required, return lowest 8 bits */
srand((unsigned) pid); /* use pid as seed value for random */
nsleep = atoi(argv[2]);
sleep(rand()%nsleep);
n = atoi(argv[1]);
if (rand()%2){
/* randomly kill or exit with 50% probability */
/* rand()%2 returns randomly 0 or 1, if 1, kill itself */
printf("I am the child number %d with PID %d, terminating with signal %d\n",n,pid,n);
kill(pid,n);
} else {
/* if rand()%2 retuns 0, just return */
printf("I am the child number %d with PID %d, terminating with exit(%04X)\n",n,pid, ret_value);
return(ret_value);
}
}