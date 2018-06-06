#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

void set_sembuf_struct(struct sembuf *s, int num, int op, int flg)
{
    s-> sem_num = (short) num;
    s-> sem_op = op;
    s-> sem_flg = flg;
    return;
}

int main (int argc, char *argv[])
{
    int N, k, opt, i, status;
    pid_t childPid, pid = getpid();

    key_t ipc_key;
    int semid, semop_ret, sem_value;
    char buf_arr[8192], *c_ptr;
	struct semid_ds sem_buf;

    /* check for invalidation */
    if (argc != 4)
    {
        printf("Need: ./filename #process semaphoreOption(n/s) #delay\n");
        exit(1);
    }
    N = atoi(argv[1]);
    k = atoi(argv[3]);
    if (N < 0 || k < 0)
    {
        printf("Number of processes and delay adjustment speed must be positive integers\n");
        exit(1);
    }
    if (strcmp(argv[2],"n") != 0 && strcmp(argv[2],"s") != 0) 
	{
		printf("The semaphore argument must be either 'n' or 's' only\n");
		exit(1);
	}
    /* semaphore option */
	if (strcmp(argv[2], "n") == 0) // no semaphore protection
		opt = 0;
	if (strcmp(argv[2], "s") == 0) // Semaphore protection
 		opt = 1;
    
    /* declare semaphore wait and increment */
    struct sembuf semwait[1];
    struct sembuf semsignal[1];
    /* initialize semaphore element to 1 */
    set_sembuf_struct(semwait, 0, -1, 0);
    set_sembuf_struct(semsignal, 0, 1, 0);
    ipc_key = ftok(".", 'S'); // Generate a key from a pathname
	/* create semaphore */
	/* semaphore is always created regardless of semaphore procetion. It is only used if k = s */ 
	if ((semid = semget(ipc_key, 1, IPC_CREAT | IPC_EXCL | 0666)) == -1) 
	{
        perror ("semget: IPC | 0666");
        exit(1);
	}
    /* increment semaphore */
    if (semop(semid, semsignal, 1) == -1) {
        printf ("%ld: semaphore increment failed - %s\n", (long)getpid(), strerror(errno));
        if (semctl(semid, 0, IPC_RMID) == -1) // Remove the semaphore if unable to increment
            printf ("%ld: could not delete semaphore - %s\n", (long)getpid(), strerror(errno));
        exit(1);
    }

    /* fork N processes */
    for(i = 1; i < N; i++)
    {
        if((childPid = fork()) == -1) //fails
        {
            perror("fork failed\n");
            exit(1);
        }
        if(childPid > 0) //parent
        {
            break;
        }
    }
    if(opt == 1) {
        while (((semop_ret = semop(semid, semwait, 1)) == -1) && (errno == EINTR)); 
        if (semop_ret == -1) 
            printf ("%ld: semaphore decrement failed - %s\n", (long)getpid(), strerror(errno)); 
    }
    /* create the output message and put in into char buffer */
    sprintf(buf_arr,"i: %d: process ID: %6ld parent ID: %6ld child ID: %6ld\n",(i),(long)getpid(), (long)getppid(), (long)childPid);
    c_ptr = buf_arr; // pointer points to the buffer
    /* if buffer is a null pointer, buffering is disabled for the stream, which becomes an unbuffered stream */
    setbuf(stdout, NULL); // set the buffer to stream for I/O operations
    /* go through the char buffer using the pointer until it points to NULL */
    while (*c_ptr != '\0')
    {
        fputc(*c_ptr, stderr);
        usleep(k); // sleep in usec microsecond using the delay adjustment parameter
        c_ptr++;
    }
    if (opt == 1)
    {
        while (((semop_ret = semop(semid, semsignal, 1)) == -1) && (errno == EINTR)); 
            if (semop_ret == -1) 
                printf ("%ld: semaphore increment failed - %s\n", (long)getpid(), strerror(errno));
    }
    
    waitpid(childPid, &status, 0); // wait for the child process to complete before the parent is killed
    
    /* if this is the parent process, remove the semaphore set */
    if(pid == getpid())
    {
        if(semctl(semid, 0, IPC_RMID) == -1)
        {
            printf("%ld: couldn't delete semaphore - %s\n", (long)getpid(), strerror(errno));
            exit(1);
        }
    }
    exit(0);
}