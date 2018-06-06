/**************************************************************************/
/* */
/* PROGRAM: parent */
/* CLASS CECS-326 */
/* Professor: Dr. Thinh Nguyen */
/* Student: Amanda Pan */
/* DESCRIPTION: This program demonstrates communication between */
/* a parent process and a child process. This is */
/* the parent process. The parent creates N child */
/* processes. Each child process then invokes the */
/* child program via execl function call. The */
/* parent process then waits for the child process */
/* to complete. When the child process completes, */
/* it will send a status information back to the */
/* parent. */
/* INVOCATION: parent N sleeptime */
/* N = number of child processes */
/* sleeptime = maximum sleep time in seconds for */
/* each child process */
/* */
/**************************************************************************/
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/wait.h>
int main(int argc, char *argv[])
{
pid_t pid, w; /* w = return value by wait() function call */
int i, status, nchild; /* status = status of wait() */
/* nchild = number of child processes */
char child_num[10];/* child_num[] = character array for child number */
if (argc!= 3)
{
printf ("\n Incorrect number of arguments. Must have 2 arguments.\n");
exit(1);
}
nchild = atoi(argv[1]);
for (i=0; i<nchild; ++i)
{
switch(pid = fork())
{
case 0:
/* In child process */
/* copy the child number to child_num */
sprintf(child_num, "%d", i);
/* invoke child program, pass child number and sleep time */
/* note that the arguments for execl() must be char, not int */
execl("child", "child", child_num, argv[2], (char *) 0);
/* if not, exec failure */
perror ("Exec failure");
return(1);
case -1:
perror ("Fork failure.");
return(2);
default:
/* In parent process */
/* parent sleeps for 3 seconds for child process to perform its task */
sleep(3);
printf ("\nForked child %d\n", pid);
}
}
/* Wait for children */
while ((w = wait(&status)) && w!= -1)
{
if (w != -1)
printf ("Wait on PID: %d returns status of: %04X\n", w,
status);
}
return(0);
}